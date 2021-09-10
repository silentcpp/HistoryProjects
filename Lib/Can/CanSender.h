#pragma once

#pragma execution_character_set("utf-8")

#include "CanFactory.h"

//最大报文数量
#define MAX_MSG_COUNT 256

//发送处理函数定义
#define SEND_PROC_FNC(...) [__VA_ARGS__](MsgNode& FMSG)mutable->void

//发送处理定义
typedef const std::function<void(MsgNode&)>& SendProc;

/*
* @SendType,发送类型
*/
enum SendType {
	//周期
	ST_PERIOD,

	//事件
	ST_EVENT,

	//周期/事件
	ST_PE,
};

/*
* @CanMsg,CAN报文
* @notice,这个结构体顺序不可随意改变,
* 否则将会导致程序崩溃
*/

struct CanMsg {
	//报文节点
	MsgNode msg;

	//报文延时
	int delay;

	//发送类型
	SendType type;

	//发送次数
	int count;

	//发送处理
	std::function<void(MsgNode& msg)> fnc;

	//是否有效
	bool valid;

	//时间戳
	int time;
};

class CanSender
{
public:
	/*
	* @CanSender,构造
	*/
	CanSender();

	/*
	* @CanSender,构造
	* @param1,CAN传输
	*/
	CanSender(CanTransfer* transfer);

	/*
	* @~CanSender,析构
	*/
	~CanSender();

	/*
	* @getLastError,获取最终错误
	* @return,const QString&
	*/
	const QString& getLastError();

	/*
	* @init,初始化
	* @param1,CAN传输
	* @return,bool
	*/
	bool init(CanTransfer* transfer);

	/*
	* @getMsgData,获取报文数据
	* @param1,报文ID
	* @param2,报文数据
	* @return,bool
	*/
	bool getMsgData(int id, UCHAR* data);

	/*
	* @setMsgData,设置报文数据
	* @param1,报文ID
	* @param2,报文数据
	* @return,bool
	*/
	bool setMsgData(int id, const UCHAR* data);

	/*
	* @addMsg,添加报文[重载1]
	* @param1,报文
	* @param2,延时
	* @param3,发送类型
	* @param4,次数
	* @param5,发送处理[lambda]
	* @return,bool
	*/
	bool addMsg(const MsgNode& msg, int delay, SendType type = ST_PERIOD, int count = 0, SendProc proc = nullptr);

	/*
	* @addMsg,添加报文[重载2]
	* @param1,发送处理[lambda]
	* @param2,延时
	* @param3,发送类型
	* @param4,发送次数
	* @return,bool
	*/
	bool addMsg(SendProc proc, int delay, SendType type = ST_PERIOD, int count = 0);

	/*
	* @addMsg,添加报文[重载3]
	* @param1,报文
	* @return,bool
	*/
	bool addMsg(const CanMsg& msg);

	/*
	* @addMsg,添加报文[重载4]
	* @param1,报文初始化列表
	* @return,bool
	*/
	bool addMsg(const std::initializer_list<CanMsg>& msg);

	/*
	* @addMsg,添加报文[重载5]
	* @param1,报文
	* @notice,param1格式:{{id},delay,type,count}
	* @param2,起始位置
	* @param3,数据长度
	* @param4,数据
	* @return,bool
	*/
	bool addMsg(const CanMsg& msg, int start, int length, ULONGLONG data);

	/*
	* @addPeriodEventMsg,添加周期事件报文
	* @param1,CAN报文
	* @return,void
	*/
	bool addPeriodEventMsg(const CanMsg& msg);

	/*
	* @deleteMsgs,删除报文[重载1]
	* @param1,报文初始化列表
	* @return,void
	*/
	void deleteMsgs(const std::initializer_list<MsgNode>& msgs);

	/*
	* @deleteMsgs,删除报文[重载2]
	* @param1,ID初始化列表
	* @return,void
	*/
	void deleteMsgs(const std::initializer_list<int>& ids);

	/*
	* @deleteOnMsg,删除一个报文[重载1]
	* @param1,报文
	* @return,void
	*/
	void deleteOneMsg(const MsgNode& msg);

	/*
	* @deleteOnMsg,删除一个报文[重载2]
	* @param1,报文
	* @return,void
	*/
	void deleteOneMsg(const CanMsg& msg);

	/*
	* @deleteOneMsg,删除一个报文
	* @param1,报文ID
	* @return,void
	*/
	void deleteOneMsg(int id);

	/*
	* @deleteAllMsgs,删除所有报文
	* @return,void
	*/
	void deleteAllMsgs();

	/*
	* @pauseMsg,暂停报文
	* @param1,报文初始化列表
	* @return,void
	*/
	void pauseMsg(const std::initializer_list<MsgNode>& msg);

	/*
	* @continueMsg,继续报文
	* @param1,报文初始化列表
	* @return,void
	*/
	void continueMsg(const std::initializer_list<MsgNode>& msg);

	/*
	* @start,开始(发送报文)
	* @return,void
	*/
	void start();

	/*
	* @stop,停止(发送报文)
	* @return,void
	*/
	void stop();

protected:
	/*
	* @setLastError,设置最终错误
	* @param1,最终错误
	* @return,void
	*/
	void setLastError(const QString& error);

	/*
	* @sendProcThread,发送处理线程
	* @param1,参数
	* @return,void
	*/
	static UINT WINAPI sendProcThread(void* args);
private:
	//是否退出
	bool m_quit = false;

	//是否开始
	bool m_start = false;

	//CAN传输
	CanTransfer* m_transfer = nullptr;

	//定时器
	Timer m_timer;

	//报文数组
	CanMsg m_msgs[MAX_MSG_COUNT] = { 0 };

	//报文数组备份
	CanMsg m_msgsBackup[MAX_MSG_COUNT] = { 0 };

	//句柄
	HANDLE m_handle = nullptr;

	//最终错误
	QString m_lastError = "No Error";
};
