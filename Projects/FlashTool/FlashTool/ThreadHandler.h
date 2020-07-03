#pragma once
#pragma execution_character_set("utf-8")

/************************************************************************/
/* 线程管理类和工作线程类                                               */
/* WorkThread动态更新,用来烧录BIN文件,ThreadHandler用来管理开始和结束	*/
/************************************************************************/

#include <QThread>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

#include <ItechSCPIMgr/ItechSCPIMgr.h>
#include <ItechSCPIMgr6302/ItechSCPIMgr6302.h>
#include <MR-DO16-KNMgr/MR-DO16-KNMgr.h>
#include <AardvarkMgr/AardvarkMgr.h>
#include <QMutex>
#include <QTimer>
#include <QDateTime>
#include "JsonTool.h"
#include "Isp.h"

#pragma comment(lib,"MR-DO16-KNMgr.lib")
#pragma comment(lib,"ItechSCPIMgr.lib")
#pragma comment(lib,"ItechSCPIMgr6302.lib")
#pragma comment(lib,"AardvarkMgr.lib")

/*用于转换Lib库文字乱码*/
#define From8Bit(x) QString::fromLocal8Bit(x)
#define OK_NG(X) X ? "OK" :"NG"
#define Q_SPRINTF(format,...) QString().sprintf(format,__VA_ARGS__)

/************************************************************************/
/* 烧录状态                                                             */
/************************************************************************/
typedef enum class BurnStatus
{
	/*写入状态*/
	BS_WR,

	/*读取状态*/
	BS_RD,

	/*正常状态*/
	BS_OK,

	/*错误状态*/
	BS_NG,

	/*无状态*/
	BS_NONE
}burnStatus_t;

/************************************************************************/
/* 烧录顺序                                                             */
/************************************************************************/
typedef enum class BurnSequence
{
	/*扫码*/
	BS_SCAN_CODE,

	/*准备烧录*/
	BS_PREP_BURN,

	/*初始化地址*/
	BS_INIT_ADDR,

	/*读取坐标*/
	BS_READ_COOR,

	/*修改BIN文件*/
	BS_ALTER_BIN_FILE,

	/*写入BIN文件*/
	BS_WRITE_BIN_FILE,

	/*重启电源*/
	BS_RESTART_POWER,

	/*校验数据*/
	BS_CHECK_DATA,

	/*保存日志*/
	BS_SAVE_LOG,

	/*等待同步*/
	BS_WAIT_SYNC,

	/*无*/
	BS_NONE
}burnSequence_t;

/************************************************************************/
/* 烧录模式                                                             */
/************************************************************************/
enum BurnMode
{
	BM_ATC_016_SET,//0
	BM_CTC_016_SET,//1
	BM_CTC_019_SET,//2
	BM_EEP_AXS340,//3
	BM_FLASH_AXS340,//4
	BM_NET_AXS340,//5
	BM_CTC_CHANGAN_IMS,//6
	BM_EEP_GEELY_BX11,//7
	BM_CTC_EP30TAP_DMS,//8
	BM_ATC_BYD_OV7958,//9
};

/*019摄像头临时光轴*/
#define TEMP_MODE 0
#if TEMP_MODE
static int HOR = 1;
static int VOR = 3;
#else
static int HOR = 4;
static int VOR = 6;
#endif

/*支持烧录器最大数量*/
#define MAX_DEVICE_COUNT 15

/*声明工作线程*/
class WorkThread;

/************************************************************************/
/* ThreadHandler类                                                      */
/************************************************************************/
class ThreadHandler : public QThread
{
	Q_OBJECT
public:
	/*友元*/
	friend class WorkThread;

	/*构造*/
	explicit ThreadHandler(QObject* parent = nullptr);

	/*析构*/
	~ThreadHandler();

	/*启用调试模式*/
	void enableDebugMode(bool enable = false);
	
	/*获取调试模式*/
	bool getDebugMode();

	/*初始化*/
	bool initInstance();

	/*打开设备*/
	bool openDevice();

	/*关闭设备*/
	bool closeDevice();

	/*设置下拉选框,用于判断选择了几个通道*/
	void setChannelCount(const int& count);

	/*设置线程退出*/
	void threadQuit();

	/*创建工作线程*/
	bool createWorkThread();

	/*删除工作线程*/
	void deleteWorkThread();

	/*获取工作线程*/
	const WorkThread* getWorkThread() const;

	/*开始工作线程*/
	void startWorkThread();

	/*退出工作线程*/
	void quitWorkThread();

	/************************************************************************/
	/* Aardvark                                                             */
	/************************************************************************/

	/*获取烧录器端口号和序列号*/
	const QMap<quint8, quint32>& getAardvarkPortAndSn();

	/*获得烧录器数量*/
	const int getAardvarkCount();

	/*加载烧录器设备*/
	bool loadAardvarkDevice();

	/*获取错误*/
	const QString& getLastError();

	/*扫码对话框*/
	bool scanCodeDlg(const int& number);

	/*设置运行开关*/
	void setRunSwitch(bool on);

	/*消息对话框*/
	void setMessageBox(const QString& title, const QString& text);

	bool isWorkThreadRunning();
	/*信号*/
signals:
	void setMessageBoxSignal(const QString& title, const QString& text);

	void scanCodeDlgSignal(const int& number);
protected:
	/*重写run*/
	virtual void run();

	/*设置错误*/
	void setLastError(const QString& err,bool msgBox = false);

	/*打开烧录器*/
	bool openAardvarkDevice();

	/*关闭烧录器*/
	bool closeAardvarkDevice();
private:
	/*是否为调试模式*/
	bool m_debugMode = false;

	/*线程是否退出*/
	bool m_quit = false;

	/*是否连接,用于工作*/
	bool m_connect = false;

	/*子线程是否正在工作*/
	bool m_childWork = false;

	/*子线程是否退出*/
	bool m_childQuit = false;

	/*扫描对话框显示*/
	bool m_scDlgShow = false;

	///*子线程中止,如已经连接正在烧录状态*/
	//bool m_childAbort = false;

	/*启用通道数*/
	int m_channelCount = 0;

	/*烧录器数量*/
	int m_aardvarkCount = 0;

	/*错误信息*/
	QString m_lastError = "No Error";

	/*单通道电源*/
	CItechSCPIMgr m_power6832;

	/*三通道电源*/
	CItechSCPIMgr6302 m_power6302;

	/*继电器封装类*/
	CMRDO16KNMgr m_relay;

	/*线程锁*/
	QMutex m_mutex;

	/*工作线程*/
	WorkThread* m_workThread = nullptr;

	/*JSON封装类*/
	JsonTool* m_jsonTool = nullptr;

	/*设备配置*/
	DeviceConfig* m_deviceConfig = nullptr;

	/*硬件配置*/
	HardwareConfig* m_hardwareConfig = nullptr;

	/*文件配置*/
	FileConfig* m_fileConfig = nullptr;

	/*阈值配置*/
	ThresholdConfig* m_thresholdConfig = nullptr;

	/*继电器配置*/
	RelayConfig* m_relayConfig = nullptr;

	/*保存烧录器端口号和序列号*/
	QMap<quint8, quint32> m_aardvarkPortAndSn;
};


/************************************************************************/
/* WorkThread类                                                         */
/************************************************************************/
class WorkThread : public QThread
{
	Q_OBJECT
public:
	/*构造*/
	explicit WorkThread(QObject* parent = nullptr);

	/*析构*/
	~WorkThread();

	/*获取Aardvark*/
	AardvarkMgr& getAardvark();

	/*设置父对象*/
	void setParent(QObject* parent);

	/*设置烧录器端口*/
	void setAardvarkPort(const int& port);

	/*设置电源通道*/
	void setPowerChannel(const int& channel);

	/*设置继电器端口*/
	void setRelayPort(const int& port);

	/*设置序列号*/
	void setAardvarkSn(const quint32& sn);

	/*初始化*/
	bool initInstance();

	/*获取错误*/
	const QString& getLastError();

	/************************************************************************/
	/* 其他函数                                                             */
	/************************************************************************/

	/*改变FLASH烧录状态*/
	bool changeFlashStatus();

	/*初始化网络烧录*/
	bool initNetworkBurn();

	/*控制供电*/
	bool controlPower(bool powerSwitch);

	/*保存校验bin文件*/
	bool saveBinFile(const QString& name, const char* data, const ulong& size);

	/************************************************************************/
	/* 烧录顺序                                                             */
	/************************************************************************/

	/*准备烧录*/
	bool prepareBurn();

	/*初始化地址*/
	bool initAddress(bool mask = false);

	/*读取坐标*/
	bool readCoordinate();

	/*写BIN文件*/
	bool alterBinFile();

	/*写入数据*/
	bool writeBinFile();

	/*重启电源*/
	bool restartPower();

	/*校验数据*/
	bool checkData();

	/*保存日志*/
	bool saveLog(bool success);

	/*等待同步*/
	bool waitSync(bool success);

	/************************************************************************/
	/* 获取时间日期                                                         */
	/************************************************************************/

	/*获取当前时间*/
	const QString getTime(bool fileFormat = true);
	
	/*获取当前日期*/
	const QString getDate();
	
	/*获取当前日期时间*/
	const QString getDateTime(bool fileFormat = true);

	/************************************************************************/
	/* 更新GUI线程                                                           */
	/************************************************************************/

	/*更新进度条*/
	void updateProgress(const int& progress);

	/*更新当前状态*/
	void updateCurrentStatus(const QString& status);

	/*更新烧录状态*/
	void updateBurnStatus(const burnStatus_t& status, const QString& err = QString());

	/*更新组标题*/
	void updateGroupTitle(const QString& title);

	/*设置定时器启动*/
	void setBurnTimerRun(bool go);

	/*设置烧录顺序*/
	void setBurnSequence(const burnSequence_t& sequence);

	const QString getAardvarkError();
	/*信号[同上]*/
signals:
	void updateProgressSignal(const int& progress);

	void updateCurrentStatusSiganl(const QString& status);

	void updateBurnStatusSiganl(const burnStatus_t& status, const QString& err);

	void updateGroupTitleSignal(const QString& title);

	void setBurnTimerRunSignal(bool run);
	/*槽*/
public slots:
	void progressTimerSlot();

	void getBurnTimerTimeSlot(const int& data);
protected:
	/*重写run*/
	virtual void run();

	/*设置错误*/
	void setLastError(const QString& err);
private:
	JsonTool* m_jsonTool = nullptr;

	/*文件配置*/
	FileConfig* m_fileConfig = nullptr;

	/*设备配置*/
	DeviceConfig* m_deviceConfig = nullptr;

	/*硬件配置*/
	HardwareConfig* m_hardwareConfig = nullptr;

	/*阈值配置*/
	ThresholdConfig* m_thresholdConfig = nullptr;

	/*电源通道*/
	int m_powerChannel = 0;

	/*继电器IO口*/
	int m_relayPort = 0;

	/*烧录器IO口*/
	int m_aardvarkPort = 0;

	/*用于访问ThreadHandler类*/
	ThreadHandler* m_threadHandler = nullptr;

	/*烧录顺序*/
	burnSequence_t m_testSequence = BurnSequence::BS_NONE;

	/*烧录类声明*/
	AardvarkMgr m_aardvark;

	/*错误信息*/
	QString m_lastError = "No Error";

	/*坐标数据*/
	uchar m_coordData[8];

	/*更新进度条定时器*/
	QTimer* m_progressTimer = nullptr;

	/*更新进度条数据*/
	int m_progressData[3];

	/*烧录计时器时间*/
	int m_burnTimerTime = 0;

	/*是否开始工作*/
	bool m_startWork = false;

	/*烧录器序列号*/
	quint32 m_aardvarkSn = 0;

	/*是否重新上下电过*/
	bool m_restartPower = false;

	/*A12网络烧录*/
	IspTool* m_ispTool = nullptr;
};