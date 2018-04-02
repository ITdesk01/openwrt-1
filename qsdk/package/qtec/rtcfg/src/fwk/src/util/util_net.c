#include "fwk.h"
#include "util_ifAddr6_oal.h"
#include <net/if.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>


#define UTIL_DNS_RR_MAX_COUNT  (5)
#define UTIL_DNS_NAME_MAX_LEN  (255)
#define __LITTLE_ENDIAN_BITFIELD


enum
{ 
    A = 1,      /* a host address */
    NS,         /* an authoritative name server */
    MD,         /* a mail destination (Obsolete - use MX) */
    MF,         /* */
    CNAME,      /* the canonical name for an alias */
    SOA,        /* marks the start of a zone of authority  */
    MB,         /* a mailbox domain name (EXPERIMENTAL) */
    MG,         /* */
    MR,         /* */
    NUL,        /* */
    WKS,        /* a well known service description */
    PTR,        /* a domain name pointer */
    HINFO,      /* host information */
    MINFO,      /* mailbox or mail list information */
    MX,         /* mail exchange */
    TXT,        /* text strings */

    AAA = 0x1c /* IPv6 A */
};


typedef struct
{
    char name[UTIL_DNS_NAME_MAX_LEN];
    UINT16 type;
    UINT16 class;
    UINT32 ttl;
    UINT16 rdatalen;
    char data[UTIL_DNS_NAME_MAX_LEN];
} UTIL_DNS_RR_T;

typedef union header_flags {
    UINT16 flags;

    struct
    {
#if defined(__LITTLE_ENDIAN_BITFIELD)
        UINT16 rcode:4;
        UINT16 unused:3;
        UINT16 recursion_avail:1;
        UINT16 want_recursion:1;
        UINT16 truncated:1;
        UINT16 authorative:1;
        UINT16 opcode:4;
        UINT16 question:1;
#elif  defined(__BIG_ENDIAN_BITFIELD)
        UINT16 question:1;
        UINT16 opcode:4;
        UINT16 authorative:1;
        UINT16 truncated:1;
        UINT16 want_recursion:1;
        UINT16 recursion_avail:1;
        UINT16 unused:3;
        UINT16 rcode:4;
#else
#error  "Adjust your <asm/byteorder.h> defines"
#endif
    } f;
} UTIL_DNS_HEADER_FLAGS_U;

typedef struct
{
    UINT16 id;
    UTIL_DNS_HEADER_FLAGS_U flags;
    UINT16 qdcount;
    UINT16 ancount;
    UINT16 nscount;
    UINT16 arcount;
} UTIL_DNS_HEADER_T;

typedef struct dns_message
{
    UTIL_DNS_HEADER_T header;
    UTIL_DNS_RR_T question[UTIL_DNS_RR_MAX_COUNT];
    UTIL_DNS_RR_T answer[UTIL_DNS_RR_MAX_COUNT];
} UTIL_DNS_MESSAGE_T;


/* Queries are encoded such that there is and integer specifying how long 
 * the next block of text will be before the actuall text. For eaxmple:
 *             www.linux.com => \03www\05linux\03com\0
 * This function assumes that buf points to an encoded name.
 * The name is decoded into name. Name should be at least 255 bytes long.
 */
static void util_dnsDecodeName(char *name, const char **buf)
{
    SINT32 i;
    SINT32 j = 0;
    SINT32 len = 0;
    
    while (*(*buf))
    {
        len = *(*buf)++;
        for (i = 0; i < len ; i++)
        {
            name[j++] = *(*buf)++;
        }
        name[j++] = '.';
    }
    
    name[j - 1] = *(*buf)++;
}


/* reverse lookups encode the IP in reverse, so we need to turn it around
 * example 2.0.168.192.in-addr.arpa => 192.168.0.2
 * this function only returns the first four numbers in the IP
 *  NOTE: it assumes that name points to a buffer BUF_SIZE long
 */
static void util_dnsDecodeReverseName(char *name)
{
    UINT32 i, j, k;
    char buf[UTIL_DNS_NAME_MAX_LEN];    

    k = 0;

    for (j = 0, i = 0; j < 3; i++)  if (name[i] == '.')  j++;
    for (; name[i] != '.'; i++)  buf[k++] = name[i];
    buf[k++] = '.';

    name[i] = 0;

    for (j = 0, i = 0; j < 2; i++)  if( name[i] == '.')  j++;
    for (; name[i] != '.'; i++)  buf[k++] = name[i];
    buf[k++] = '.';

    for (j = 0, i = 0; j < 1; i++)  if (name[i] == '.')  j++;
    for (; name[i] != '.'; i++)  buf[k++] = name[i];
    buf[k++] = '.';

    for (i = 0; name[i] != '.'; i++)  buf[k++] = name[i];
    buf[k] = 0;

    UTIL_STRNCPY(name, buf, util_strlen(name));
}


/* Decodes the raw packet in buf to create a rr. Assumes buf points to the 
 * start of a rr. 
 * Note: Question rrs dont have rdatalen or rdata. Set is_question when
 * decoding question rrs, else clear is_question
 */
static void util_dnsDecodeRR(UTIL_DNS_RR_T *rr, const char **buf, UBOOL8 isQuestion, const char *header)
{
    /* if the first two bits the of the name are set, then the message has been
     * compressed and so the next byte is an offset from the start of the message
     * pointing to the start of the name 
     */
    if (**buf & 0xC0)
    {
        (*buf)++;
        header += *(*buf)++;
        util_dnsDecodeName(rr->name, &header);
    }
    else
    {
        /* ordinary decode name */
        util_dnsDecodeName(rr->name, buf);
    }  

    UTIL_NTOHS(rr->type, *buf);
    UTIL_NTOHS(rr->class, *buf);

    if ( ! isQuestion)
    {
        UTIL_NTOHL(rr->ttl, *buf);
        UTIL_NTOHS(rr->rdatalen, *buf);

        memcpy(rr->data, *buf, rr->rdatalen);
        *buf += rr->rdatalen;
    }

    if (rr->type == PTR)
    { 
        /* reverse lookup */
        util_dnsDecodeReverseName(rr->name);
    }
}

/* A raw packet pointed to by buf is decoded in the assumed to be alloced 
 * UTIL_DNS_MESSAGE_T structure.
 * RETURNS: 0
 */
static void util_dnsDecodeMessage(const char *response, UTIL_DNS_MESSAGE_T *message)
{
    UINT16 i = 0;
    const char *header = response;

    /* BRCM: just decode id and header */
    UTIL_NTOHS(message->header.id, response);
    UTIL_NTOHS(message->header.flags.flags, response);
    UTIL_NTOHS(message->header.qdcount, response);
    UTIL_NTOHS(message->header.ancount, response);
    UTIL_NTOHS(message->header.nscount, response);
    UTIL_NTOHS(message->header.arcount, response);

    /* decode all the question rrs */
    for (i = 0; i < message->header.qdcount && i < UTIL_DNS_RR_MAX_COUNT; i++)
    {
        util_dnsDecodeRR(&message->question[i], &response, 1, header);
    }  

    /* decode all the response rrs */
    for (i = 0; i < message->header.ancount && i < UTIL_DNS_RR_MAX_COUNT; i++)
    {
        util_dnsDecodeRR(&message->answer[i], &response, 0, header);
    }
}


static void util_dnsDecodeResponse(const char *response, char *hostIp, UINT32 hostIpLen)
{
    struct in_addr *addr = NULL;
    struct in6_addr *addr6 = NULL;
    UINT16 i = 0;
    UTIL_DNS_MESSAGE_T message;

    util_dnsDecodeMessage(response, &message);

    if (message.question[0].type == PTR)
    {
        UTIL_STRNCPY(hostIp, message.question[0].name, hostIpLen);
    }

    /* set according to the response */
    for (i = 0; i < message.header.ancount && i < UTIL_DNS_RR_MAX_COUNT; i++)
    {
        /* make sure we ge the same type as the query incase there are multiple
           and unrelated answers */
        if (message.question[0].type == message.answer[i].type)
        {
            if (message.answer[i].type == A /* BRCM || m->message.response[i].type == AAA */)
            {
                /* Standard lookup so convert data to an IP */
                addr = (struct in_addr *)message.answer[i].data;
                UTIL_STRNCPY(hostIp, inet_ntoa(addr[0]), hostIpLen);
                break;
            }
            else if (message.answer[i].type == AAA)
            {
                addr6 = (struct in6_addr *)message.answer[i].data;
                inet_ntop(AF_INET6, addr6, hostIp, hostIpLen);
                break;
            }
            else if (message.answer[i].type == PTR)
            {
                /* Reverse lookup so convert data to a nume */
                UTIL_STRNCPY(hostIp, message.answer[i].name, hostIpLen);
                break;
            }
        }
    }
}


VOS_RET_E UTIL_dnsDoQuery(const char *hostName,
                          const char *ifName,
                          const char *dnsIp,
                          char *hostIp,
                          UINT32 hostIpLen)
{    
    int sockFd = -1;
    struct sockaddr_in serverAddrIn;
    struct sockaddr_in clientAddrIn;
    struct ifreq ifr;
    const char *start = NULL;
    const char *end = NULL;
    UINT32 len = 0;
    char query[BUFLEN_512] = {0};
    char response[BUFLEN_512] = {0};
    char *buf = NULL;
    int responseLen = 0;
    UINT16 count = 0;
    UINT32 tryTimes = 0;
 
    if (NULL == hostName || NULL == ifName || NULL == dnsIp || NULL == hostIp)
    {
        vosLog_error("Invalid arguments, hostName = %p, ifName = %p, dnsIp = %p, hostIp = %p",
            hostName, ifName, dnsIp, hostIp);
        return VOS_RET_INVALID_ARGUMENTS;
    }
    
    vosLog_debug("Enter: hostName = %s, ifName = %s, dnsIp = %s, hostIpLen = %u",
        hostName, ifName, dnsIp, hostIpLen);

    if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        vosLog_error("Open socket error, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }

    UTIL_STRNCPY(ifr.ifr_name, ifName, IFNAMSIZ);
    if (setsockopt(sockFd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof(ifr)))
    {
        close(sockFd);
        vosLog_error("Bind socket to device error, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }

    bzero(&clientAddrIn, sizeof(clientAddrIn));
    clientAddrIn.sin_family = AF_INET;
    clientAddrIn.sin_port = htons(0);
    if (bind(sockFd, (struct sockaddr *) &clientAddrIn, sizeof(clientAddrIn)))
    {
        close(sockFd);
        vosLog_error("Bind socket error, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }
    
    bzero(&serverAddrIn, sizeof(serverAddrIn));
    serverAddrIn.sin_family = AF_INET;
    serverAddrIn.sin_addr.s_addr = inet_addr(dnsIp);
    serverAddrIn.sin_port = htons(53);

    buf = query;

    UTIL_HTONS(0x5678, buf);
    UTIL_HTONS(0x0100, buf);
    UTIL_HTONS(1, buf);
    UTIL_HTONS(0, buf);
    UTIL_HTONS(0, buf);
    UTIL_HTONS(0, buf);

    start = hostName;
    while ((end = strchr(start, '.')))
    {
        len = end - start;
        if (0 == len)
        {
            close(sockFd);
            vosLog_error("Invalid host name: %s", hostName);
            return VOS_RET_INTERNAL_ERROR;
        }

        *buf++ = len;
        memcpy(buf, start, len);
        buf += len;
        start = end + 1;
    }

    len = util_strlen(start);
    if (0 == len)
    {
        close(sockFd);
        vosLog_error("Invalid host name: %s", hostName);
        return VOS_RET_INTERNAL_ERROR;
    }

    *buf++ = len;
    memcpy(buf, start, len);
    buf += len;
    *buf++ = '\0';

    UTIL_HTONS(1, buf);
    UTIL_HTONS(1, buf);

    vosLog_debug("sendto %u bytes", buf - query);

    if (sendto(sockFd, query, buf - query, 0, (struct sockaddr *)&serverAddrIn, sizeof(serverAddrIn)) < 0)
    {
        close(sockFd);
        vosLog_error("sendto fail, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }
    
    fcntl(sockFd, F_SETFL, O_NONBLOCK);

    for (tryTimes = 0; tryTimes < 3; tryTimes++)
    {
        vosLog_debug("Retry %u time", tryTimes);

        responseLen = recvfrom(sockFd, response, sizeof(response), 0, NULL, NULL);
        if (responseLen < 0)
        {
            vosLog_debug("recvfrom fail, %s(%d)", strerror(errno), errno);
            sleep(1);
        }
        else
        {
            buf = &response[6];
            UTIL_NTOHS(count, buf);
            if (count >= 1)
            {
                close(sockFd);
                util_dnsDecodeResponse(response, hostIp, hostIpLen);

                vosLog_debug("Success: hostIp = %s", hostIp);
                return VOS_RET_SUCCESS;
            }
        }
    }

    close(sockFd);

    vosLog_debug("Fail");
    
    return VOS_RET_INTERNAL_ERROR;
}


VOS_RET_E UTIL_dnsDoIpv6Query(const char *hostName,
                              const char *ifName,
                              const char *dnsIp,
                              char *hostIp,
                              UINT32 hostIpLen)
{    
    int sockFd = -1;
    struct sockaddr_in6 serverAddrIn;
    struct sockaddr_in6 clientAddrIn;
    struct ifreq ifr;
    const char *start = NULL;
    const char *end = NULL;
    UINT32 len = 0;
    char query[BUFLEN_512] = {0};
    char response[BUFLEN_512] = {0};
    char *buf = NULL;
    int responseLen = 0;
    UINT16 count = 0;
    UINT32 tryTimes = 0;
 
    if (NULL == hostName || NULL == ifName || NULL == dnsIp || NULL == hostIp)
    {
        vosLog_error("Invalid arguments, hostName = %p, ifName = %p, dnsIp = %p, hostIp = %p",
            hostName, ifName, dnsIp, hostIp);
        return VOS_RET_INVALID_ARGUMENTS;
    }
    
    vosLog_debug("Enter: hostName = %s, ifName = %s, dnsIp = %s, hostIpLen = %u",
        hostName, ifName, dnsIp, hostIpLen);

    if ((sockFd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0)
    {
        vosLog_error("Open socket error, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }

    UTIL_STRNCPY(ifr.ifr_name, ifName, IFNAMSIZ);
    if (setsockopt(sockFd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof(ifr)))
    {
        close(sockFd);
        vosLog_error("Bind socket to device error, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }

    bzero(&clientAddrIn, sizeof(clientAddrIn));
    clientAddrIn.sin6_family = AF_INET6;
    clientAddrIn.sin6_port = htons(0);
    if (bind(sockFd, (struct sockaddr *) &clientAddrIn, sizeof(clientAddrIn)))
    {
        close(sockFd);
        vosLog_error("Bind socket error, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }
    
    bzero(&serverAddrIn, sizeof(serverAddrIn));
    serverAddrIn.sin6_family = AF_INET6;
    inet_pton(AF_INET6,dnsIp,&serverAddrIn.sin6_addr.s6_addr);
    serverAddrIn.sin6_port = htons(53);

    buf = query;

    UTIL_HTONS(0x5678, buf);
    UTIL_HTONS(0x0100, buf);
    UTIL_HTONS(1, buf);
    UTIL_HTONS(0, buf);
    UTIL_HTONS(0, buf);
    UTIL_HTONS(0, buf);

    start = hostName;
    while ((end = strchr(start, '.')))
    {
        len = end - start;
        if (0 == len)
        {
            close(sockFd);
            vosLog_error("Invalid host name: %s", hostName);
            return VOS_RET_INTERNAL_ERROR;
        }

        *buf++ = len;
        memcpy(buf, start, len);
        buf += len;
        start = end + 1;
    }

    len = util_strlen(start);
    if (0 == len)
    {
        close(sockFd);
        vosLog_error("Invalid host name: %s", hostName);
        return VOS_RET_INTERNAL_ERROR;
    }

    *buf++ = len;
    memcpy(buf, start, len);
    buf += len;
    *buf++ = '\0';

    UTIL_HTONS(0x1c, buf);
    UTIL_HTONS(1, buf);

    vosLog_debug("sendto %u bytes", buf - query);

    if (sendto(sockFd, query, buf - query, 0, (struct sockaddr *)&serverAddrIn, sizeof(serverAddrIn)) < 0)
    {
        close(sockFd);
        vosLog_error("sendto fail, %s(%d)", strerror(errno), errno);
        return VOS_RET_INTERNAL_ERROR;
    }
    
    fcntl(sockFd, F_SETFL, O_NONBLOCK);

    for (tryTimes = 0; tryTimes < 3; tryTimes++)
    {
        vosLog_debug("Retry %u time", tryTimes);

        responseLen = recvfrom(sockFd, response, sizeof(response), 0, NULL, NULL);
        if (responseLen < 0)
        {
            vosLog_debug("recvfrom fail, %s(%d)", strerror(errno), errno);
            sleep(1);
        }
        else
        {
            buf = &response[6];
            UTIL_NTOHS(count, buf);
            if (count >= 1)
            {
                close(sockFd);
                util_dnsDecodeResponse(response, hostIp, hostIpLen);

                vosLog_debug("Success: hostIp = %s", hostIp);
                return VOS_RET_SUCCESS;
            }
        }
    }

    close(sockFd);

    vosLog_error("Fail");
    return VOS_RET_INTERNAL_ERROR;
}


UBOOL8 UTIL_areIpv6AddrEqual(const char *ip6Addr1, const char *ip6Addr2)
{
    VOS_RET_E ret = VOS_RET_SUCCESS;
    char address1[BUFLEN_64] = {0};
    char address2[BUFLEN_64] = {0};
    UINT32 plen1 = 0;
    UINT32 plen2 = 0;
    struct in6_addr   in6Addr1, in6Addr2;

    if (IS_EMPTY_STRING(ip6Addr1) && IS_EMPTY_STRING(ip6Addr2))
    {
        return TRUE;
    }
    
    if (ip6Addr1 == NULL || ip6Addr2 == NULL)
    {
        return FALSE;
    }

    if (VOS_RET_SUCCESS != (ret = util_parsePrefixAddress(ip6Addr1, address1, sizeof(address1), &plen1)))
    {
        vosLog_error("util_parsePrefixAddress returns error. ret=%d", ret);
        return FALSE;
    }
    
    if (VOS_RET_SUCCESS != (ret = util_parsePrefixAddress(ip6Addr2, address2, sizeof(address2), &plen2)))
    {
        vosLog_error("util_parsePrefixAddress returns error. ret=%d", ret);
        return FALSE;
    }

    if (inet_pton(AF_INET6, address1, &in6Addr1) <= 0)
    {
        vosLog_error("Invalid address1=%s", address1);
        return FALSE;
    }
    
    if (inet_pton(AF_INET6, address2, &in6Addr2) <= 0)
    {
        vosLog_error("Invalid address2=%s", address2);
        return FALSE;
    }

    return ((memcmp(&in6Addr1, &in6Addr2, sizeof(struct in6_addr)) == 0) && (plen1 == plen2));
}  /* cmsNet_areIp6AddrEqual() */


UBOOL8 UTIL_isAddressOnLanSide(const char *ipAddr)
{
   UBOOL8 onLanSide = FALSE;

   /* determine the address family of ipAddr */
   if ((ipAddr != NULL) && (strchr(ipAddr, ':') == NULL))
   {
      /* ipv4 address */
      char ip[BUFLEN_64] = {0};
      char mask[BUFLEN_64] = {0};
      struct in_addr clntAddr, inAddr, inMask;

      UTIL_getIfAddr("br0", ip, sizeof(ip));
      UTIL_getIfMask("br0", mask, sizeof(mask));

      clntAddr.s_addr = inet_addr(ipAddr);
      inAddr.s_addr = inet_addr(ip);
      inMask.s_addr = inet_addr(mask);
      
      /* check ip address of support user to see it is in LAN or not */
      if ( (clntAddr.s_addr & inMask.s_addr) == (inAddr.s_addr & inMask.s_addr))
         onLanSide = TRUE;
      else 
      {
         /* check ip address of support user to see if it is from secondary LAN */
         UBOOL8 isUp = FALSE;

         UTIL_checkInterfaceUp("br0:0", &isUp);
         if (isUp)
         {
            UTIL_getIfAddr("br0", ip, sizeof(ip));
            UTIL_getIfMask("br0", mask, sizeof(mask));

            inAddr.s_addr = inet_addr(ip);
            inMask.s_addr = inet_addr(mask);
            
            if ( (clntAddr.s_addr & inMask.s_addr) == (inAddr.s_addr & inMask.s_addr) )
               onLanSide = TRUE;
         }
         /* This function will not work for ppp ip extension.  See dal_auth.c for detail */
      }
   }
   else if (1)
   {
      /* ipv6 address */
      char lanAddr6[BUFLEN_32];

      if (UTIL_getIfAddr("br0", lanAddr6, sizeof(lanAddr6)) != VOS_RET_SUCCESS)
      {
         vosLog_error("cmsDal_getLanAddr6 returns error.");
      }
      else
      {
         /* see if the client addr is in the same subnet as br0. */
         onLanSide = UTIL_isHostInSameSubnet(ipAddr, lanAddr6);
      }
   }

   return onLanSide;

}  /* End of cmsNet_isAddressOnLanSide() */


UBOOL8 UTIL_isHostInSameSubnet(const char *addrHost, const char *addrPrefix)
{
   char address[BUFLEN_32];
   char prefix1[BUFLEN_32];
   char prefix2[BUFLEN_32];
   UINT32 plen = 0;
   VOS_RET_E ret = VOS_RET_SUCCESS;

   *address = '\0';
   *prefix1 = '\0';
   *prefix2 = '\0';

   if (IS_EMPTY_STRING(addrHost) && IS_EMPTY_STRING(addrPrefix))
   {
      return TRUE;
   }
   if (addrHost == NULL || addrPrefix == NULL)
   {
      return FALSE;
   }

   if (strchr(addrHost, '/') != NULL)
   {
      vosLog_error("Invalid host address %s", addrHost);
      return FALSE;
   }
   if (strchr(addrPrefix, '/') == NULL)
   {
      vosLog_error("Invalid address prefix %s", addrPrefix);
      return FALSE;
   }

   if ((ret = util_parsePrefixAddress(addrPrefix, address, sizeof(address), &plen)) != VOS_RET_SUCCESS)
   {
      vosLog_error("cmsUtl_parsePrefixAddress returns error. ret=%d", ret);
      return FALSE;
   }

   if ((ret = util_getAddrPrefix(addrHost, plen, prefix1)) != VOS_RET_SUCCESS)
   {
      vosLog_error("cmsUtl_getAddrPrefix returns error. ret=%d", ret);
      return FALSE;
   }
   if ((ret = util_getAddrPrefix(address, plen, prefix2)) != VOS_RET_SUCCESS)
   {
      vosLog_error("cmsUtl_getAddrPrefix returns error. ret=%d", ret);
      return FALSE;
   }

   return (UTIL_areIpv6AddrEqual(prefix1, prefix2));

}  /* cmsNet_isHostInSameSubnet() */


UBOOL8 UTIL_getIfMask(const char *devName, char* ip, UINT32 ipLen)
{
    SINT32  skfd = 0;
    UBOOL8  ret = FALSE;
    struct ifreq intf;
    char *ptr = NULL;
    
    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return ret;
    }
    
    UTIL_STRNCPY((char *)intf.ifr_name, devName, (UINT32)sizeof(intf.ifr_name));
    
    if (-1 != ioctl(skfd, SIOCGIFNETMASK, &intf)) 
    {
        if (NULL != (ptr = inet_ntoa(((struct sockaddr_in *)(&(intf.ifr_netmask)))->sin_addr)))
        {
            UTIL_STRNCPY(ip, ptr, ipLen);
            ret = TRUE;
        }
    }
    close(skfd);
    
    return ret;
}


UBOOL8 UTIL_getIfSubnet(const char *devName, char* ipSubnet, UINT32 ipSubnetLen) 
{
    char *ptr = NULL;
    char ipaddr[BUFLEN_32] = {0}, netmask[BUFLEN_32] = {0};
    struct in_addr ip, mask, subnet;
    UBOOL8 ret = FALSE;

    memset(&ip, 0, sizeof(ip));
    memset(&mask, 0, sizeof(mask));
    memset(&subnet, 0, sizeof(subnet));

    if (UTIL_getIfAddr(devName, ipaddr, BUFLEN_32) && UTIL_getIfMask(devName, netmask, BUFLEN_32))
    {
        if (inet_aton(ipaddr, &ip) && inet_aton(netmask, &mask)) 
        {
            subnet.s_addr = ip.s_addr & mask.s_addr;
            if (NULL != (ptr = inet_ntoa(subnet))) 
            {
                UTIL_STRNCPY(ipSubnet, ptr, ipSubnetLen);
                ret = TRUE;
            }
        }
    }
    
    return ret;
}


UBOOL8 UTIL_isInterfaceExisted(const char *ifName)
{
    int sockfd;
    struct ifreq ifr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        vosLog_debug("[%s, %d] socket fail\r\n", __FUNCTION__, __LINE__);
        return FALSE;
    }

    UTIL_STRNCPY(ifr.ifr_name, ifName, sizeof(ifr.ifr_name));
    if (0 > ioctl(sockfd, SIOCGIFINDEX, &ifr))
    {
        vosLog_debug("[%s, %d] ioctl fail\r\n", __FUNCTION__, __LINE__);
        return FALSE;
    }

    close(sockfd);

    return (ifr.ifr_ifindex > 0) ? TRUE : FALSE;
}


VOS_RET_E UTIL_setIfState(const char *ifName, UBOOL8 up)
{
    int sockfd = -1;
    struct ifreq ifr;

    if (NULL == ifName)
    {
        vosLog_error("NULL == ifName");
        return VOS_RET_INVALID_ARGUMENTS;
    } 

    vosLog_debug("ifName = %s, up = %s", ifName, up ? "UP" : "DOWN");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        vosLog_error("Create socket fail");
        return VOS_RET_INTERNAL_ERROR;
    }

    strncpy(ifr.ifr_name, ifName, IFNAMSIZ);
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0)
    {
        vosLog_error("Get if flags fail");
        close(sockfd);
        return VOS_RET_INTERNAL_ERROR;
    }

    if (up)
    {
        ifr.ifr_flags |= IFF_UP;
    }
    else
    {
        ifr.ifr_flags &= (~IFF_UP);
    }

    if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0)
    {
        vosLog_error("Set if flags fail");
        close(sockfd);
        return VOS_RET_INTERNAL_ERROR;
    }

    close(sockfd);

    return VOS_RET_SUCCESS;
}


VOS_RET_E UTIL_checkInterfaceUp(const char *devName, UBOOL8 *up) 
{
   int skfd = 0;
   struct ifreq intf;
   *up = FALSE;

   if ((NULL == devName) || (0 > (skfd = socket(AF_INET, SOCK_DGRAM, 0)))) 
   {
   	  *up = FALSE;
      return VOS_RET_INTERNAL_ERROR;
   }

   strncpy(intf.ifr_name, devName, strlen(devName));

   /*    if interface is br0:0 and
    * there is no binding IP address then return down
    */

   if (NULL != strchr(devName, ':')) 
   {
      if (0 > ioctl(skfd, SIOCGIFADDR, &intf))
      {
	  	 *up = FALSE;
         close(skfd);
         return VOS_RET_INTERNAL_ERROR;
      }
   }

   // if interface flag is down then return down
   if (-1 != ioctl(skfd, SIOCGIFFLAGS, &intf)) 
   {
      if (0 != (intf.ifr_flags & IFF_UP))
      {
         *up = TRUE;
      }
   }

   close(skfd);

   return VOS_RET_SUCCESS;
}


UBOOL8 UTIL_getIfAddr(const char *devName, char* ip, UINT32 ipLen) 
{
    SINT32 skfd = 0;
    struct ifreq intf;
    char *ptr = NULL;
    UBOOL8 ret = FALSE;
    
    if (0 > (skfd = socket(AF_INET, SOCK_DGRAM, 0))) 
    {
        return ret;
    }
    
    UTIL_STRNCPY(intf.ifr_name, devName, sizeof(intf.ifr_name));
    
    if (-1 != ioctl(skfd, SIOCGIFADDR, &intf))
    {
        if (NULL != (ptr = inet_ntoa(((struct sockaddr_in *)(&(intf.ifr_dstaddr)))->sin_addr))) 
        {
            UTIL_STRNCPY(ip, ptr, ipLen);
            ret = TRUE;
        }
    }
    close(skfd);
    
    return ret;
}


VOS_RET_E UTIL_getIfAddr6(const char *ifname, 
                                   UINT32 addrIdx,
                                   char *ipAddr, 
                                   UINT32 *ifIndex,
                                   UINT32 *prefixLen, 
                                   UINT32 *scope, 
                                   UINT32 *ifaFlags)
{
    return oal_getIfAddr6(ifname, addrIdx, ipAddr, ifIndex, prefixLen, scope, ifaFlags); 
}


VOS_RET_E UTIL_getLinkLocalIfAddr6(const char *ifname, 
                                           char *ipAddr,
                                           UINT32 *prefixLen)
{
    VOS_RET_E ret = VOS_RET_SUCCESS;
    UINT32 addrIdx=0;
    UINT32 netlinkIndex=0;
    UINT32 scope=0;
    UINT32 ifaflags=0;

    while (VOS_RET_SUCCESS == ret)
    {
        ret = UTIL_getIfAddr6(ifname, addrIdx, ipAddr, &netlinkIndex, prefixLen, &scope, &ifaflags);
        if ((VOS_RET_SUCCESS == ret) && (0x20 == scope))  // found it
        {
             return VOS_RET_SUCCESS;
        }
       
        addrIdx++;
    }

    // if we get here, then we did not find one
    return VOS_RET_NO_MORE_INSTANCES;
}


VOS_RET_E UTIL_getGloballyUniqueIfAddr6(const char *ifname, 
                                        char *ipAddr, 
                                        UINT32 *prefixLen)
{
    VOS_RET_E ret = VOS_RET_SUCCESS;
    UINT32 addrIdx=0;
    UINT32 netlinkIndex=0;
    UINT32 scope=0;
    UINT32 ifaflags=0;

    while (VOS_RET_SUCCESS == ret)
    {
        ret = UTIL_getIfAddr6(ifname, addrIdx, ipAddr, &netlinkIndex, prefixLen, &scope, &ifaflags);
        if ((VOS_RET_SUCCESS == ret) && (0 == scope))  // found it
        {
             return VOS_RET_SUCCESS;
        }
       
        addrIdx++;
    }

    // if we get here, then we did not find one
    return VOS_RET_NO_MORE_INSTANCES;
}


VOS_RET_E UTIL_subnetLenToSubnetMask(const UINT32 subnetLen, char *subnetMask, UINT32 subnetMaskLen)
{
    VOS_RET_E ret = VOS_RET_SUCCESS;
    UINT32 sMask = 0xffffffff;
    UINT32 pos = 32 - subnetLen;
    unsigned char *buffer = NULL;

    sMask = sMask << pos;

    buffer = (unsigned char *)&sMask;

    UTIL_SNPRINTF(subnetMask, subnetMaskLen, "%d.%d.%d.%d", buffer[3], buffer[2], buffer[1], buffer[0]);

    return ret;
}


