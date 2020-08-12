#ifndef _H_SIMPLESRMGR_H_
#define _H_SIMPLESRMGR_H_
#pragma warning(disable:4477)
/************************************************************************/
/* Include                                                              */
/************************************************************************/
#include <CanMgr\ConnFactory.h>
#pragma comment(lib, "CanMgr.lib")

#include "JsonTool.h"

typedef bool (*fpConfirmMsg)(LPVOID pstSS, UCHAR* src);

static UINT __stdcall SendCanProc(void* pArgs);

/************************************************************************/
/* Class define                                                         */
/************************************************************************/
class CanSender
{
public:
	friend static UINT __stdcall SendCanProc(void* pArgs);

	CanSender();

	CanSender(IConnMgr* pIConnMgr);

	~CanSender();

	bool EnableExternalMsg(bool enable = true);

	bool Init(IConnMgr* pIConnMgr);

	bool GetMsgData(const int& ID, UCHAR* ucData);

	bool SetMsgData(const int& ID, const UCHAR* const ucData);

	bool AddMsg(const MsgNode& msg, const int& iDelay, const SendType& emST = ST_Period, const int& iSendCount = 0);

	bool AddMsg(const CanMsg& msg);

	bool AddMsg(std::initializer_list<CanMsg> msg);

	bool DeleteMsgs(const int* iIDs, const int& iCount);

	bool DeleteMsgs(std::initializer_list<int> ids);

	bool DeleteOneMsg(const int& iID);

	bool PauseMsg(const int* iIDs, const int& iCount);

	bool ProceedMsg(const int* iIDs, const int& iCount);

	bool Start();

	bool Stop();

	bool ReceSpecSigs(const int& iID, LPVOID pstSS, fpConfirmMsg fpConMsg, const int& iTime, char* szResult);

	const char* GetLastError();
protected:
	void SetLastError(const char* szError);
private:
	bool m_bQuit;

	bool m_bStart;

	IConnMgr* m_pIConnMgr = nullptr;

	CTimeMgr m_time;

	CanMsg m_msgs[MAX_MSG_COUNT] = { 0 };

	CanMsg m_msgBackup[MAX_MSG_COUNT] = { 0 };

	HANDLE m_hSend;

	char m_szLastError[512] = { 0 };

	JsonTool* m_jsonTool = JsonTool::getInstance();
};
#endif//_H_SIMPLESRMGR_H_
