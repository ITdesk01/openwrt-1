#include "basic.h"


// ������ļ����ṩ�ӿ�api �� websock �� zigbee ��Ϣ������߳� ���е���


 /*
 ���ݵ�ַ�����豸
 �����: list_head ָ���ĸ��б� Ŀǰ������ global_searchedDeviceEntryList_head �� global_ManagedDeviceEntryList_head
         input_ieee_addr, nw_addr ,ֻ��Ҫƥ��һ���Ϳɷ��أ�
 ���� ��� Ϊ 
 ���ҵ����򷵻� һ��ָ����ڴ��ָ�룬���Ժ���ʹ���߳��Ƿǳ����ţ����򲻽���ȥ�޸��������ݣ����ⲻҪȥfree it
 ���ݵ�ַ�����豸
 ��û�ҵ����򷵻�NULL, ���Ե�������Ҫ���ж�
*/
struct simpleDeviceEntry * GetDevInfoByAddr( struct simpleDeviceEntry *input_list_head, char * input_ieee_addr, int nw_addr)
{
    DEBUG_PRINTF("===[%s]====input_list_head: 0x %x===== input_ieee_addr: %s === nw_addr: %d ====\n", __func__, input_list_head,input_ieee_addr,nw_addr);
    
    if( input_list_head == NULL)
    {
        return NULL;
    }
    if( input_list_head == global_ManagedDeviceEntryList_head )
    {
        return findManagedDeviceEntryByAddr(input_ieee_addr, nw_addr);
    }
    else if (input_list_head == global_searchedDeviceEntryList_head)
    {
        return findSearchedDeviceEntryByAddr(input_ieee_addr, nw_addr);
    }
    else
    {
        printf("====[%s] the input is wrong ====\n", __func__);
        return NULL;
    }
}

/*
�����豸id �������豸
*/
struct simpleDeviceEntry * GetDevInfoById(struct simpleDeviceEntry *input_list_head, char *input_deviceid)
{
    DEBUG_PRINTF("===[%s]====input_list_head: 0x %x === input_deviceid: %s =====\n",__func__,input_list_head, input_deviceid);

    if(input_list_head == NULL)
    {
        return NULL;
    }

    if(input_list_head == global_ManagedDeviceEntryList_head )
    {
        return findManagedDeviceEntryByDeviceId(input_deviceid);
    }
    else if(input_list_head == global_searchedDeviceEntryList_head )
    {
        return findSearchedDeviceEntryByDeviceId(input_deviceid);
    }
    else
    {
        printf("===[%s] the input is wrong ====\n", __func__);
        return NULL;
    }
}

//���һ���豸�������б�
//�����:
// input_entry ��ջ�ϵ��ڴ棬
// ����ֵ0 Ϊ�ɹ�
int AddDeviceInfo2SearchedDeviceList(struct simpleDeviceEntry *input_entry)
{
    DEBUG_PRINTF("===[%s] ====\n", __func__);
    PrintSimpleDeviceEntry(input_entry);
    struct simpleDeviceEntry *newentry = malloc_simpleDeviceEntry();
    strcpy(newentry->deviceid,input_entry->deviceid);
    newentry->type = input_entry->type;
    strcpy(newentry->name, input_entry->name);
    newentry->status =input_entry->status;
    strcpy(newentry->ieee_addr,input_entry->ieee_addr);
    newentry->nw_addr = input_entry->nw_addr;
    strcpy(newentry->version, input_entry->version);
    strcpy(newentry->model, input_entry->model);
    strcpy(newentry->seq, input_entry->seq);

    return AddToSearchedDeviceList(newentry);    
}

//���һ���豸�������豸�б�
//�����:
// input_entry ��ջ�ϵ��ڴ棬
// ����ֵ0 Ϊ�ɹ�
int AddDeviceInfo2ManagedDeviceList(struct simpleDeviceEntry *input_entry)
{
    DEBUG_PRINTF("===[%s] ====\n", __func__);
    struct simpleDeviceEntry *newentry = malloc_simpleDeviceEntry();
    strcpy(newentry->deviceid,input_entry->deviceid);
    newentry->type = input_entry->type;
    strcpy(newentry->name, input_entry->name);
    newentry->status =input_entry->status;
    strcpy(newentry->ieee_addr,input_entry->ieee_addr);
    newentry->nw_addr = input_entry->nw_addr;
    strcpy(newentry->version, input_entry->version);
    strcpy(newentry->model, input_entry->model);
    strcpy(newentry->seq, input_entry->seq);

    return AddToManagedDeviceList(newentry);    
}

//�ӹ����豸�б���ɾ���豸
//���: char * input_deviceid
int DelDeviceInfo2ManagedDeviceList(char *input_deviceid)
{
    DEBUG_PRINTF("===[%s]====input_deviceid:%s ===\n",__func__, input_deviceid);

    return RemoveFromManagedDeviceList(input_deviceid);
}

//���� �����豸�б�
int ClearDevSearchList()
{
    DEBUG_PRINTF("====[%s]=====\n",__func__);
    return RefreshSearchedDeviceList();
}

//���豸����
int RenameDevName(char *input_devid, char *input_name)
{
    DEBUG_PRINTF("===[%s]===input_devid:%s, input_name:%s===\n",__func__,input_devid,input_name);
    struct simpleDeviceEntry* result = findManagedDeviceEntryByDeviceId(input_devid);
    if(result == NULL)
    {
        printf("====[%s]=== can't find the match device===\n",__func__);
        return -1;
    }
    else
    {
        memset(result->name,0,sizeof(result->name));
        strcpy(result->name,input_name);
        UpdateEntryToManagedDeviceTable(result);
    }
    return 0;
}

//���ָ��
int AddFingerPrint(char *input_devid, char *input_userid, char *input_fingerprintid)
{
    DEBUG_PRINTF("===[%s]====input_devid:%s, input_userid: %s, fingerprintid: %s ==== \n", __func__,input_devid, input_userid, input_fingerprintid);

    struct FingerPrintEntry *newentry= malloc_fingerPrintEntry();
    strcpy(newentry->deviceid,input_devid);
    strcpy(newentry->userid, input_userid);
    strcpy(newentry->fingerprintid,input_fingerprintid);
    int rownum= getMaxRowIdFromDatabase("fingerPrint_table")+1;
    DEBUG_PRINTF("==[%s]=== rownum is %d===\n",__func__,rownum);
    snprintf(newentry->name,64,"fingerprint%d",rownum);
    DEBUG_PRINTF("==[%s]===name: %s===\n",__func__,newentry->name);
    return AddToFingerPrintEntryList(newentry);
}

//ɾ��ָ��
int DelFingerPrint(char *input_devid, char *input_userid, char *input_fingerprintid)
{
    DEBUG_PRINTF("==[%s]===input_devid:%s, input_userid:%s, input_fingerprintid: %s ===\n", __func__,input_devid,input_userid,input_fingerprintid);

    return RemoveFromFingerPrinterEntryList(input_fingerprintid, input_devid);
}

//rename ָ��
int RenameFingerPrint(char *input_devid, char *input_userid, char *input_fingerprintid, char *input_fingerprintname)
{
    DEBUG_PRINTF("===[%s]===input_devid:%s, input_userid:%s, input_fingerprintid:%s, input_fingerprintname:%s===\n",__func__,input_devid,input_userid,input_fingerprintid,input_fingerprintname);
    struct FingerPrintEntry *result =findFingerPrintEntry(input_fingerprintid,input_devid);
    if(result == NULL)
    {
        printf("====[%s]=== can't find the match fingerprint===\n",__func__);
        return -1;
    }
    else
    {
        if(strcmp(result->userid, input_userid) != 0)
        {
            printf("===[%s]=== the user id is wrong ===\n",__func__);
            return -1;
        }
        memset(result->name,0,sizeof(result->name));
        strcpy(result->name,input_fingerprintname);
        UpdateEntryToFingerPrintTable(result);
    }
    return 0;
}

//��ȡĳһ�û���ĳһ�豸�µ�����ָ�Ƶ���Ϣ
//���: buf ָ��һ���㹻���ջ�ϵ��ڴ������洢������ṹΪ����
//���� ����ĸ���
//-1 �������
int GetFingerPrintsByUserIdDeviceId(char *input_devid, char* input_userid, struct FingerPrintEntry* buf)
{
    DEBUG_PRINTF("==[%s] === input_devid: %s , input_userid: %s ===\n", __func__,input_devid,input_userid);
    int count =0;

    if(global_FingerPrintEntryList_head == NULL)
    {
        DEBUG_PRINTF("==[%s]=== global_FingerPrintEntryList is null ===\n",__func__);
        return 0;
    }

    struct FingerPrintEntry* tmp = global_FingerPrintEntryList_head;

    while(tmp!=NULL)
    {
        if( (strcmp(tmp->deviceid,input_devid)==0) && (strcmp(tmp->userid,input_userid)==0) )
        {
           strcpy(buf[count].fingerprintid, tmp->fingerprintid);
           strcpy(buf[count].name,tmp->name);
           strcpy(buf[count].deviceid,tmp->deviceid);
           strcpy(buf[count].userid,tmp->userid);
           count++;
        }
        tmp=tmp->root.next;
    }

    return count;
}

//����log �����ػ�������ݿ�
int savelog2local(char *input_time, int opratetype, char * input_usrid, char * devid)
{
    DEBUG_PRINTF("===[%s]===input_time:%s, opratetype:%d, input_usrid: %s, devid:%s ===\n",__func__,input_time,opratetype,input_usrid,devid);
    struct LogEntry *newentry = malloc_logEntry();
    strcpy(newentry->time,input_time);
    newentry->opratetype=opratetype;
    strcpy(newentry->userid, input_usrid);
    strcpy(newentry->devid,devid);

    return AddToLogEntryList(newentry);
}

//��ȡ����ĵ�һ��logEntry
struct LogEntry *getFirstLog()
{
    DEBUG_PRINTF("===[%s]=====\n",__func__);
    return global_LogEntryList_head;
}

//ɾ���ڴ���ĵ�һ��log
int DelFirstLog()
{
    DEBUG_PRINTF("===[%s]=====\n",__func__);
    return      RemoveFirstEntryFromLogEntryList();
}
