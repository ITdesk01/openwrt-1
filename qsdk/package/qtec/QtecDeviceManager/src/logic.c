#include "basic.h"
#include "logic.h"

struct simpleDeviceEntry *global_searchedDeviceEntryList_head=NULL;
struct simpleDeviceEntry *global_searchedDeviceEntryList_tail=NULL;

//���ݵ�ַ����global_searchedDeviceEntryList����ұ���
struct simpleDeviceEntry* findSearchedDeviceEntryByAddr(char *ieee_addr, int nw_addr)
{
    DEBUG_PRINTF("====[%s]=========\n",__func__);
    
    if(global_searchedDeviceEntryList_head == NULL)
    {
        DEBUG_PRINTF("====[%s]====global_searchedDeviceEntryList is null ===\n",__func__);   
        return NULL;
    }
    struct simpleDeviceEntry *tmp=global_searchedDeviceEntryList_head;
    
    while(tmp !=NULL)
    {
        if( (strcmp(tmp->ieee_addr,ieee_addr) == 0) || (tmp->nw_addr == nw_addr) )
        {
            DEBUG_PRINTF("===[%s]=== found entry: entry address is 0x %x ; ieee_addr is %s ; nw_addr is %d ====\n", __func__,tmp,tmp->ieee_addr, tmp->nw_addr);
            return tmp;
        }
        tmp=tmp->root.next;
    }
    return NULL;
}

//����ָ��device id ��global_searchedDeviceEntryList �� ���ұ���
//��û�ҵ�����NULL,�ҵ��򷵻�entry ��ַ��
struct simpleDeviceEntry* findSearchedDeviceEntryByDeviceId(char *deviceid)
{
    DEBUG_PRINTF("=====[%s]=========deviceid:%s ===\n",__func__,deviceid);
    
    if(global_searchedDeviceEntryList_head == NULL)
    {
        DEBUG_PRINTF("====[%s]====global_searchedDeviceEntryList is null ===\n",__func__);   
        return NULL;
    }
    struct simpleDeviceEntry *tmp=global_searchedDeviceEntryList_head;
    
    while(tmp !=NULL)
    {
        DEBUG_PRINTF("[%s]====tmp->deviceid:%s===\n",__func__,tmp->deviceid);
        if(strcmp(tmp->deviceid,deviceid) == 0 )
        {
            DEBUG_PRINTF("===[%s]=== found entry: entry address is 0x %x ; deviceid is %s====\n", __func__,tmp,deviceid);
            return tmp;
        }
        tmp=tmp->root.next;
    }
    return NULL;
}

//���һ���豸���ѷ����豸�б�
//input �Ǹ��ѷ���ռ���ڴ�
//���input��listĳ��entry�ظ�����free it.
int AddToSearchedDeviceList(struct simpleDeviceEntry *input)
{
    DEBUG_PRINTF("===[%s]=====\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct simpleDeviceEntry *result=NULL;
    result = findSearchedDeviceEntryByDeviceId(input->deviceid);
    if(result == NULL)
    {
        DEBUG_PRINTF("====[%s]: add new entry into searchedDevice====\n",__func__);
    
        qtec_insert_list((struct qtec_list *)input,(struct qtec_list **) &global_searchedDeviceEntryList_head, (struct qtec_list **) &global_searchedDeviceEntryList_tail);
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in searchedDevice List===\n",__func__);
        if(input != NULL)
        {
            free_simpleDeviceEntry(input);
        }
        return 1;
    }
    return 0;
}


//ˢ���ѷ����豸�б�(������0)
int RefreshSearchedDeviceList()
{
    DEBUG_PRINTF("======[%s]======\n",__func__);
    if(global_searchedDeviceEntryList_head == NULL)
    {
        return 0;
    }

    struct simpleDeviceEntry *tmp = global_searchedDeviceEntryList_head;
    struct simpleDeviceEntry *tmp2 = NULL;
    while(tmp->root.next!=NULL)
    {
        tmp2=tmp->root.next;
        free_simpleDeviceEntry(tmp);
        tmp = tmp2;
    }
    free_simpleDeviceEntry(tmp);
    
    global_searchedDeviceEntryList_head =NULL;
    global_searchedDeviceEntryList_tail =NULL;
    
}


struct simpleDeviceEntry *global_ManagedDeviceEntryList_head=NULL;
struct simpleDeviceEntry *global_ManagedDeviceEntryList_tail=NULL;

//���ݵ�ַ����global_ManagedDeviceEntryList����ұ���
struct simpleDeviceEntry* findManagedDeviceEntryByAddr(char *ieee_addr, int nw_addr)
{
    DEBUG_PRINTF("====[%s]=========\n",__func__);
    
    if(global_ManagedDeviceEntryList_head == NULL)
    {
        DEBUG_PRINTF("====[%s]====global_ManagedDeviceEntryList is null ===\n",__func__);   
        return NULL;
    }
    struct simpleDeviceEntry *tmp=global_ManagedDeviceEntryList_head;
    
    while(tmp !=NULL)
    {
        if( (strcmp(tmp->ieee_addr,ieee_addr) == 0) || (tmp->nw_addr == nw_addr) )
        {
            DEBUG_PRINTF("===[%s]=== found entry: entry address is 0x %x ; ieee_addr is %s ; nw_addr is %d ====\n", __func__,tmp,tmp->ieee_addr, tmp->nw_addr);
            return tmp;
        }
        tmp=tmp->root.next;
    }
    return NULL;
}

//����ָ��device id ��global_ManagedDeviceEntryList �� ���ұ���
//��û�ҵ�����NULL,�ҵ��򷵻�entry ��ַ��
struct simpleDeviceEntry* findManagedDeviceEntryByDeviceId(char *deviceid)
{
    DEBUG_PRINTF("=====[%s]============\n",__func__);
    
    if(global_ManagedDeviceEntryList_head == NULL)
    {
        DEBUG_PRINTF("====[%s]====global_ManagedDeviceEntryList is null ===\n",__func__);   
        return NULL;
    }
    struct simpleDeviceEntry *tmp=global_ManagedDeviceEntryList_head;
    
    while(tmp !=NULL)
    {
        
        if(strcmp(tmp->deviceid,deviceid) == 0 )
        {
            DEBUG_PRINTF("===[%s]=== found entry: entry address is 0x %x ; deviceid is %s====\n", __func__,tmp,deviceid);
            return tmp;
        }
        tmp=tmp->root.next;
    }
    return NULL;
}

//���һ���豸���ѷ����豸�б�
//input �Ǹ��ѷ���ռ���ڴ�
//���input��listĳ��entry�ظ�����free it.
//����ֵ: 0 ����ɹ�
//        1 ����û�����б����ҵ�
//        -1 �������������� �����ݿ��������
int AddToManagedDeviceList(struct simpleDeviceEntry *input)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct simpleDeviceEntry *tmp_result= findManagedDeviceEntryByDeviceId(input->deviceid);
    if(tmp_result == NULL)
    {
        DEBUG_PRINTF("====[%s]: add new entry into ManagedDevice List====\n",__func__);

        //��ִ�����ݿ��������������ɹ������ٶ�������в���
        int result = 0;
        result = AddNewEntrytoManagedDeviceTable(input);

        if(result != 0)
        {
            printf("===[%s]: add entry into database fail =====\n",__func__);
            return -1;
        }
        else
        {
            qtec_insert_list((struct qtec_list *)input,(struct qtec_list **) &global_ManagedDeviceEntryList_head, (struct qtec_list **) &global_ManagedDeviceEntryList_tail);

        }
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in ManagedDevice List===\n",__func__);
        if(input != NULL)
        {
            free_simpleDeviceEntry(input);
        }
        return 1;
    }
    return 0;
}


//ɾ��һ���豸���ѷ����豸�б�
//input �Ǹ��ѷ���ռ���ڴ�
//���input��listĳ��entry�ظ�����free it.
int RemoveFromManagedDeviceList(char* input_deviceid)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input_deviceid == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct simpleDeviceEntry *output_result= NULL;
    output_result = findManagedDeviceEntryByDeviceId(input_deviceid);
    if(output_result== NULL)
    {
        DEBUG_PRINTF("====[%s]: this entry is not in ManagedDeviceEntryList====\n",__func__);
        
        return 1;  
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in ManagedDevice List, so remove it===\n",__func__);

        //��ִ�����ݿ�������ٶ�������в���
        int result=0;
        result=DelEntryFromManagedDeviceTable(output_result->deviceid);
        if(result != 0)
        {
            printf("====[%s]: del entry from database fail====\n", __func__);
            
            return -1;
        }
        else
        {
            //��ͬ��deviceid ��entry ���б���ɾ��
            qtec_remove_list((struct qtec_list *)output_result, (struct qtec_list * *) &global_ManagedDeviceEntryList_head, (struct qtec_list * *) &global_ManagedDeviceEntryList_tail);
            //�ͷ��ڴ�
            if(output_result!=NULL)
            {
                free_simpleDeviceEntry(output_result);
            }
        }
       
    }
    return 0;
}


//����һ���豸��Ϣ�������豸�б�
//input �Ǹ��ѷ���ռ���ڴ�
//���input��listĳ��entry�ظ�����free it.

int UpdateToManagedDeviceList(struct simpleDeviceEntry *input)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct simpleDeviceEntry *tmp_result= findManagedDeviceEntryByDeviceId(input->deviceid);
    if(tmp_result == NULL)
    {
        DEBUG_PRINTF("====[%s]: this entry not in  ManagedDevice List====\n",__func__);
        if(input != NULL)
        {
            free_simpleDeviceEntry(input);
        }
        return 1;
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in ManagedDevice List===\n",__func__);

        //�Ƚ������ݿ��������û���⣬�ٸ����ڴ�
        int result=0;
        result = UpdateEntryToManagedDeviceTable(input);

        if(result != 0)
        {
            printf("=====[%s] ==== update entry in database fail ====\n", __func__);
            if(input !=NULL)
            {
                free_simpleDeviceEntry(input);
            }
            return -1;
        }
        else
        {
            //update info in memory list
            memset(tmp_result->name,0,sizeof(tmp_result->name));
            strcpy(tmp_result->name,input->name);
            tmp_result->type=input->type;
            tmp_result->status=input->status;

            memset(tmp_result->ieee_addr,0,sizeof(tmp_result->ieee_addr));
            strcpy(tmp_result->ieee_addr,input->ieee_addr);
            tmp_result->nw_addr = input->nw_addr;

            memset(tmp_result->version,0,sizeof(tmp_result->version));
            strcpy(tmp_result->version,input->version);

            memset(tmp_result->model,0,sizeof(tmp_result->model));
            strcpy(tmp_result->model,input->model);

            memset(tmp_result->seq,0,sizeof(tmp_result->seq));
            strcpy(tmp_result->seq,input->seq);
        }
        
    }
    return 0;
}


//ά���û��б��߼�����
struct UserEntry *global_UserEntryList_head=NULL;
struct UserEntry *global_UserEntryList_tail=NULL;

//����ָ��user id ��global_UserEntryList �� ���ұ���
//��û�ҵ�����NULL,�ҵ��򷵻�entry ��ַ��
struct simpleDeviceEntry* findUserEntryByUserId(char *userid)
{
    DEBUG_PRINTF("=====[%s]============\n",__func__);
    
    if(global_UserEntryList_head == NULL)
    {
        DEBUG_PRINTF("====[%s]====global_ManagedDeviceEntryList is null ===\n",__func__);   
        return NULL;
    }
    struct UserEntry*tmp=global_UserEntryList_head;
    
    while(tmp !=NULL)
    {
        
        if(strcmp(tmp->userid, userid) == 0 )
        {
            DEBUG_PRINTF("===[%s]=== found entry: entry address is 0x %x ; userid is %s====\n", __func__,tmp, userid);
            return tmp;
        }
        tmp=tmp->root.next;
    }
    return NULL;
}

//���һ���û����û��б�
//input �Ǹ��ѷ���ռ���ڴ�
//���input��listĳ��entry�ظ�����free it.
//����ֵ: 0 ����ɹ�
//        1 ����û�����б����ҵ�
//        -1 �������������� �����ݿ��������
int AddToUserEntryList(struct UserEntry *input)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct UserEntry*tmp_result= findUserEntryByUserId(input->userid);
    if(tmp_result == NULL)
    {
        DEBUG_PRINTF("====[%s]: add new entry into UserEntry List====\n",__func__);

        //��ִ�����ݿ��������������ɹ������ٶ�������в���
        int result = 0;
        result = AddNewEntryToUserTable(input);

        if(result != 0)
        {
            printf("===[%s]: add entry into database fail =====\n",__func__);
            if(input !=NULL)
            {
                free_userEntry(input);
            }
            return -1;
        }
        else
        {
            qtec_insert_list((struct qtec_list *)input,(struct qtec_list **) &global_UserEntryList_head, (struct qtec_list **) &global_UserEntryList_tail);

        }
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in userentry List===\n",__func__);
        if(input != NULL)
        {
            free_userEntry(input);
        }
        return 1;
    }
    return 0;
}


//ɾ��һ���û����û��б�
//input �Ǹ��ѷ���ռ���ڴ�
int RemoveFromUserEntryList(char* input_userid)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input_userid == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct UserEntry* output_result= NULL;
    output_result = findUserEntryByUserId(input_userid);
    if(output_result== NULL)
    {
        DEBUG_PRINTF("====[%s]: this entry is not in userentry list====\n",__func__);
        
        return 1;  
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in userentry List, so remove it===\n",__func__);

        //��ִ�����ݿ�������ٶ�������в���
        int result=0;
        result=DelEntryFromUserTable(input_userid);
        if(result != 0)
        {
            printf("====[%s]: del entry from database fail====\n", __func__);
            
            return -1;
        }
        else
        {
            //��ͬ��deviceid ��entry ���б���ɾ��
            qtec_remove_list((struct qtec_list *)output_result, (struct qtec_list * *) &global_UserEntryList_head, (struct qtec_list * *) &global_UserEntryList_tail);
            //�ͷ��ڴ�
            if(output_result!=NULL)
            {
                free_userEntry(output_result);
            }
        }
       
    }
    return 0;
}


//����һ���û���Ϣ���û��б�
//input �Ǹ��ѷ���ռ���ڴ�
int UpdateToUserEntryList(struct UserEntry* input)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct UserEntry*tmp_result= findUserEntryByUserId(input->userid);
    if(tmp_result == NULL)
    {
        DEBUG_PRINTF("====[%s]: this entry not in  userentry List====\n",__func__);
        if(input != NULL)
        {
            free_userEntry(input);
        }
        return 1;
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in userEntry List===\n",__func__);

        //�Ƚ������ݿ��������û���⣬�ٸ����ڴ�
        int result=0;
        result = UpdateEntryToUserTable(input);

        if(result != 0)
        {
            printf("=====[%s] ==== update entry in database fail ====\n", __func__);
            if(input !=NULL)
            {
                free_userEntry(input);
            }
            return -1;
        }
        else
        {
            //update info in memory list
            memset(tmp_result->username,0,sizeof(tmp_result->username));
            strcpy(tmp_result->username,input->username);
            tmp_result->grade=input->grade;
        }
        
    }
    return 0;
}


//ָ�ƹ����
struct FingerPrintEntry * global_FingerPrintEntryList_head = NULL;
struct FingerPrintEntry * global_FingerPrintEntryList_tail = NULL;

//����ָ��fingerPrintid �� deviceid ��global_UserEntryList �� ���ұ���
//��û�ҵ�����NULL,�ҵ��򷵻�entry ��ַ��
struct FingerPrintEntry* findFingerPrintEntry(char *input_fingerPrintid, char *input_deviceid)
{
    DEBUG_PRINTF("=====[%s]============\n",__func__);
    
    if(global_FingerPrintEntryList_head == NULL)
    {
        DEBUG_PRINTF("====[%s]====global_FingerPrintEntryList is null ===\n",__func__);   
        return NULL;
    }
    struct FingerPrintEntry* tmp=global_FingerPrintEntryList_head;
    
    while(tmp !=NULL)
    {
        
        if((strcmp(tmp->fingerprintid, input_fingerPrintid) == 0 ) && ( strcmp(tmp->deviceid,input_deviceid)==0))
        {
            DEBUG_PRINTF("===[%s]=== found entry: entry address is 0x %x ; fingerPrintid is %s, deviceid is %s ====\n", __func__,tmp, input_fingerPrintid, input_deviceid);
            return tmp;
        }
        tmp=tmp->root.next;
    }
    return NULL;
}

//���һ���û����û��б�
//input �Ǹ��ѷ���ռ���ڴ�
//���input��listĳ��entry�ظ�����free it.
//����ֵ: 0 ����ɹ�
//        1 ����û�����б����ҵ�
//        -1 �������������� �����ݿ��������
int AddToFingerPrintEntryList(struct FingerPrintEntry *input)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct FingerPrintEntry* tmp_result= findFingerPrintEntry(input->fingerprintid, input->deviceid);
    if(tmp_result == NULL)
    {
        DEBUG_PRINTF("====[%s]: add new entry into FingerPrintEntry List====\n",__func__);

        //��ִ�����ݿ��������������ɹ������ٶ�������в���
        int result = 0;
        result = AddNewEntryToFingerPrintTable(input);

        if(result != 0)
        {
            printf("===[%s]: add entry into database fail =====\n",__func__);
            if(input !=NULL)
            {
                free_fingerPrintEntry(input);
            }
            return -1;
        }
        else
        {
            qtec_insert_list((struct qtec_list *)input,(struct qtec_list **) &global_FingerPrintEntryList_head, (struct qtec_list **) &global_FingerPrintEntryList_tail);

        }
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in fingerPrintentry List===\n",__func__);
        if(input != NULL)
        {
            free_fingerPrintEntry(input);
        }
        return 1;
    }
    return 0;
}


//ɾ��һ���û����û��б�
//input �Ǹ��ѷ���ռ���ڴ�
int RemoveFromFingerPrinterEntryList(char* input_fingerPrintid, char* input_deviceid)
{
    DEBUG_PRINTF("====[%s]====input_fingerPrintid:%s  input_deviceid:%s==\n",__func__,input_fingerPrintid,input_deviceid);
    if((input_fingerPrintid== NULL) || (input_deviceid == NULL))
    {
        DEBUG_PRINTF("====%s====input is wrong === \n",__func__);
        return -1;
    }
    struct FingerPrintEntry* output_result= NULL;
    output_result = findFingerPrintEntry(input_fingerPrintid,input_deviceid);
    
    if(output_result== NULL)
    {
        DEBUG_PRINTF("====[%s]: this entry is not in userentry list====\n",__func__);
        
        return 1;  
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in userentry List, so remove it===\n",__func__);

        //��ִ�����ݿ�������ٶ�������в���
        int result=0;
        result=DelEntryFromFingerPrintTable(input_fingerPrintid,input_deviceid);
        if(result != 0)
        {
            printf("====[%s]: del entry from database fail====\n", __func__);
            
            return -1;
        }
        else
        {
            //��ͬ��deviceid ��entry ���б���ɾ��
            qtec_remove_list((struct qtec_list *)output_result, (struct qtec_list * *) &global_FingerPrintEntryList_head, (struct qtec_list * *) &global_FingerPrintEntryList_tail);
            //�ͷ��ڴ�
            if(output_result!=NULL)
            {
                free_fingerPrintEntry(output_result);
            }
        }
       
    }
    return 0;
}


//����һ���û���Ϣ���û��б�
//input �Ǹ��ѷ���ռ���ڴ�
int UpdateToFingerPrinterEntryList(struct FingerPrintEntry* input)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
    struct FingerPrintEntry* tmp_result= findFingerPrintEntry(input->fingerprintid,input->deviceid);
    
    if(tmp_result == NULL)
    {
        DEBUG_PRINTF("====[%s]: this entry not in  fingerprintentry List====\n",__func__);
        if(input != NULL)
        {
            free_fingerPrintEntry(input);
        }
        return 1;
    }
    else
    {
        DEBUG_PRINTF("====[%s]: this entry alread in fingerPrintEntry List===\n",__func__);

        //�Ƚ������ݿ��������û���⣬�ٸ����ڴ�
        int result=0;
        result = UpdateEntryToFingerPrintTable(input);

        if(result != 0)
        {
            printf("=====[%s] ==== update entry in database fail ====\n", __func__);
            if(input !=NULL)
            {
                free_fingerPrintEntry(input);
            }
            return -1;
        }
        else
        {
            //update info in memory list
            memset(tmp_result->name,0, sizeof(tmp_result->name));
            strcpy(tmp_result->name,input->name);
            memset(tmp_result->userid,0,sizeof(tmp_result->userid));
            strcpy(tmp_result->userid,input->userid);
        }
        
    }
    return 0;
}


//������־�б�����ݿ⣬��Ϊÿ�β��붼�����һ�У���ɾ��ҲҪɾ�������һ����ʼɾ
//���ݿⵯ����һ������ 
//delete from user_table where rowid=(select min(rowid) from user_table);
struct LogEntry* global_LogEntryList_head=NULL;
struct LogEntry* global_LogEntryList_tail=NULL;

int AddToLogEntryList(struct LogEntry* input)
{
    DEBUG_PRINTF("====[%s]======\n",__func__);
    if(input == NULL)
    {
        DEBUG_PRINTF("====%s====input is null === \n",__func__);
        return -1;
    }
   
    DEBUG_PRINTF("====[%s]: add new entry into LogEntry List====\n",__func__);

    //��ִ�����ݿ��������������ɹ������ٶ�������в���
    int result = 0;
    result = AddNewEntryToLogTable(input);

    if(result != 0)
    {
        printf("===[%s]: add entry into database fail =====\n",__func__);
        if(input !=NULL)
        {
            free_logEntry(input);
        }
        return -1;
    }
    else
    {
        qtec_insert_list((struct qtec_list *)input,(struct qtec_list **) &global_LogEntryList_head, (struct qtec_list **) &global_LogEntryList_tail);
    }
    
  
    return 0;
}


//ɾ��һ���û����û��б�
//input �Ǹ��ѷ���ռ���ڴ�
int RemoveFirstEntryFromLogEntryList()
{
    DEBUG_PRINTF("====[%s]======\n",__func__);

    if(global_LogEntryList_head == NULL)
    {
        DEBUG_PRINTF("[%s]===global_logEntry list head is null===\n");
        return -1;
    }
    int rc =0;
    rc = DelFirstEntryFromLogTable();
    if(rc != 0)
    {
        printf("==[%s]===del entry from database fail ===\n",__func__);
        return -1;
    }
    else
    {
        struct LogEntry *tmp = global_LogEntryList_head;
        qtec_remove_list((struct qtec_list *) tmp, (struct qtec_list * *) &global_LogEntryList_head, (struct qtec_list * *) &global_LogEntryList_tail);
        if(tmp !=NULL)
        {
            free_logEntry(tmp);
        }
    }
    return 0;
}


