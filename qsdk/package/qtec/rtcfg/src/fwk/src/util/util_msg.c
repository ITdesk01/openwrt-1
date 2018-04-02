#include "fwk.h"


static VOS_RET_E util_sendRequest(void *msgHandle,
                                  VosEntityId eid,
                                  VosMsgType msgType,
                                  UINT32 wordData,
                                  const void *msgData,
                                  UINT32 msgDataLen)
{
    VosMsgHeader *msg;
    void *msgBuf;
    VOS_RET_E ret;

    if (msgData != NULL && msgDataLen != 0)
    {
        msgBuf = VOS_MALLOC_FLAGS(sizeof(VosMsgHeader) + msgDataLen, ALLOC_ZEROIZE);
    } 
    else
    {
        msgBuf = VOS_MALLOC_FLAGS(sizeof(VosMsgHeader), ALLOC_ZEROIZE);
    }

    msg = (VosMsgHeader *)msgBuf;
    if (NULL == msg)
    {
        vosLog_error("VOS_MALLOC_FLAGS fail");
        return VOS_RET_RESOURCE_EXCEEDED;
    }

    msg->type = msgType;
    msg->src = vosMsg_getHandleEid(msgHandle);
    msg->dst = eid;
    msg->flags_request = 1;
    msg->wordData = wordData;

    if (msgData != NULL && msgDataLen != 0)
    {
        msg->dataLength = msgDataLen;
        memcpy((char *) (msg + 1), (char *)msgData, msgDataLen);
    }      

    ret = vosMsg_sendAndGetReplyWithTimeout(msgHandle, msg, 5 * 60 * MSECS_IN_SEC);

    vosLog_debug("Send msg 0x%x from 0x%x to smd, ret=%d",
                 msgType,
                 vosMsg_getHandleEid(msgHandle),
                 ret);

    VOS_FREE(msgBuf);

    return ret;
}


static VOS_RET_E util_sendEventMsg(void *msgHandle,
                                VosEntityId eid,
                                VosMsgType msgType,
                                UINT32 wordData,
                                const void *msgData,
                                UINT32 msgDataLen,
                                UBOOL8 isEvent)
{
    VosMsgHeader *msg;
    void *msgBuf;
    VOS_RET_E ret;

    if (msgData != NULL && msgDataLen != 0)
    {
        msgBuf = VOS_MALLOC_FLAGS(sizeof(VosMsgHeader) + msgDataLen, ALLOC_ZEROIZE);
    } 
    else
    {
        msgBuf = VOS_MALLOC_FLAGS(sizeof(VosMsgHeader), ALLOC_ZEROIZE);
    }

    msg = (VosMsgHeader *)msgBuf;
    if (NULL == msg)
    {
        vosLog_error("VOS_MALLOC_FLAGS fail");
        return VOS_RET_RESOURCE_EXCEEDED;
    }

    msg->type = msgType;
    msg->src = vosMsg_getHandleEid(msgHandle);
    msg->dst = eid;
    msg->flags_event = isEvent;
    msg->wordData = wordData;

    if (msgData != NULL && msgDataLen != 0)
    {
        msg->dataLength = msgDataLen;
        memcpy((char *) (msg + 1), (char *)msgData, msgDataLen);
    }      

    ret = vosMsg_send(msgHandle, msg);
    if (ret != VOS_RET_SUCCESS)
    {
        vosLog_error("Send msg 0x%x from 0x%x to smd fail, ret=%d",
                     msgType,
                     vosMsg_getHandleEid(msgHandle),
                     ret);
    }
    else
    {
        vosLog_debug("Send msg 0x%x from 0x%x to smd succeeded",
                     msgType,
                     vosMsg_getHandleEid(msgHandle));
    }

    VOS_FREE(msgBuf);

    return ret;
}


VOS_RET_E UTIL_sendRequestToSmd(void *msgHandle,
                                VosMsgType msgType,
                                UINT32 wordData,
                                const void *msgData,
                                UINT32 msgDataLen)
{
    return util_sendRequest(msgHandle,
                            EID_SMD,
                            msgType,
                            wordData,
                            msgData,
                            msgDataLen);
}


VOS_RET_E UTIL_sendEventToSmd(void *msgHandle,
                            VosMsgType msgType,
                            UINT32 wordData,
                            const void *msgData,
                            UINT32 msgDataLen)
{
    return util_sendEventMsg(msgHandle,
                          EID_SMD,
                          msgType,
                          wordData,
                          msgData,
                          msgDataLen,
                          TRUE);
}


VOS_RET_E UTIL_sendHeartbeat(void *msgHandle)
{
    return util_sendEventMsg(msgHandle,
                          EID_SMD,
                          VOS_MSG_WATCHDOG_HEARTBEAT,
                          0,
                          NULL,
                          0,
                          FALSE);
}

VOS_RET_E UTIL_stopWatchdog(void *msgHandle)
{
    return util_sendEventMsg(msgHandle,
                          EID_SMD,
                          VOS_MSG_WATCHDOG_STOP,
                          0,
                          NULL,
                          0,
                          FALSE);
}


VOS_RET_E UTIL_sendRequestToSsk(void *msgHandle,
                                VosMsgType msgType,
                                UINT32 wordData,
                                const void *msgData,
                                UINT32 msgDataLen)
{
    return util_sendRequest(msgHandle,
                            EID_SSK,
                            msgType,
                            wordData,
                            msgData,
                            msgDataLen);
}


VOS_RET_E UTIL_sendEventToSsk(void *msgHandle,
                            VosMsgType msgType,
                            UINT32 wordData,
                            const void *msgData,
                            UINT32 msgDataLen)
{
    return util_sendEventMsg(msgHandle,
                          EID_SSK,
                          msgType,
                          wordData,
                          msgData,
                          msgDataLen,
                          TRUE);
}


VOS_RET_E UTIL_registerEvent(void *msgHandle,
                             VosMsgType eventType,
                             const void *matchData,
                             UINT32 matchDataLen)
{
    return UTIL_sendRequestToSmd(msgHandle,
                                 VOS_MSG_REGISTER_EVENT_INTEREST,
                                 eventType,
                                 matchData,
                                 matchDataLen);
}


VOS_RET_E UTIL_unregisterEvent(void *msgHandle,
                               VosMsgType eventType,
                               const void *matchData,
                               UINT32 matchDataLen)
{
    return UTIL_sendRequestToSmd(msgHandle,
                                 VOS_MSG_UNREGISTER_EVENT_INTEREST,
                                 eventType,
                                 matchData,
                                 matchDataLen);
}

#if 0
VOS_RET_E UTIL_reboot(void *msgHandle)
{
    if (SF_FEATURE_SUPPORT_SYSLOG)
    {
        syslog(LOG_WARNING,"104001 System Reboot\n");
        util_saveLogToFlash(msgHandle);
        
        /*waiting the security log be flushed
        one second is not enough*/
        sleep(3);
    }
    
    return UTIL_sendRequestToSmd(msgHandle,
                                 VOS_MSG_REBOOT_SYSTEM,
                                 0,
                                 NULL,
                                 0);
}
#endif


VOS_RET_E UTIL_addEntityInfo(VosEntityInfoMsg *eInfo, void *msgHandle)
{
    return UTIL_sendRequestToSmd(msgHandle,
                                 VOS_MSG_ADD_ENTITY_INFO,
                                 0,
                                 (void *)eInfo,
                                 sizeof(VosEntityInfoMsg));
}


VOS_RET_E UTIL_delEntityInfo(const char *appName, void *msgHandle)
{
    return UTIL_sendRequestToSmd(msgHandle,
                                 VOS_MSG_DEL_ENTITY_INFO,
                                 0,
                                 (void *)appName,
                                 util_strlen(appName) + 1);
}

VosEntityId UTIL_getEidByAppName(const char *appName, void *msgHandle)
{
    return UTIL_sendRequestToSmd(msgHandle,
                                 VOS_MSG_GET_EID_FROM_NAME,
                                 0,
                                 (void *)appName,
                                 util_strlen(appName) + 1);
}


VOS_RET_E UTIL_sendRequestToGponproxy(void *msgHandle,
                                      VosMsgType msgType,
                                      UINT32 wordData,
                                      const void *msgData,
                                      UINT32 msgDataLen)
{
    return util_sendEventMsg(msgHandle,
                          EID_GPONHAL,
                          msgType,
                          wordData,
                          msgData,
                          msgDataLen,
                          TRUE);
}

VOS_RET_E UTIL_sendRequestToEponapp(void *msgHandle,
                                      VosMsgType msgType,
                                      UINT32 wordData,
                                      const void *msgData,
                                      UINT32 msgDataLen)
{
    return util_sendEventMsg(msgHandle,
                          EID_EPON_APP,
                          msgType,
                          wordData,
                          msgData,
                          msgDataLen,
                          TRUE);
}



VOS_RET_E UTIL_sendRequestToSnmpd(void *msgHandle,
                                      VosMsgType msgType,
                                      UINT32 wordData,
                                      const void *msgData,
                                      UINT32 msgDataLen)
{
    return util_sendEventMsg(msgHandle,
                          EID_SNMPD,
                          msgType,
                          wordData,
                          msgData,
                          msgDataLen,
                          TRUE);
}

