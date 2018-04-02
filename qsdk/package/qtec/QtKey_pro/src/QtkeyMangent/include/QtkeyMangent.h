/********************************************************
*	Filename:	QtkeyMangent.h	                    	*
*	Author	:	lirui(lir@qtec.cn)                    	*
*                                                      	*
* 	History                                         	*
*		2017/06/19	Create								*
********************************************************/

#ifndef __QKKEYMANGENT_H__
#define __QKKEYMANGENT_H__

#include "QtManagent_defines.h"
#include "QtkeyMangent_raw.h"
#include "QtkeyMangent_syn.h"
#include "QtKeyEncrypt.h"

class CQtQkPoolBase
{
public:
	CQtQkPoolBase()
	{
		m_pQkPoolHandle = 0;
	}
	~CQtQkPoolBase(){}
	
public:
	int Initialize();
	void UnInitialize();
	
protected:
	sqlite3 *m_pQkPoolHandle;
	CQtQkMangentCommon m_QkMangentCommon;
};

class CQtQkMangent : public CQtQkPoolBase
{
public:
	CQtQkMangent();
	~CQtQkMangent();

public:
	/* �����Կ */
	virtual int AddKey(BYTE nPoolType, CQtUserId UserId, CQtDeviceId &DeviceId, ListKeyID &lKeyId, ListKey &lKey, BYTE *mainKey);

	/* ��ȡ��ǰ����ĳ�ڵ���Կ������(ʹ��/δʹ��) */
	virtual int GetCount(BYTE nPoolType, int *pUsedCount, int *pUnusedCount, CQtUserId UserId, CQtDeviceId &DeviceId);

	/* ����user_id��ȡָ��������Կ */
	virtual int GetKeyByNode(BYTE nPoolType, BYTE nNumber, CQtUserId UserId, CQtDeviceId &DeviceId, ListKeyID &lKeyId, ListKey &lKey, BYTE *mainKey);

    /* ����user_id��ȡָ������ԭʼ��Կ */
	virtual int GetRawKeyByNode(BYTE nPoolType, BYTE nNumber, CQtUserId UserId, CQtDeviceId &DeviceId, ListKeyID &lKeyId, ListKey &lKey, BYTE *mainKey);

	/* ����key_id��ȡָ��������Կ */
	virtual int GetKeyById(BYTE nPoolType, BYTE nNumber, CQtUserId UserId, CQtDeviceId &DeviceId, ListKeyID &lKeyId, ListKey &lKey);

	/* ����key_id��user_id��ȡָ��������Կ */
	virtual int GetKeyByIdNode(BYTE nPoolType, BYTE nNumber, CQtUserId UserId, CQtDeviceId &DeviceId, ListKeyID &lKeyId, ListKey &lKey, BYTE *mainKey);

	/* ����user_idɾ����Կ */
	virtual int DeleteKeyByNode(BYTE nPoolType, CQtUserId UserId, CQtDeviceId &DeviceId);

	/* ����key_idɾ����Կ */
	virtual int DeleteKeyById(BYTE nPoolType, ListKeyID &lKeyId);

    /* ɾ����keyidС��ͬ����Կ */
    virtual int DeleteSynKeyByNodeId(BYTE *keyid, CQtUserId UserId, CQtDeviceId &DeviceId);

	/* ����key_id����peer */
	virtual int UpdatePeerById(BYTE nPoolType, string &lUserId, ListKeyID &lKeyId);    

private:
	CQtQkMangentRawKey m_QkMangentRawKey;
	CQtQkMangentSynKey m_QkMangentSynKey;
    CQtKeyEncrypt m_KeyEncrypt;
};

#endif

