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

typedef const std::function<void(MsgNode&)>& SendProc;

#define SEND_PROC_FNC(...) [__VA_ARGS__](MsgNode& FMSG)mutable->void

/************************************************************************/
/* Class define                                                         */
/************************************************************************/
class CanSender
{
public:
	friend static UINT WINAPI SendCanProc(void* pArgs);

	CanSender();

	CanSender(IConnMgr* const pIConnMgr);

	~CanSender();

	bool EnableExternalMsg(bool enable = true);

	bool Init(IConnMgr* const pIConnMgr);

	bool GetMsgData(const int& ID, UCHAR* ucData);

	bool SetMsgData(const int& ID, const UCHAR* const ucData);

	bool AddMsg(const MsgNode& msg, const int& iDelay, const SendType& emST = ST_Period, const int& iSendCount = 0, SendProc sendProc = nullptr);

	bool AddMsg(SendProc sendProc, const int& delay, const SendType& type = ST_Period, const int& count = 0);

	bool AddMsg(const CanMsg& msg);

	bool AddMsg(const std::initializer_list<CanMsg>& msg);

	void DeleteMsgs(const std::initializer_list<MsgNode>& msgs);

	void DeleteMsgs(const std::initializer_list<int>& ids);

	void DeleteOneMsg(const MsgNode& msg);

	void DeleteOneMsg(const CanMsg& msg);

	void DeleteOneMsg(const int& id);

	void DeleteAllMsgs();

	void PauseMsg(const std::initializer_list<MsgNode>& msg);

	void ProceedMsg(const std::initializer_list<MsgNode>& msg);

	void Start();

	void Stop();

	bool ReceSpecSigs(const int& iID, LPVOID pstSS, fpConfirmMsg fpConMsg, const int& iTime, char* szResult);

	const char* GetLastError();
protected:
	void SetLastError(const char* szError);
private:
	bool m_bQuit = false;

	bool m_bStart = false;

	IConnMgr* m_pIConnMgr = nullptr;

	CTimeMgr m_time;

	CanMsg m_msgs[MAX_MSG_COUNT] = { 0 };

	CanMsg m_msgBackup[MAX_MSG_COUNT] = { 0 };

	HANDLE m_hSend = nullptr;

	char m_szLastError[512] = { 0 };

	JsonTool* m_jsonTool = JsonTool::getInstance();
};
#endif//_H_SIMPLESRMGR_H_
