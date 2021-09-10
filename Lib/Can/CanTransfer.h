#pragma once

#pragma execution_character_set("utf-8")

#include <QObject>

#include <QDir>

#include <QFileInfo>

#include <Windows.h>

#include <functional>

#include <LogMgr/LogMgr.h>
#pragma comment(lib, "LogMgr.lib")

#include <Timer/Timer.h>
#pragma comment(lib, "Timer.lib")

#include "CanMessage.h"

#include "CanMatrix.hpp"

#define MAX_SUPPORTED_BAUDRATE_COUNT 5

#define CONTINUE_RECEIVE_TIMES 2

#define CONTINUE_RECEIVE_INTERVAL 1

#define MAX_FRAME_COUNT 4096

/*
* @CanTransfer,CAN传输
* @notice,此类作为CAN卡的父类,如需增长新CAN卡需要继承此类
*/

class CanTransfer
{
public:
	/*
	* @CanTransfer,构造
	*/
	CanTransfer();

	/*
	* @virtual ~CanTransfer,虚析构
	*/
	virtual ~CanTransfer();

	/*
	* @setReceiveID,设置接收ID
	* @param1,需要接收的CAN ID
	* @return,void
	*/
	void setReceiveID(unsigned int id)
	{
		m_filter = true;
		m_recvID = id;
	};

	/*
	* @setMatrixType,设置矩阵类型
	* @param1,矩阵类型
	* @return,void
	*/
	void setMatrixType(MatrixType matrix);

	/*
	* @open,连接CAN卡
	* @notice,此类为纯虚函数,必须重写
	* @param1,波特率
	* @param2,拓展帧,0否,1是
	* @param3,设备号
	* @param4,端口号
	* @return,bool
	*/
	virtual bool open(int baudrate, int extFrame, int device = 0, int port = 0) = 0;

	/*
	* @close,断开CAN卡
	* @notice,此类为纯虚函数,必须重写
	* @return,bool
	*/
	virtual bool close() = 0;

	/*
	* @clearBuffer,清空缓存
	* @notice,此类为纯虚函数,必须重写
	* @return,bool
	*/
	virtual bool clearBuffer() = 0;

	/*
	* @send,发送CAN报文
	* @notice,此类为纯虚函数,必须重写
	* @param1,MsgNode结构体
	* @return,bool
	*/
	virtual bool send(const MsgNode* msg) = 0;

	/*
	* @multiSend,多重发送
	* @notice,此类为纯虚函数,必须重写
	* @param1,MsgNode结构体
	* @param2,发送数量
	* @return,bool
	*/
	virtual bool multiSend(const MsgNode* msg, int count) = 0;

	/*
	* @receiveProtected,接收保护
	* @param1,MsgNode结构体
	* @param2,MsgNode数组大小
	* @param3,毫秒
	*/
	virtual int receiveProtected(MsgNode* pMsg, int size, int ms = 200) = 0;

	/*
	* @receive,接收CAN报文
	* @param1,MsgNode结构体
	* @param2,接收多少MsgNode结构体
	* @param3,毫秒
	* @param4,接收ID
	* @param5,命令ID
	* @return,const int,返回实际接收的数量
	*/
	int receive(MsgNode* msg, int size, int ms, int recvID = -1, int cmdID = -1);

	/*
	* @quickReceive,快速接收CAN报文
	* @param1,MsgNode结构体
	* @param2,接收多少MsgNode结构体
	* @param3,毫秒
	* @return,const int,返回实际接收的数量
	*/
	int quickReceive(MsgNode* msg, int size, int ms);

	/*
	* @receive,接收CAN报文
	* @param1,MsgNode结构体
	* @param2,接收多少MsgNode结构体
	* @param3,毫秒
	* @param4,接收ID
	* @param5,命令ID
	* @return,const int,返回实际接收的数量
	*/
	int safeReceive(MsgNode* msg, int size, int ms, int recvID = -1, int cmdID = -1);

	/*
	* @enableSaveLog,启用保存日志
	* @param1,是否启用
	* @return,void
	*/
	void enableSaveLog(bool on);

	/*
	* @enableDebug,启用调试
	* @param1,是否启用
	* @return,void
	*/
	void enableDebug(bool on);

	/*
	* @saveLog,保存日志
	* @param1,发送类型
	* @param2,MsgNode结构体
	* @param3,MsgNode的数量
	* @return,bool
	*/
	bool saveLog(const char* type, const MsgNode* msg, int count = 1);

	/*
	* @flushLogFile,刷新日志文件
	* @return,bool
	*/
	bool flushLogFile();

	/*
	* @clearLogFile,清空日志文件
	* @return,bool
	*/
	bool clearLogFile();

	/*
	* @connected,是否连接
	* @return,bool
	*/
	bool isOpened();

	/*
	* @startReceiveThread,开启接收线程
	* @return,bool
	*/
	bool startReceiveThread();

	/*
	* @stopReceiveThread,停止接收线程
	* @return,bool
	*/
	bool stopReceiveThread();

	/*
	* @getLastError,获取最终错误
	* @return,const char*
	*/
	const QString& getLastError();

	/*
	* @setSaveLogInfo,设置保存日志信息
	* @param1,目录名
	* @param2,机种名
	* @param3,条码名
	* @return,void
	*/
	void setSaveLogInfo(const QString& dirName, const QString& moduleName = QString(), const QString& codeName = QString());

	/*
	* @setProcessFnc,设置处理函数
	* @param1,lambda表达式,用于处理所(发送/接收)的内容
	* @format,std::function<void(const char*, const MsgNode&)>
	* @return,void
	*/
	void setProcessFnc(const std::function<void(const char*, const MsgNode&)>& fnc = nullptr);

	/*
	* @getDataLength,获取数据长度
	* @notice,此API在使用FD得时候才会被调用.
	* @return,int
	*/
	int getDlc() const;

	/*
	* @m_matrix,CAN矩阵算法
	*/
	CanMatrix m_matrix;

	/*
	* @获取是否使用flexible data-rate
	* @return,bool
	*/
	bool getUseFd() const;

	/*
	* @设置使用flexible data-rate
	* @param1,是否使用
	* @return,void
	*/
	void setUseFd(bool on);

protected:

	/*
	* @setLastError,设置最终错误
	* @param1,最终错误
	* @return,void
	*/
	void setLastError(const QString& error);

	/*
	* @receiveThread,接收线程
	* @param1,传入参数
	* @return,unsigned int
	*/
	static UINT WINAPI receiveThread(void* args);

	/*
	* @getDlc,获取数据长度代码,DLC[data length code]
	* @param1,MsgNode结构体
	* @return,实际长度
	*/
	int getDlc(const MsgNode* msg);

	/*
	* @formatMsg,格式化报文
	* @param1,类型[S:SEND,R:RECEIVE,F:FAILED]
	* @param1,MsgNode结构体
	* @param2,需要格式化的缓冲区
	* @return,void
	*/
	void formatMsg(const char* type, const MsgNode& msg, char* text);

	/*
	* @outputMsg,输出报文
	* @param1,类型[S:SEND,R:RECEIVE,F:FAILED]
	* @param2,MsgNode结构体
	* @param3,MsgNode数量
	* @return,void
	*/
	void outputMsg(const char* type, const MsgNode* msg, int count = 1);

	/*
	* @setDlc,设置数据长度
	* @notice,此API需要在写子类中调用,实际长度取决于定义,一般长度为8
	* @param1,长度
	* @return,void
	*/
	void setDlc(int dlc = 8);
protected:
	//线程是否退出
	bool m_quit = false;

	//是否打开
	bool m_open = false;

	//设备号
	int m_device = 0;

	//波特率
	int m_baudrate = 500;

	//端口号
	int m_port = 0;

	//拓展帧
	int m_extFrame = 0;

	//接收ID
	int m_recvID = 0;

	//是否过滤报文
	bool m_filter = false;

	//CAN报文
	CanMessage m_message;

	//定时器
	Timer m_timer;

	//是否保存日志
	bool m_saveLog = false;

	//是否调试
	bool m_debug = false;

	//ACC代码
	int m_accCode = 0;

	//ACC屏蔽
	int m_accMask = 0;

	//使用CANFD(CAN flexible data-rate)
	bool m_useFd = false;
private:
	//线程句柄
	HANDLE m_threadHandle = nullptr;

	//线程锁
	CRITICAL_SECTION m_cs;

	CLogMgr* m_logMgr = nullptr;

	//文件夹名
	QString m_dirName = "Log";

	//机种名
	QString m_modelName = "未知机种";

	//条码名
	QString m_codeName = "未知条码";

	//最终错误
	QString m_lastError = "No Error";

	//报文处理函数
	std::function<void(const char*, const MsgNode&)> m_fnc = nullptr;

	//数据长度
	int m_dlc = 8;
};

