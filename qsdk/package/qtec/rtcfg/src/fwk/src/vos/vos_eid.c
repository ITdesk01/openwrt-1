#include "fwk.h"
#include "util_pid_oal.h"


#define VOS_EID_DEF_LIFE_NUM  (20)


static VosEntityInfo entityInfoArray[] = {
#if 0
   {EID_GPONHAL,
    0,
    "gponhal",
    "/usr/S204/bin/hal",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_VOIPAGENT,
    NDA_ACCESS_VOIPAGENT,
    "voipagent",
    "/usr/S204/bin/voipagent",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_CTCSTP,
    NDA_ACCESS_HTTPD,
    "loopdetect",
    "/bin/loopdetect",
    "",    /* run args */
    EIF_MDM|EIF_SERVER|EIF_SERVER_TCP|EIF_LAUNCH_ON_BOOT|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    FALSE,
    0, 0, 0, 0},

   {EID_TR69C,        /* eid */
    NDA_ACCESS_TR69C, /* TR69 attribute access bit */
    "tr69c",          /* name */
    "/usr/S304/bin/tr69c",     /* path */
    "",               /* run args */
    EIF_MDM|EIF_SERVER|EIF_SERVER_TCP|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE|EIF_MONITOR|EIF_AUTO_RELAUNCH,
    1,                /* backlog for TCP server port */
    TR69C_CONN_REQ_PORT,       /* TCP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, VOS_EID_DEF_LIFE_NUM},         /* misc mem usage parameters */

   {EID_HTTPD,
    NDA_ACCESS_HTTPD,
    "httpd",
    "/usr/S304/bin/httpd",
    "",
    EIF_MDM|EIF_SERVER|EIF_SERVER_TCP|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    20,                /* backlog for TCP server port */
    HTTPD_DEF_PORT,       /* TCP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_SNMPD,
    NDA_ACCESS_SNMPD,
    "snmpd",
    "/usr/S304/bin/snmpd",
    "",
    EIF_MDM|EIF_MESSAGING_CAPABLE,
    /*    EIF_MDM, */
    0,
    SNMPD_PORT,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},
#endif
   {EID_CONSOLED,
    NDA_ACCESS_CONSOLED,
    "consoled",
    "/usr/bin/consoled",
    "",
    EIF_MDM|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_TELNETD,
    NDA_ACCESS_TELNETD,
    "telnetd",
    "/usr/bin/telnetd",
    "",
    EIF_MDM|EIF_SERVER|EIF_SERVER_TCP|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    3,             /* backlog for TCP server port */
    TELNETD_PORT,
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},
#if 0    
   {EID_SSHD,
    NDA_ACCESS_SSHD,
    "sshd",
    "/usr/S304/bin/sshd",
    "",
    EIF_MDM|EIF_SERVER|EIF_SERVER_TCP|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    3,             /* backlog for TCP server port */
    SSHD_PORT,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_UPNP,
    NDA_ACCESS_UPNP,
    "upnp",
    "/usr/S304/bin/upnp",
    "",
    EIF_MDM|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    FALSE,             /* isFeatureCompiledIn */
    0, 0, 0, 0}, 
#endif
   {EID_SMD,
    0,
    "smd",
    "/usr/S304/bin/smd",
    "",
    EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,   /* flags */
    0,
    0,
    TRUE,               /* isFeatureCompiledIn */
    0, 0, 0, 0},
#if 0
    {EID_HAL,
     0,
     "hal",
     "/usr/S304/bin/hal",
     "",
     EIF_LAUNCH_IN_STAGE_1|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
     0,
     0,
     TRUE,             /* isFeatureCompiledIn */
     0, 0, 0, 0},

   {EID_CMC,
    0,
    "cmc",
    "/usr/S304/bin/cmc",
    "",
    EIF_LAUNCH_IN_STAGE_1|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE|EIF_AUTO_RELAUNCH|EIF_MONITOR,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 6},

   {EID_SSK,
    NDA_ACCESS_SSK,
    "ssk",
    "/usr/S304/bin/ssk",
    "",
    EIF_LAUNCH_ON_BOOT|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE|EIF_AUTO_RELAUNCH|EIF_MONITOR,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, VOS_EID_DEF_LIFE_NUM},

    {EID_MMC,
    NDA_ACCESS_SSK,
    "mmc",
    "/usr/S304/bin/mmc",
    "",
    EIF_LAUNCH_ON_BOOT|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, VOS_EID_DEF_LIFE_NUM},

   {EID_PPP,
    0,
    "pppd",
    "/usr/S304/bin/pppd",
    "-c",
    EIF_MESSAGING_CAPABLE|EIF_MULTIPLE_INSTANCES,
    0,
    0,
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_L2TPD,
    0,
    "openl2tpd",
    "/usr/S304/bin/openl2tpd",
    "",
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_DHCPC,
    0,
    "dhcpc",
    "/usr/S304/bin/dhcpc",
    "-f",  /* stay in foreground, we don't want it to fork or daemonize */
    EIF_MESSAGING_CAPABLE|EIF_MULTIPLE_INSTANCES,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_DHCPD,
    0,
    "dhcpd",
    "/usr/S304/bin/dhcpd",
    "",
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_FTPD,
    0,
    "bftpd",
    "/usr/S304/bin/bftpd",
    "",
    EIF_SERVER|EIF_SERVER_TCP|EIF_MESSAGING_CAPABLE,
    1, /* backlog for TCP server port */
    FTPD_PORT,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_TFTPD,
    0,
    "tftpd",
    "/usr/bin/tftpd",
    "",
    EIF_SERVER|EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    0,
    TFTPD_PORT,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_TFTP,  /* this is the client */
    0,
    "tftp",
    "/usr/bin/tftp",
    "",
    EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_DNSPROBE,
    0,                  /* TR69 attribute access bit */
    "dnsprobe",
    "/bin/dnsprobe",
    "",                 /* run args */
    0,                  /* EIF_ flags */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_DNSPROXY,
    0,
    "dnsproxy",
    "/usr/S304/bin/dnsproxy",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE|EIF_AUTO_RELAUNCH|EIF_LAUNCH_ON_BOOT,  /* EIF_ flags */
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_SYSLOGD,
    0,                  /* TR69 attribute access bit */
    "syslogd",
    "/usr/S304/bin/syslogd",
    "-n",               /* run args (don't daemonize) */
    0,                  /* flags */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_KLOGD,
    0,                  /* TR69 attribute access bit */
    "klogd",
    "/sbin/klogd",
    "-n",               /* run args (don't daemonize) */
    0,                  /* flags */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_VODSL,
    NDA_ACCESS_VODSL,   /* tr69 attribute access bit, not applicable to vodsl */
    "vodsl",
    "/usr/S304/bin/vodsl",
    "-t",           /* run args */
    EIF_MDM|EIF_MESSAGING_CAPABLE|EIF_AUTO_RELAUNCH|EIF_MONITOR,
    0,            /* backlog for TCP server port, if this is a tcp server */
    0,            /* TCP/UDP server port */
    FALSE,
    0, 0, 0, VOS_EID_DEF_LIFE_NUM},     /* misc memory parameters */

   {EID_DECTDBGD,
    NDA_ACCESS_DECTDBGD,   /* tr69 attribute access bit, not applicable to vodsl */
    "dectdbgd_NEW",
    "/etc/dectdbgd",
    "",           /* run args */
    EIF_MDM|EIF_MESSAGING_CAPABLE,
    0,            /* backlog for TCP server port, if this is a tcp server */
    0,            /* TCP/UDP server port */
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},     /* misc memory parameters */

   {EID_DDNSD,
    0,                  /* TR69 attribute access bit */
    "ddnsd",
    "/usr/S304/bin/ddnsd",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* flags (later make it desktop capable) */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_ZEBRA,
    0,                  /* TR69 attribute access bit */
    "zebra",
    "/bin/zebra",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* flags (later make it desktop capable) */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_RIPD,
    0,                  /* TR69 attribute access bit */
    "ripd",
    "/bin/ripd",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* flags (later make it desktop capable) */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_SNTP,
    0,                  /* TR69 attribute access bit */
    "sntp",
    "/usr/S304/bin/sntp",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* flags (later make it desktop capable) */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_URLFILTERD,
    0,
    "urlfilterd",
    "/usr/S304/bin/urlfilterd",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* flags (later make it desktop capable) */
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_DHCP6C,
    0,
    "dhcp6c",
    "/usr/S304/bin/dhcp6c",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE|EIF_MULTIPLE_INSTANCES,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_DHCP6S,
    0,
    "dhcp6s",
    "/usr/S304/bin/dhcp6s",
    "",                 /* run args */
    0,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_RADVD,
    0,
    "radvd",
    "/usr/S304/bin/radvd",
    "",                 /* run args */
    0,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_RASTATUS6,
    0,
    "rastatus6",
    "/bin/rastatus6",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_FTP,   /* this is FTP the client */
    0,
    "ftp",
    "/usr/bin/ftp",
    "",
    EIF_MESSAGING_CAPABLE|EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_UNITTEST,
    0,
    "ut",
    "/",
    "",
    0,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},
    
   {EID_PING,
    0,
    "ping",
    "/usr/S304/bin/ping",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_MULTIPLE_INSTANCES,  /* EIF_ flags */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_TRACERT,
    0,
    "traceroute",
    "/usr/S304/bin/traceroute",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* EIF_ flags */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */
  
   {EID_PWRCTL,
    0,
    "pwrctl",
    "/bin/pwrctl",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* EIF_ flags */
    0,                  /* backlog for TCP server port */
    0,                  /* TCP/UDP server port */
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},           /* misc memory parameters */

   {EID_HOTPLUG,
    0,
    "hotplug",
    "/usr/S304/bin/hotplug_netlink",
    "",
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_SAMBA,
    0,
    "smbd",
    "/bin/smbd",
    "-D",
    0,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_MISC,
    0,
    "misc",
    "/",
    "",
    0,
    0,
    0,
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_MCPD,
    0,
    "mcpd",
    "/usr/S304/bin/mcpd",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE|EIF_AUTO_RELAUNCH|EIF_MONITOR,  /* flags (later make it desktop capable) */
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, VOS_EID_DEF_LIFE_NUM},

   {EID_MCPCTL,
    0,
    "mcpctl",
    "/bin/mcpctl",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,  /* flags (later make it desktop capable) */
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_PPPOE_SERVER,
     0,
     "pppoe-server",
     "/usr/sbin/pppoe-server",
     "",
     EIF_MULTIPLE_INSTANCES,
     0,
     0,
     FALSE,            /* isFeatureCompiledIn */
     0, 0, 0, 0},

   {EID_DMSD,
    0,
    "dmsd",
    "/usr/S304/bin/dmsd",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0}, 

   {EID_EPON_APP,
    NDA_ACCESS_EPONAPP,
    "eponapp",
    "/bin/eponapp",
    "",                 /* run args */
    EIF_MDM | EIF_LAUNCH_ON_BOOT | EIF_MESSAGING_CAPABLE,
    0,
    0,
    FALSE,             /* isFeatureCompiledIn */
    0, 0, 0, 0}, 

    {EID_IPV6MON,
      0,
      "ipv6mon",
      "/usr/S304/bin/ipv6mon",
      "",                 /* run args */
      EIF_LAUNCH_ON_BOOT | EIF_MESSAGING_CAPABLE,
      0,
      0,
      FALSE,            /* isFeatureCompiledIn */
      0, 0, 0, 0},

   {EID_SIPALG,
    0,   /* tr69 attribute access bit, not applicable to vodsl */
    "siproxd",
    "/usr/S304/bin/siproxd",
    "--config /var/siproxd/siproxd.conf",           /* run args */
    0,
    0,            /* backlog for TCP server port, if this is a tcp server */
    0,            /* TCP/UDP server port */
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},     /* misc memory parameters */
    
   {EID_MMED,
    NDA_ACCESS_MME,
    "mmed",
    "/usr/S304/bin/mmed",
    "",
    EIF_LAUNCH_ON_BOOT|EIF_MESSAGING_CAPABLE|EIF_AUTO_RELAUNCH|EIF_MONITOR,
    0, 
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, VOS_EID_DEF_LIFE_NUM},

   {EID_IPPD,
    0,
    "ippd",
    "/usr/S304/bin/ippd",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    FALSE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_MONITORCOLLECTOR,
     NDA_ACCESS_MONITORCOLLECTOR,
     "monitorcollector",
     "/usr/S304/bin/monitorcollector",
     "",  /* stay in foreground, we don't want it to fork or daemonize */
     EIF_MDM |EIF_MESSAGING_CAPABLE,
     0,
     0,
     FALSE,             /* isFeatureCompiledIn */
     0, 0, 0, 0},

   {EID_DYNAMIC_BASE,
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},    

   {(VosEntityId)(EID_DYNAMIC_BASE + 1),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 2),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 3),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 4),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 5),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 6),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 7),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 8),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},  
    
   {(VosEntityId)(EID_DYNAMIC_BASE + 9),
    0,   
    NULL,
    NULL,
    NULL,
    0,
    0,            
    0,            
    FALSE,
    0, 0, 0, 0},

   {EID_NET_SNIFFER,
    0,
    "net_sniffer",
    "/usr/S304/bin/net_sniffer",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},

   {EID_WGET,
    NDA_ACCESS_HTTPD,
    "wget",
    "/bin/wget",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE,
    0,
    0,
    TRUE,            /* isFeatureCompiledIn */
    0, 0, 0, 0},
#endif
    {EID_QTECDEVICEMANAGER,
    0,
    "QtecDeviceManager",
    "/bin/QtecDeviceManager",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_AUTO_RELAUNCH,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_MYWEBSOCKET,
    0,
    "mywebsocket",
    "/usr/bin/myclient",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_AUTO_RELAUNCH,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},
	
	{EID_CGIREQ,
    0,
    "CGIREQ",
    NULL,
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_MULTIPLE_INSTANCES,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

	{EID_CGIMSGPROC,
    0,
    "CGIMSGPROC",
    "/bin/cgimsgmanager",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_AUTO_RELAUNCH,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

	{EID_LANHOST,
    0,
    "LANHOST",
    "/bin/lanHostManager",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_AUTO_RELAUNCH,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},
    
    {EID_SCRCTRL,
    0,
    "screen_ctrl",
    "/usr/bin/scrctrl",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_AUTO_RELAUNCH,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_TCP_PROXY,
    0,
    "tcpproxy",
    "/usr/bin/tcpproxy",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_AUTO_RELAUNCH,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_WDS_CTRL,
    0,
    "wdsctrl",
    "/usr/bin/wdsctrl",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_MULTIPLE_INSTANCES,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_QTEC_GETKEY,
    0,
    "qtec_getkey",
    "/sbin/qtec_getkey",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE | EIF_MULTIPLE_INSTANCES,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},


    {EID_SMB_INIT,
    0,
    "smbinit",
    "/usr/bin/smbinit",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_MYCLIENT_FOR_LOCK,
    0,
    "mywebsocket1",
    "/usr/bin/myclient1",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

    {EID_TIMER_TASK,
    0,
    "timertask",
    "/usr/bin/timertask",
    "",                 /* run args */
    EIF_MESSAGING_CAPABLE | EIF_DESKTOP_LINUX_CAPABLE,
    0,
    0,
    TRUE,             /* isFeatureCompiledIn */
    0, 0, 0, 0},

};


#define NUM_ENTITY_INFO_ENTRIES (sizeof(entityInfoArray)/sizeof(VosEntityInfo))


UINT32 vosEid_getNumberOfEntityInfoEntries(void)
{
   return NUM_ENTITY_INFO_ENTRIES;
}


const VosEntityInfo *vosEid_getFirstEntityInfo(void)
{
   return &(entityInfoArray[0]);
}


const VosEntityInfo *vosEid_getEntityInfo(VosEntityId eid)
{
   UINT32 i=0;

   while (i < NUM_ENTITY_INFO_ENTRIES)
   {
      if (entityInfoArray[i].eid == eid)
      {
         return (&entityInfoArray[i]);
      }

      i++;
   }

   return NULL;
}


const VosEntityInfo *vosEid_getEntityInfoByAccessBit(UINT16 bit)
{
   UINT32 i=0;

   if (bit == 0)
   {
      return NULL;
   }

   while (i < NUM_ENTITY_INFO_ENTRIES)
   {
      if (entityInfoArray[i].accessBit == bit)
      {
         return (&entityInfoArray[i]);
      }

      i++;
   }

   return NULL;
}


const VosEntityInfo *vosEid_getEntityInfoByStringName(const char *name)
{
   UINT32 i=0;

   if (name == NULL)
   {
      vosLog_error("name is NULL");
      return NULL;
   }

   while (i < NUM_ENTITY_INFO_ENTRIES)
   {
      if (entityInfoArray[i].name && !strcmp(entityInfoArray[i].name, name))
      {
         return (&entityInfoArray[i]);
      }

      i++;
   }

   return NULL;
}


VOS_RET_E vosEid_getStringNamesFromBitMask(UINT16 bitMask, char **buf)
{
   UINT32 i, mask;
   UINT32 len=1; /* for empty mask, return a buffer with an empty string. */
   UINT32 idx=0;
   UINT32 numBits = sizeof(bitMask) * 8;
   const VosEntityInfo *info;
   UBOOL8 firstName=TRUE;
   VOS_RET_E ret = VOS_RET_SUCCESS;

   /* first loop calculates how much space needed for string names */
   for (mask=1, i=0; i < numBits; i++)
   {
      info = vosEid_getEntityInfoByAccessBit(bitMask & mask);
      if (info == NULL)
      {
         if (bitMask & mask)
         {
            vosLog_error("unrecognized bitmask 0x%x", (bitMask & mask));
            ret = VOS_RET_SUCCESS_UNRECOGNIZED_DATA_IGNORED;
         }
      }
      else
      {
         len += strlen(info->name) + 1;
      }

      mask = mask << 1;
   }

   if (((*buf) = VOS_MALLOC_FLAGS(len, ALLOC_ZEROIZE)) == NULL)
   {
      vosLog_error("VOS_MALLOC_FLAGS failed");
      return VOS_RET_RESOURCE_EXCEEDED;
   }

   /* this loop copies string names into buffer */
   for (mask=1, i=0; i < numBits; i++)
   {
      info = vosEid_getEntityInfoByAccessBit(bitMask & mask);
      if (info != NULL)
      {
         if (firstName)
         {
            idx = UTIL_SNPRINTF((*buf), len, "%s", info->name);
            firstName = FALSE;
         }
         else
         {
            idx += UTIL_SNPRINTF(&((*buf)[idx]), len - idx, ",%s", info->name);
         }
      }

      mask = mask << 1;
   }

   utilAst_assert(idx < len);

   return ret;
}



VOS_RET_E vosEid_getBitMaskFromStringNames(const char *buf, UINT16 *bitMask)
{
   const char *start;
   const char *end;
   const VosEntityInfo *info;
   VOS_RET_E ret = VOS_RET_SUCCESS;

   if (bitMask == NULL)
   {
      vosLog_error("bitMask is NULL");
      return VOS_RET_INVALID_ARGUMENTS;
   }

   *bitMask = 0;

   if ((buf == NULL) || (strlen(buf) == 0))
   {
      /* null or empty string means no bits are set */
      return VOS_RET_SUCCESS;
   }

   start = buf;
   end = strchr(start, ',');
   while (end != NULL)
   {
      char name[BUFLEN_256]; /* this should be long enough to hold string names */

      utilAst_assert((end - start + 1) < (SINT32) sizeof(name));
      snprintf(name, end - start + 1, "%s", start);
      info = vosEid_getEntityInfoByStringName(name);
      if (info == NULL)
      {
         vosLog_debug("ignoring name %s", name);
         ret = VOS_RET_SUCCESS_UNRECOGNIZED_DATA_IGNORED;
      }
      else
      {
         (*bitMask) |= info->accessBit;
      }

      start = end+1;
      while ((*start == ' ') && (*start != 0))
      {
         start++;
      }

      if (*start != 0)
      {
         end = strchr(start, ',');
      }
      else
      {
         end = NULL;
      }
   }

   /* there is one more name at the end (with no trailing comma) */
   info = vosEid_getEntityInfoByStringName(start);
   if (info == NULL)
   {
      vosLog_debug("ignoring name %s", start);
      ret = VOS_RET_SUCCESS_UNRECOGNIZED_DATA_IGNORED;
   }
   else
   {
      (*bitMask) |= info->accessBit;
   }



   return ret;
}


SINT32 vosEid_getPid(void)
{
   return (oal_getPid());
}


VosEntityId vosEid_addDynamicEntityInfo(const char *appName, const char *args)
{
    UINT32 i = 0;
    const char *name = NULL;

    if (NULL == appName)
    {
        vosLog_error("appName is NULL");
        return EID_INVALID;
    }

    vosLog_debug("Add app %s to array", appName);

    for (i = 0; i < NUM_ENTITY_INFO_ENTRIES; i++)
    {
        if (entityInfoArray[i].eid >= EID_DYNAMIC_BASE)
        {
            if (0 == util_strlen(entityInfoArray[i].name))
            {
                break;
            }
        }
    }

    if (i == NUM_ENTITY_INFO_ENTRIES)
    {
        vosLog_error("No available space for dynamic app");
        return EID_INVALID;
    }

    name = strrchr(appName, '/');
    if (name)
    {
        name++;
    }
    else
    {
        name = appName;
    }

    entityInfoArray[i].isFeatureCompiledIn = TRUE;
    entityInfoArray[i].flags = EIF_NONE;

    VOS_MEM_REPLACE_STRING(entityInfoArray[i].name, name);
    if (NULL == entityInfoArray[i].name)
    {
        vosLog_error("VOS_STRDUP name failed for %s", appName);
        return EID_INVALID;
    }

    VOS_MEM_REPLACE_STRING(entityInfoArray[i].path, appName);
    if (NULL == entityInfoArray[i].path)
    {
        vosLog_error("VOS_STRDUP path failed for %s", appName);
        VOS_MEM_FREE_BUF_AND_NULL_PTR(entityInfoArray[i].name);
        return EID_INVALID;
    }

    if (args)
    {
        VOS_MEM_REPLACE_STRING(entityInfoArray[i].runArgs, args);
        if (NULL == entityInfoArray[i].runArgs)
        {
            vosLog_error("VOS_STRDUP runArgs failed for %s", appName);
            VOS_MEM_FREE_BUF_AND_NULL_PTR(entityInfoArray[i].name);
            VOS_MEM_FREE_BUF_AND_NULL_PTR(entityInfoArray[i].path);
            return EID_INVALID;
        }
    }

    vosLog_debug("Add app %s, eid %d to array[%u]",
        appName, entityInfoArray[i].eid, i);

    return entityInfoArray[i].eid;

}


VOS_RET_E vosEid_delDynamicEntityInfo(const char * appName)
{
    UINT32 i = 0;
    
    if (NULL == appName)
    {
        vosLog_error("appName is NULL");
        return VOS_RET_INVALID_ARGUMENTS;
    }

    vosLog_debug("Del app %s from array", appName);

    for (i = 0; i < NUM_ENTITY_INFO_ENTRIES; i++)
    {
        if (entityInfoArray[i].eid >= EID_DYNAMIC_BASE)
        {
            if (!util_strcmp(entityInfoArray[i].path, appName))
            {
                vosLog_debug("found app %s(%u) in array[%u]",
                    appName, entityInfoArray[i].eid, i);

                entityInfoArray[i].isFeatureCompiledIn = FALSE;
                entityInfoArray[i].flags = EIF_NONE;

                VOS_MEM_FREE_BUF_AND_NULL_PTR(entityInfoArray[i].name);
                VOS_MEM_FREE_BUF_AND_NULL_PTR(entityInfoArray[i].path);
                VOS_MEM_FREE_BUF_AND_NULL_PTR(entityInfoArray[i].runArgs);
                
                return VOS_RET_SUCCESS;
            }
        }
    }

    vosLog_error("Not found app %s in array", appName);
    return VOS_RET_OBJECT_NOT_FOUND;
}


void vosEid_init()
{
    UINT32 i = 0;
#if 0

    for (i = 0; i < NUM_ENTITY_INFO_ENTRIES; i++)
    {
        switch (entityInfoArray[i].eid)
        {
            case EID_GPONHAL:
            case EID_VOIPAGENT:
                if (SF_FEATURE_UPLINK_TYPE_GPON)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE; 
                }
                else if(SF_FEATURE_UPLINK_TYPE_EPON)
                {
                    /*set error path for not set up gpon hal in epon mode*/
                    if(entityInfoArray[i].eid == EID_GPONHAL)
                    {
                        entityInfoArray[i].path = "/usr/Sfff204/bin/hal";
                    }

                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE; 
                }
                break;
                
            case EID_TR69C:
                if (SF_FEATURE_SUPPORT_TR69C)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE; 
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE; 
                }

                if (SF_FEATURE_SUPPORT_IPV6)
                {
                    entityInfoArray[i].flags |= EIF_IPV6;
                }
                break;
                
            case EID_HTTPD:
                if (SF_FEATURE_SUPPORT_HTTPD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE; 
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE; 
                }

                if (SF_FEATURE_SUPPORT_IPV6)
                {
                    entityInfoArray[i].flags |= EIF_IPV6;
                }

#ifndef DESKTOP_LINUX
#ifdef SUPPORT_HTTPD_SSL
                if (SF_FEATURE_SUPPORT_HTTPD_SSL)
                {
                    entityInfoArray[i].port = HTTPD_SSL_PORT;
                }
#endif
#endif
                break;

            case EID_SIPALG:
                if (SF_FEATURE_SUPPORT_ALG_SIPROXD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE; 
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE; 
                }
                break;

            case EID_PPPOE_SERVER:
                if (SF_FEATURE_SUPPORT_RTP_ROX)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_FTPD:
                if (SF_FEATURE_SUPPORT_FTPD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }

                if (SF_FEATURE_SUPPORT_IPV6)
                {
                    entityInfoArray[i].flags |= EIF_IPV6;
                }
                break;

            case EID_TELNETD:
                if (SF_FEATURE_SUPPORT_TELNETD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }

                if (SF_FEATURE_SUPPORT_IPV6)
                {
                    entityInfoArray[i].flags |= EIF_IPV6;
                }
                break;

            case EID_SSHD:
                if (SF_FEATURE_SUPPORT_SSHD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }

                if (SF_FEATURE_SUPPORT_IPV6)
                {
                    entityInfoArray[i].flags |= EIF_IPV6;
                }
                break;

            case EID_SAMBA:
                if (SF_FEATURE_SUPPORT_SAMBA)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_SNMPD:
                if (SF_FEATURE_SUPPORT_SNMP)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_DNSPROXY:
                 if (SF_FEATURE_SUPPORT_DNSPROXY)
                 {
                     entityInfoArray[i].isFeatureCompiledIn = TRUE;
                 }
                 else
                 {
                     entityInfoArray[i].isFeatureCompiledIn = FALSE;
                 }
                 break;
                 
            case EID_DMSD:
                if (SF_FEATURE_SUPPORT_DLNA)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_DHCPC:
            case EID_DHCPD:
                if (SF_FEATURE_SUPPORT_DHCP)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;
    
             case EID_MCPD:
             case EID_MCPCTL:
                if (SF_FEATURE_SUPPORT_MCAST || SF_FEATURE_SUPPORT_MCAST_MLD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

             case EID_UPNP:
                if (SF_FEATURE_SUPPORT_UPNP)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

             case EID_HOTPLUG:
                if (SF_FEATURE_SUPPORT_USB_STORAGESERVICE)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;
 
            case EID_TFTPD:
                if (SF_FEATURE_SUPPORT_TFTPD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                
                if (SF_FEATURE_SUPPORT_IPV6)
                {
                    entityInfoArray[i].flags |= EIF_IPV6;
                }
                break;
                
            case EID_DHCP6C:
            case EID_DHCP6S:
            case EID_RADVD:
            case EID_RASTATUS6:
            case EID_IPV6MON:
                if (SF_FEATURE_SUPPORT_IPV6)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_EPON_APP:
                if (SF_FEATURE_UPLINK_TYPE_EPON)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_MMED:
                if (SF_FEATURE_UPLINK_TYPE_EOC)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_CTCSTP:
                if (SF_FEATURE_SUPPORT_CT_LOOPDETECT)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;
                
            case EID_VODSL:
                if (SF_FEATURE_SUPPORT_VOIP)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_SYSLOGD:
            case EID_KLOGD:
                if (SF_FEATURE_SUPPORT_SYSLOG)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_DDNSD:
                if (SF_FEATURE_SUPPORT_DDNS)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_SNTP:
                if (SF_FEATURE_SUPPORT_SNTP)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_URLFILTERD:
                if (SF_FEATURE_SUPPORT_URLFILTER)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_FTP:
                if (SF_FEATURE_SUPPORT_FTPD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_PING:
                if (SF_FEATURE_SUPPORT_IPPING)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_TFTP:
                if (SF_FEATURE_SUPPORT_TFTPD)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;

            case EID_IPPD:
                if (SF_FEATURE_SUPPORT_IPP)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;
                
            case EID_L2TPD:
                if (SF_FEATURE_SUPPORT_L2TPAC)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }
                break;
            case EID_MONITORCOLLECTOR:
                if (SF_FEATURE_SUPPORT_MONITOR_COLLECTOR)
                {
                    entityInfoArray[i].isFeatureCompiledIn = TRUE;
                }
                else
                {
                    entityInfoArray[i].isFeatureCompiledIn = FALSE;
                }                
                break;
        
            default:
                break;
        }
    }
#endif
}


VOS_RET_E vosEid_setServerPort(VosEntityId eid, UINT16 port)
{
    UINT32 i = 0;
    
    for (i = 1; i < NUM_ENTITY_INFO_ENTRIES; i++)
    {
        if (entityInfoArray[i].eid == eid)
        {
            entityInfoArray[i].port = port;
            break;
        }
    }

    return VOS_RET_SUCCESS;
}
