#pragma once

#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QProcess>

#include <functional>

#include "File.h"
#include "AuthDlg.h"
#include "UnlockDlg.h"
#include "UpdateDlg.h"
#include "JQCPUMonitor.h"

#define GET_JSON() Json::getInstance()

#define TO_STRING(X) #X

#define BUFF_SIZE 0x1000

#define NO_THROW_NEW new(std::nothrow)

#define S_TO_Q_STR(X) QString::fromStdString(X)

#define WS_TO_Q_STR(X) QString::fromStdWString(X)

#define WC_TO_Q_STR QString::fromWCharArray

#define Q_TO_C_STR(X) X.toStdString().c_str()

#define Q_TO_C_LEN(X) X.toStdString().length()

#define Q_TO_WC_STR(X) X.toStdWString().c_str()

#define Q_TO_WC_LEN(X) X.toStdWString().length()

#define G_TO_Q_STR(X) QString::fromLocal8Bit(X)

#define G_TO_C_STR(X) Q_TO_C_STR(G_TO_Q_STR(X))

#define N_TO_Q_STR QString::number

#define SU_FA(X) X ? "成功":"失败"

#define OK_NG(X) X ? "OK" : "NG"

#define Q_SPRINTF(format,...) QString().sprintf(format,##__VA_ARGS__)

#define DEC_TO_HEX(num) Q_SPRINTF("%d",num).toInt(nullptr,16)

#define DEBUG_INFO()\
if (Utility::Var::debugInfo)\
	qDebug().noquote() << QString("%1 %2 %3 %4").arg(QString::number(Utility::Var::logCount), 4, '0').arg(Utility::getCurrentTime(), \
	__FUNCTION__, QString::number(__LINE__))

#define DEBUG_INFO_EX(format,...) \
if (Utility::Var::debugInfo)\
	qDebug().noquote() << QString("%1 %2 %3 %4 %5").arg(QString::number(Utility::Var::logCount), 4, '0').arg(Utility::getCurrentTime(), \
	__FUNCTION__, QString::number(__LINE__), Q_SPRINTF(format, ##__VA_ARGS__))

#define RUN_BREAK(success,error) \
if ((success))\
{\
	setLastError(error);\
	break;\
}

//安全删除数组
#define SAFE_DELETE_A(X)\
if (X)\
{\
	delete[] X;\
	X = nullptr;\
}

//安全删除变量
#define SAFE_DELETE(X)\
if (X)\
{\
	delete X;\
	X = nullptr;\
}


/*
* @Utility,实用工具
*/
namespace Utility {

	/*
	* @Var,静态变量命名空间
	*/
	namespace Var {
		static bool debugInfo = false;

		static unsigned int logCount = 0;

		static QString lastError = "未知错误";

		static QString appendName;

		static bool appendPos = false;
	}

	/*
	* @setDebugInfo,启用调试信息
	* @param1,是否启用
	* @return,void
	*/
	void setDebugInfo(bool enable);

	/*
	* @setLastError,设置错误信息
	* @param1,错误信息
	* @return,void
	*/
	void setLastError(const QString& error);

	/*
	* @getLastError,获取错误信息
	* @return,const QString&
	*/
	const QString& getLastError();

	/*
	* @getFileNameByUrl,通过URL获取文件名
	* @param1,URL
	* @return,QString
	*/
	QString getFileNameByUrl(const QString& url);

	/*
	* @getFileNameByPath,通过路径获取文件名
	* @param1,路径
	* @return,QString
	*/
	QString getFileNameByPath(const QString& path);

	/*
	* @getCurrentFileName,获取当前文件名
	* @return,const QString
	*/
	QString getCurrentFileName();

	/*
	* @getCurrentDir,获取当前目录
	* @return,const QString
	*/
	QString getCurrentDir();

	/*
	* @makePath,创建路径
	* @param1,路径名
	* @return,bool
	*/
	bool makePath(const QString& path);

	/*
	* @existPath,存在路径
	* @param1,路径名
	* @return,bool
	*/
	bool existPath(const QString& path);

	/*
	* @makeDir,创建目录
	* @param1,目录名
	* @return,bool
	*/
	bool makeDir(const QString& dir);

	/*
	* @existDir,存在目录
	* @param1,目录名
	* @return,bool
	*/
	bool existDir(const QString& dir);

	/*
	* @_getAppVersion,获取应用程序版本号
	* @return,const QString
	*/
	QString _getAppVersion();

	/*
	* @getAppVersion,获取应用程序版本号
	* @return,const QString
	* @notice,只获取一次
	*/
	const QString& getAppVersion();

	/*
	* @setAppAppendName,设置应用程序附加名称
	* @notice,这个API为外部设置所使用
	* @param1,附加名
	* @return,void
	*/
	void setAppAppendName(const QString& appendName);

	/*
	* @setAppAppendPos,设置应用程序附加位置
	* @notice,这个API为外部设置所使用
	* @param1,附加位置,前:ture 后:false
	* @return,void
	*/
	void setAppAppendPos(bool appendPos);

	/*
	* @getAppAppendName,获取应用程序附加名称
	* @notice,这个API为外部设置所使用
	* @return,QString
	*/
	QString getAppAppendName();

	/*
	* @getAppAppendPos,获取应用程序附加位置
	* @notice,这个API为外部设置所使用
	* @return,bool
	*/
	bool getAppAppendPos();

	/*
	* @renameAppByVersion,通过版本号重命名应用程序
	* @notice,如果Var::appendName不为空,则使用它
	* @param1,QWidget
	* @param2,附加名
	* @param3,附加位置,前:true 后:false
	* @return,bool
	*/
	bool renameAppByVersion(QWidget* widget, const QString& appendName = QString(), bool appendPos = false);

	/*
	* @startApp,启动应用程序
	* @param1,程序名称
	* @param2,显示方式
	* @param3,是否为绝对路径
	* @return,bool
	*/
	bool startApp(const QString& name, const int& show, bool absolutely = false);

	/*
	* @finishApp,结束应用程序
	* @param1,程序名
	* @return,bool
	*/
	bool finishApp(const QString& name);

	/* 
	* @getCurrentTime,获取当前时间
	* @param1,是否为文件格式
	* @return,const QString
	*/
	QString getCurrentTime(bool fileFormat = false);

	/* 
	* @getCurrentDate,获取当前日期
	* @param1,是否为文件格式
	* @return,const QString
	*/
	QString getCurrentDate(bool fileFormat = false);

	/*
	* @getCurrentDateTime,获取当前时间日期
	* @param1,是否为文件格式
	* @return,const QString
	*/
	QString getCurrentDateTime(bool fileFormat = false);

	/*
	* @getFileListByPath,通过路径获取文件列表
	* @param1,路径
	* @param2,所获取的文件列表
	* @return,void
	*/
	void getFileListByPath(const QString& path, QStringList& fileList);

	/* 
	* @getFileListBySuffixName,通过后缀名获取文件列表
	* @param1,路径
	* @param2,后缀名
	* @return,QStringList
	*/
	QStringList getFileListBySuffixName(const QString& path, const QStringList& suffix);

	/*
	* @wideCharToMultiByte,宽字符集转多字符集
	* @param1,宽字符数组
	* @return,char*
	* @notice,需要手动释放内存
	*/
	char* wideCharToMultiByte(const wchar_t* wide);

	/*
	* @multiByteToWideChar,多字符集转宽字符集
	* @param1,多字符集
	* @return,wchar_t*
	* @notice,需要手动释放内存
	*/
	wchar_t* multiByteToWideChar(const char* multi);

	/*
	* @ping,测试网络是否畅通
	* @param1,地址
	* @param2,次数
	* @return,bool
	*/
	bool ping(const char* address, const int& times);

	/*
	* @compareList,对比字符串链表
	* @param1,链表1
	* @param2,链表2
	* return,bool
	*/
	bool compareList(const QStringList& cmp1, const QStringList& cmp2);

	/*
	* @removeList,移除链表
	* @param1,链表1
	* @param2,链表2
	* @return,bool
	* @notice,移除链表2中存在链表1中的数据
	*/
	bool removeList(const QStringList& list1, QStringList& list2);

	/*
	* @httpDownload,超文本传输协议下载
	* @param1,链接
	* @param2,超时
	* @param3,lambda
	*/
	bool httpDownload(const char* url, int timeout, const std::function<void(long, const char*)>&);

	/*
	* 初始化控制台窗口
	* @notice,调用此函数前,不可进行任何输出,
	* 否则重定向流将失败,你无法看到打印内容.
	*/
	bool initConsoleWindow(const QString& title = "调试控制台");

	/*
	* @exitConsoleWindow,退出控制台窗口
	* @return,bool
	*/
	bool exitConsoleWindow();

	/*
	* @getTimeStamp,获取时间戳
	* @notice,所需ISO DATE格式 2021-05-15 10:00:00.00 
	* @param1,新日期时间
	* @param2,旧日期时间
	* @return,const uint[成功返回秒数,失败(uint)-1]
	*/
	uint getTimeStamp(const QString& dt1, const QString& dt2);

	/*
	* @secToMinCountdown,分钟倒计时
	* @param1,总计分钟
	* @param2,当前秒数
	* @param3,倒计时分钟
	* @param4,倒计时秒
	* @return,void
	*/
	void minuteCountdown(int totalMinute, int currentSecond, int& minute, int& second);

	/*
	* @getAppNameVersion,获取APP名称版本
	* @param1,APP名称
	* @return,QString 
	* @useage,如C:/Windows/App[1.0.0.1].exe,则返回1.0.0.1
	* 成功,则返回版本例如1.0.0.0字符串
	* 失败,则返回空字符串
	*/
	QString getAppNameVersion(const QString& fileName);

	/*
	* @versionToNumber,版本转数字
	* @param1,如1.0.0.1或程序名可带路径如C:\Windows\XXXX[1.0.0.1].exe
	* @return,int
	* 成功,返回计算过的版本值
	* 失败,-1
	*/
	int versionToNumber(const QString& appName);
}