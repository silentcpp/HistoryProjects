#pragma once

/*
* @Detection.h不可单独include这个头文件,否则将会报错
* @notice1,如果需要写功能,请#include <Function.h>
* @notice2,如果需要写硬件,请#include <Hardware.h>
*/

#include "Types.h"

#pragma warning(disable:4838)
#pragma execution_character_set("utf-8")

//条码声明
extern QString g_code;

/*
* @Cc,采集卡命名空间声明
*/
namespace Cc {

	/*
	* @Mv800Proc,MV800采集卡回调函数
	*/
	void WINAPI Mv800Proc(const uchar* head, const uchar* bits, LPVOID param);

	/*
	* @Mil,MOR采集卡类声明
	*/
	class Mil;

	/*
	* @CaptureCard,通用采集卡类声明
	*/
	class CaptureCard;
}

/*
* @Nt,网络传输命名空间声明
*/
namespace Nt {
	/*
	* @DvrClient,DVR客户端类声明
	*/
	class DvrClient;

	/*
	* @SfrServer,SFR服务端类声明
	*/
	class SfrServer;
}

/*Detection*/
namespace Dt {
	/************************************************************************/
	/* Base Class                                                           */
	/************************************************************************/

	class Base : public QThread
	{
		Q_OBJECT
	public:
		/*构造*/
		explicit Base(QObject* parent = nullptr);

		/*虚析构*/
		virtual ~Base();

		/*获取错误*/
		const QString& getLastError();

		/*设置测试顺序*/
		void setTestSequence(int testSequence);

		/*设置检测类型*/
		void setDetectionType(BaseTypes::DetectionType type);

		/*获取检测类型*/
		static BaseTypes::DetectionType getDetectionType();
		
		/*获取检测名称*/
		static QString getDetectionName();

		/*设置SOC延时*/
		void setSocDelay(ulong delay);

		/*初始化实例*/
		virtual bool initInstance();

		/*
		* 初始化控制台窗口
		* @notice,调用此函数前,不可进行任何输出,
		* 否则重定向流将失败,你无法看到打印内容.
		*/
		bool initConsoleWindow();

		/*退出控制台窗口*/
		bool exitConsoleWindow();

		/*打开设备*/
		virtual bool openDevice();

		/*关闭设备*/
		virtual bool closeDevice();

		/*准备测试,重载1*/
		virtual bool prepareTest(ulong delay = START_DELAY);

		/*
		 准备测试,重载2
		 @param1,总线状态报文ID
		 @param2,启动超时
		 @notice,如果不需要等待ECU完全启动则param3,4忽略
		 @param3,完全启动的值
		 @param4,完全启动处理
		 @return,bool
		 */
		virtual bool prepareTest(int id, ulong timeout, int value = 0, MsgProc msgProc = nullptr);

		/*结束测试*/
		virtual bool finishTest(bool success);

		/*保存日志*/
		virtual bool saveLog(bool success);

		/*检测电流*/
		virtual bool checkCurrent();

		/*
		* 检测静态电流
		* @param1,是否打开ACC
		* @notice,如果接下来不检测休眠和唤醒setAcc则为true,
		* @param2,是否设置为16V电压
		* @return,bool
		*/
		virtual bool checkStaticCurrent(bool setAcc = false, bool set16Vol = true);

		/*检测电压*/
		virtual bool checkVoltage();

		/*清除DTC*/
		virtual bool clearDtc();

		/*
		* 检测版本号
		* @param1,读取DID之间的时间间隔
		* @param2,如果失败,重复读取多少次
		* @return,bool
		*/
		virtual bool checkVersion(ulong delay = 200, int tryTimes = 3);

		/*检测DTC*/
		virtual bool checkDtc();

		/*写入序列号*/
		bool writeSn(const std::function<bool()>& lambda);

		/*检测序列号*/
		bool checkSn(const std::function<bool()>& lambda);

		/*写入日期*/
		bool writeDate(const std::function<bool()>& lambda);

		/*检测日期*/
		bool checkDate(const std::function<bool()>& lambda);

		/*写入设置*/
		bool writeSet(const std::function<bool()>& lambda);

		/*
		* @setFnc,设置函数
		* @notice,此函数用于,处理一些没有在框架中的函数,
		* 将其放入到lambda中执行
		*/
		bool setFnc(const std::function<bool()>& lambda);

		/*输出CAN日志*/
		void outputCanLog(bool enable = true);

		/*保存CAN日志*/
		void saveCanLog(bool enable);

		/*设置CAN日志名*/
		void setCanLogName(const QString& modelName, const QString& code);

		/*刷新CAN日志缓冲区*/
		void flushCanLogBuffer();

		/*清空CAN缓冲区*/
		void clearCanBuffer();

		/*快速接收CAN消息*/
		int quickRecvCanMsg(MsgNode* msgNode, int maxSize, int ms);

		/*自动处理CAN消息,[重载1]*/
		bool autoProcessCanMsg(int id, int value, MsgProc msgProc, ulong timeout = 10000U);

		/*自动处理CAN消息拓展,[重载2]*/
		bool autoProcessCanMsgEx(IdList idList, ValList valList, MsgProc msgProc, ulong timeout = 10000U);

		/*设置Can处理函数[重载1]*/
		bool setCanProcessFnc(const char* name, const CanMsg& msg, const CanProcInfo& procInfo);

		/*设置Can处理函数[重载2]*/
		bool setCanProcessFnc(const char* name, const CanMsg& msg, int id, int value, CanProc proc);

		/*设置Can处理函数,拓展版[重载1]*/
		bool setCanProcessFncEx(const char* name, CanList list, const CanProcInfo& procInfo);

		/*设置Can处理函数,拓展版[重载2]*/
		bool setCanProcessFncEx(const char* name, CanList list, int id, int value, CanProc proc);

		/*设置UDS处理函数*/
		bool setUdsProcessFnc(const char* name, DidList list, int value, int size, UdsProc proc, ulong timeout = 10000U);

		/*设置UDS处理函数,拓展版*/
		bool setUdsProcessFncEx(const char* name, DidList list, ValList valList, int size, UdsProcEx procEx, ulong timeout = 10000U);

		/*
		 *自动回收,用于处理缓存,导致占用空间的问题
		 *@param1,路径列表
		 *@param2,后缀名列表
		 *@param3,几个月回收一次
		 *@return,void
		*/
		void autoRecycle(const QStringList& path,
			const QStringList& suffixName = { ".mp4",".jpg",".png",".bmp",".net",".run",".can" },
			int interval = 1);

		/*启用自动回收*/
		void enableRecycle(bool enable) { m_autoRecycle = enable; };

		/*设置回收后缀名*/
		void setRecycleSuffixName(const QStringList& suffixName) { m_recycleSuffixName = suffixName; }

		/*设置回收间隔月*/
		void setRecycleIntervalMonth(int interval) { m_recycleIntervalMonth = interval; }

		/************************************************************************/
		/* Get Local Function                                                   */
		/************************************************************************/
		static CanTransfer* getCanTransfer();

		static CanSender* getCanSender();

		static CItechSCPIMgr* getPowerDevice();

		static CMRDO16KNMgr* getRelayDevice();

		static CVoltageTestMgr* getVoltageDevice();

		static StaticCurrentMgr* getCurrentDevice();

		/************************************************************************/
		/* UDS                                                                  */
		/************************************************************************/

		/*设置访问等级*/
		void setAccessLevel(int udsLevel);

		/*设置诊断会话*/
		void setDiagnosticSession(int udsSession);

		/*还原访问等级*/
		void restoreAccessLevel();

		/*还原诊断会话*/
		void restoreDiagnosticSession();

		/*进入安全访问*/
		bool enterSecurityAccess(uchar session = SL_EXTENDED, uchar access = SAL_LEVEL2, int repeat = 3);

		/*通过DID读数据*/
		bool readDataByDid(uchar did0, uchar did1, uchar* data, int* size);

		/*通过DID写数据[重载1]*/
		bool writeDataByDid(uchar did0, uchar did1, const uchar* data, int size);

		/*通过DID写数据[重载2]*/
		bool writeDataByDid(uchar did0, uchar did1, const std::initializer_list<uchar>& data);

		/*通过DID写数据,不安全,拓展版本[重载1]*/
		bool writeDataByDidEx(const uchar* routine, uchar did0, uchar did1, const uchar* data, int size);

		/*通过DID写数据,拓展版本[重载2]*/
		bool writeDataByDidEx(const std::initializer_list<uchar>& routine, uchar did0, uchar did1, const uchar* data, int size);

		/*通过DID确认数据*/
		bool confirmDataByDid(uchar did0, uchar did1, const uchar* data, int size);

		/*安全通过DID写数据*/
		bool safeWriteDataByDid(uchar did0, uchar did1, const uchar* data, int size);

		/*获取UDS最终错误*/
		QString getUdsLastError() const;

		/************************************************************************/
		/* Log                                                                  */
		/************************************************************************/

		/*初始化检测日志*/
		void initDetectionLog();

		/*设置检测日志*/
		void setDetectionLog(BaseTypes::DetectionLog log = BaseTypes::DL_ALL, const std::function<void(const int&)>& fnc = nullptr);

		/*创建日志文件*/
		QString createLogFile(bool success);

		/*写入日志*/
		bool writeLog(bool success);

		/************************************************************************/
		/* Thread control                                                       */
		/************************************************************************/

		/*线程暂停*/
		void threadPause();

		/*线程是否暂停*/
		bool threadIsPause();

		/*线程继续*/
		void threadContinue();

		/*线程退出*/
		void threadQuit();

		/************************************************************************/
		/* GUI                                                                  */
		/************************************************************************/
		/*设置扫码对话框*/
		bool setScanCodeDlg(bool show = true);

		/*设置结束对话框*/
		void setUnlockDlg(bool show = true);

		/*消息对话框,只可以在子线程中使用*/
		void setMessageBox(const QString& title, const QString& text);

		/*消息对话框,拓展版*/
		void setMessageBoxEx(const QString& title, const QString& text, const QPoint& point = QPoint(0, 0));

		/*询问对话框,只可以在子线程中使用*/
		bool setQuestionBox(const QString& title, const QString& text);

		/*询问对话框,拓展版*/
		bool setQuestionBoxEx(const QString& title, const QString& text, const QPoint& point = QPoint(0, 0));

		/*设置测试结果*/
		void setTestResult(BaseTypes::TestResult testResult);

		/*设置当前状态*/
		void setCurrentStatus(const QString& status, bool systemStatus = false);

		/*列表控件中增加一个元素*/
		void addListItem(const QString& item, bool logItem = true);

		/*列表控件中增加一个元素,拓展版*/
		void addListItemEx(const QString& item);

		/*清空列表控件*/
		void clearListItem();

		/*设置下载对话框槽*/
		bool setDownloadDlg(BaseTypes::DownloadInfo* info);

		bool callPythonFnc();

		/*
		* 等待启动
		* @param1,启动延时
		* @return,bool
		*/
		virtual bool waitStartup(ulong delay);

		/*
		* @checkPing,检测是否Ping通
		* @notice,与操作系统有关,可能会不准确
		* @param1,IP地址
		* @param2,次数
		* @return,bool
		*/
		bool checkPing(const QString& address, int times);

		/*
		* @checkPing,检测是否Ping通
		* @param1,IP地址
		* @param2,端口
		* @param3,超时时间
		* @return,bool
		*/
		bool checkPing(const QString& address, int port, int timeout);
	protected:
		/*线程是否退出*/
		bool m_quit = false;

		/*是否连接*/
		bool m_connect = false;

		/*等待SOC启动延时*/
		ulong m_socDelay = 3000U;

		/*测试顺序*/
		int m_testSequence = TS_NO;

		/*所用时间*/
		size_t m_elapsedTime = 0;

		/*统计产品*/
		size_t m_total = 1;

		/*检测类型*/
		static BaseTypes::DetectionType m_detectionType;

		/*JSON工具类*/
		JsonTool* m_jsonTool = nullptr;

		/*默认配置*/
		DefConfig* m_defConfig = nullptr;

		/*硬件检测配置 */
		HwdConfig* m_hwdConfig = nullptr;

		/*UDS检测配置*/
		UdsConfig* m_udsConfig = nullptr;

		/*电源类*/
		static CItechSCPIMgr m_power;

		/*16路继电器类*/
		static CMRDO16KNMgr m_relay;

		/*电压表类*/
		static CVoltageTestMgr m_voltage;

		/*电流表*/
		static StaticCurrentMgr m_current;

		/*CAN连接管理*/
		static CanTransfer* m_canTransfer;

		/*UDS传输*/
		UdsTransfer* m_udsTransfer = nullptr;

		/*CAN发送者*/
		static CanSender* m_canSender;

		/*保存错误*/
		QString m_lastError = "No Error";

		/*日志链表*/
		QList<QString> m_logList;

		/*唤醒电流*/
		float m_rouseCurrent = 0.0f;

		/*矩阵算法*/
		CanMatrix m_matrix;

		void* m_core = nullptr;
	protected:
		/*设置错误信息,重载1*/
		void setLastError(const QString& error);

		/*设置错误信息,重载2*/
		void setLastError(const QString& error, bool addItem, bool msgBox = false);

		/*UDS编码转换*/
		bool udsEncodeConvert(VersonConfig* config);

	private:
		/*UDS等级*/
		int m_udsLevel = SAL_LEVEL1;

		/*UDS会话*/
		int m_udsSession = 0x03;

		/*启用自动回收*/
		bool m_autoRecycle = true;

		/*回收后缀名*/
		QStringList m_recycleSuffixName = {};

		/*回收间隔月*/
		int m_recycleIntervalMonth = -1;

	signals:
		/*更新图像信号*/
		void updateImageSignal(const QImage& image);

		/*设置消息对话框信号*/
		void setMessageBoxSignal(const QString& title, const QString& text);

		/*设置消息对话框拓展版信号*/
		void setMessageBoxExSignal(const QString& title, const QString& text, const QPoint& point);

		/*设置询问对话框信号*/
		void setQuestionBoxSignal(const QString& title, const QString& text, bool* result);

		/*设置询问对话框拓展版信号*/
		void setQuestionBoxExSignal(const QString& title, const QString& text, bool* result, const QPoint& point);

		/*设置测试结果信号*/
		void setTestResultSignal(BaseTypes::TestResult result);

		/*设置当前状态信号*/
		void setCurrentStatusSignal(const QString& status, bool append);

		/*设置扫码对话框信号*/
		void setScanCodeDlgSignal(bool show);

		/*设置解锁对话框信号*/
		void setUnlockDlgSignal(bool show);

		/*增加一个列表项目信号*/
		void addListItemSignal(const QString& item, bool logItem);

		/*清空列表控件信号*/
		void clearListItemSignal();

		/*设置下载对话框信号*/
		void setDownloadDlgSignal(BaseTypes::DownloadInfo* info);
	};

	/************************************************************************/
	/* Hardware Class                                                       */
	/************************************************************************/
	class Hardware : public Base {
		Q_OBJECT
	public:
		explicit Hardware(QObject* parent = nullptr);

		~Hardware();

	protected:
		virtual void run() override = 0;

	private:

	};

	/************************************************************************/
	/* Function Class                                                       */
	/************************************************************************/

	class Function : public Base {
		Q_OBJECT
	public:
		/*构造*/
		explicit Function(QObject* parent = nullptr);

		/*析构*/
		~Function();

		/*友元*/
		friend void WINAPI Cc::Mv800Proc(const uchar* head, const uchar* bits, LPVOID param);

		/*友元*/
		friend class Cc::Mil;

		/*友元*/
		friend class Cc::CaptureCard;

		/*初始化实例*/
		virtual bool initInstance();

		/*打开设备*/
		virtual bool openDevice();

		/*关闭设备*/
		virtual bool closeDevice();

		/*
		 *检测CAN唤醒休眠,[重载1]
		 *@param1,唤醒报文
		 *@param2,报文延时
		 *@param3,总线状态报文ID
		 *@param4,唤醒成功的值
		 *@param5,报文处理函数
		 *@return,bool
		*/
		virtual bool checkCanRouseSleep(const MsgNode& msg, ulong delay, int id, int value = 0, MsgProc msgProc = nullptr);

		/*
		* 检测CAN唤醒休眠,[重载2]
		* @param1,总线状态报文ID
		* @param2,唤醒成功的值
		* @param3,报文处理函数
		* @return,bool
		*/
		virtual bool checkCanRouseSleep(int id, int value = 0, MsgProc msgProc = nullptr);

		/************************************************************************/
		/* 图像控制                                                              */
		/************************************************************************/

		/*设置采集卡属性*/
		void setCaptureCardAttribute();

		/*开始采集卡采集数据*/
		void startCapture();

		/*停止采集卡采集数据*/
		void stopCapture();

		/*打开采集卡*/
		bool openCaptureCard();

		/*关闭采集卡*/
		bool closeCaptureCard();

		/*循环抓图,效率最高*/
		bool cycleCapture();

		/*保存分析图像*/
		bool saveAnalyzeImage(const QString& name, const IplImage* image, const CvSize& size = CvSize());

		/*在图像上画矩形*/
		inline void drawRectOnImage(IplImage* image);

		/*在图像上画矩形*/
		inline void drawRectOnImage(cv::Mat& mat);

		/*在图像上检测矩形*/
		bool checkRectOnImage(IplImage* cvImage, const RectConfig& rectConfig, QString& colorData);

		/*设置矩形类型*/
		void setRectType(FcTypes::RectType rectType = FcTypes::RT_SMALL);

		/*获取矩形类型*/
		FcTypes::RectType getRectType() const;

		/*还原矩形类型*/
		void restoreRectType();

		/*更新图像*/
		void updateImage(const QImage& image);

		/*显示图像*/
		void showImage(const IplImage* image, const QString& name = "image");

		/************************************************************************/
		/* Get                                                                  */
		/************************************************************************/
		inline Cc::Mil* getMil() { return m_mil; };

		inline CMV800Mgr* getMv800() { return &m_mv800; }

		inline Cc::CaptureCard* getCaptureCard() { return m_cap; }

		bool getCardConnectStatus();

		inline const int& getMilChannelId() { return m_cardConfig.channelId; }

		inline const int& getMv800ChannelId() { return m_cardConfig.channelId; }

		inline const int& getCaptureCardId() { return m_cardConfig.channelId; }

		const FcTypes::CardConfig* getCaptureCardConfig();

		/*设置采集状态*/
		void setCaptureStatus(bool capture);

		/*获取采集状态*/
		bool getCaptureStatus();
	protected:
		/*必须重写线程*/
		virtual void run() override = 0;

		/*目标分析图像*/
		IplImage* m_cvAnalyze = nullptr;

	private:
		/*类型*/
		FcTypes::RectType m_rectType = FcTypes::RT_NO;

		/*控件显示图像*/
		IplImage* m_cvPainting = nullptr;

		/*MIL采集卡*/
		Cc::Mil* m_mil = nullptr;

		/*MV800采集卡*/
		CMV800Mgr m_mv800;

		/*采集卡通用类*/
		Cc::CaptureCard* m_cap = nullptr;

		/*采集卡结构体*/
		FcTypes::CardConfig m_cardConfig;

		/*抓图*/
		bool m_capture = false;
	};

	/************************************************************************/
	/* AVM Class                                                            */
	/************************************************************************/
	class Avm : public Function {
		Q_OBJECT
	public:
		/*构造*/
		explicit Avm(QObject* parent = nullptr);

		/*析构*/
		~Avm();

		/*初始化实例*/
		virtual bool initInstance();

		/*
		* 设置led灯
		* @param1,开关
		* @return,bool
		*/
		void setLedLight(bool _switch);

		/*
		* 通过按键触发AVM
		* @param1,高电平延时
		* @param2,AVM反馈报文ID
		* @param3,AVM反馈成功的值
		* @param4,处理AVM反馈函数
		* @return,bool
		*/
		virtual bool triggerAvmByKey(ulong delay = 300, int id = 0, int value = 0, MsgProc proc = nullptr);

		/*
		* 通过报文触发AVM
		* @param1,触发AVM的报文
		* @param2,AVM反馈报文ID
		* @param3,AVM反馈成功的值
		* @param4,处理AVM反馈函数
		* @return,bool
		*/
		virtual bool triggerAvmByMsg(const CanMsg& msg, int id = 0, int value = 0, MsgProc proc = nullptr);

		/*检测视频出画不使用任何*/
		virtual bool checkVideoUseNot();

		/*
		* 检测视频出画使用报文[拓展版]
		* @param1,触发全景报文
		* @param2,触发全景成功报文
		* @param3,触发全景成功的值
		* @param4,触发全景成功函数处理
		* @return,bool
		*/
		virtual bool checkVideoUseMsg(const CanMsg& msg, int id, int value, MsgProc proc);

		/*
		* 检测视频出画使用按键
		* @param1,总线状态报文ID
		* @param2,进入全景成功的值
		* @param3,处理全景报文函数
		* @param4,高电平延时
		* @param5,触发成功延时
		* @return,bool
		*/
		virtual bool checkVideoUseKey(int id, int req, MsgProc proc, ulong hDelay = 300, ulong sDelay = 3000);

		/*检测视频出画使用人工
		* @return,bool
		*/
		virtual bool checkVideoUsePerson();

		/*
		* 检查单个图像使用报文
		* @param1,矩形类型
		* @param2,触发报文
		* @param3,成功报文
		* @param4,成功的值
		* @param5,处理函数
		* @param6,超时
		* @return,bool
		*/
		bool checkSingleImageUseMsg(FcTypes::RectType type, const CanMsg& msg,
			int id = 0, int value = 0, MsgProc proc = 0, ulong timeout = 10000U);

		/*
		* 检测AVM前后视图使用报文
		* @notice,[F]代表前,[R]代表后,
		* 默认全景加前,把切后报文写第一个,反之一样.
		* @param1,前后景报文列表
		* @param2,报文延时
		* @param3,接收ID
		* @param4,请求列表
		* @param5,lambda
		* @return,bool
		*/
		virtual bool checkFRViewUseMsg(CanList msgList, int id, ValList valList, MsgProc proc);

		/*
		* 检测按键电压
		* @param1,进入全景成功报文ID
		* @param2,进入全景成功的值
		* @param3,处理进入全景的报文
		* @param4,高电平延时
		* @param5,成功之后延时
		* @notice,延时取决于高电平电压是否准确
		* @return,bool
		*/
		virtual bool checkFRViewUseKey(int id, int value, MsgProc proc, ulong hDelay = 300U, ulong sDelay = 3000U);

		/*
		* 检测按键电压
		* @param1,高电平延时
		* @param1,成功之后延时
		* @notice,延时取决于高电平电压是否准确
		* @param2,进入全景成功报文ID
		* @param3,进入全景成功的值
		* @param4,处理进入全景的报文
		* @return,bool
		*/
		virtual bool checkKeyVoltage(ulong hDelay = 300U, ulong sDelay = 3000U,
			int id = 0, int value = 0, MsgProc proc = nullptr);

	protected:
		/*必须重写线程*/
		virtual void run() override = 0;
	private:
	};

	/************************************************************************/
	/* DVR Class                                                            */
	/************************************************************************/
	class Dvr : public Function {
		Q_OBJECT
	public:
		/*构造*/
		explicit Dvr(QObject* parent = nullptr);

		/*虚析构*/
		~Dvr();

		/*初始化实例*/
		virtual bool initInstance();

		/*开始测试*/
		virtual bool prepareTest(ulong delay = 30000U);

		/*结束测试*/
		virtual bool finishTest(bool success);

		/*设置系统状态报文*/
		void setSysStatusMsg(DvrTypes::SysStatusMsg msg);

		/*设置SD卡状态*/
		void setSdCardStatus(DvrTypes::SdCardStatus status);

		/*设置系统状态*/
		void setSystemStatus(DvrTypes::SystemStatus status);

		/*设置其他动作,[比如时间同步,激活控制器报文...]*/
		virtual bool setOtherAction() { return true; };

		/*获取所有状态
		* @param1,系统状态报文
		* @param2,所获取的状态值
		* @return,bool
		*/
		template<class T>bool getAllStatus(T& status);

		/*自动处理状态,[重载1]
		* @param1,系统状态报文
		* @param2,处理超时
		* @return,bool
		*/
		template<class T>bool autoProcessStatus(ulong timeout = 30000U);

		/*自动处理状态,[重载2]
		* @param1,系统状态报文
		* @param2,系统精确状态值
		* @param3,处理超时
		* @return,bool
		*/
		template<class T>bool autoProcessStatus(T value, ulong timeout = 30000U);

		/*检测DVR[重载1]
		* @param1,RTSP协议地址
		* @param2,是否使用WIFI
		* @param3,是否使用采集卡
		* @param4,是否下载视频
		* @return,bool
		*/
		bool checkDvr(const QString& rtspUrl, bool useWifi = true, bool useCard = false, bool downloadVideo = true);

		/*检测DVR[重载2]
		* @param1,是否使用WIFI
		* @param2,是否使用采集卡
		* @param3,是否下载视频
		* @return,bool
		*/
		bool checkDvr(bool useWifi = true, bool useCard = false, bool downloadVideo = true);

		/*设置声音和灯光*/
		bool setSoundLight(bool enable);

		/*声音和灯光是否开启*/
		bool getSoundLigth();

		/*设置声音*/
		bool setSound(bool enable);

		/*设置灯光*/
		bool setLight(bool enable);

		/*设置vlc媒体播放句柄*/
		void setVlcMediaHwnd(HWND vlcHwnd);

		/*使用vlc库调用rtsp播放文件*/
		bool vlcRtspStart(const QString& url);

		/*停止rtsp播放*/
		bool vlcRtspStop();

		/*获取文件列表,重载1*/
		bool getFileUrl(QString& url, DvrTypes::FilePath filePath);

		/*下载紧急录制文件,重载1*/
		bool downloadFile(const QString& url, const QString& dirName, bool isVideo = true);

		/*下载紧急录制文件,重载2*/
		bool downloadFile(const QString& url, DvrTypes::FileType types);

		/*设置下载文件目录*/
		void setDownloadFileDir(DvrTypes::FileType types, const QString& dirName);

		/*检测DVR光轴*/
		bool checkRayAxis(const QString& url, const QString& dirName);

		/*获取DVR解像度*/
		bool checkSfr(const QString& url, const QString& dirName);

		/*
		* 检测光轴解像度使用报文
		* @param1,CAN报文列表
		* @param2,接收报文ID
		* @param3,数值
		* @param4,lambda
		* @return,bool
		*/
		bool checkRayAxisSfrUseMsg(CanList list, int id, int req, MsgProc proc);

		/*
		* 检测光轴解像度使用网络
		* @return,bool
		*/
		bool checkRayAxisSfrUseNet();

		/*
		* 检测光轴解像度
		* @return,bool
		*/
		bool checkRayAxisSfr();

		/*格式化SD卡*/
		virtual bool formatSdCard(bool pauseRecord = true);

		/*卸载SD卡*/
		virtual bool umountSdCard();

		/*设置WIFI密码*/
		virtual bool changeWifiPassword();

		/*设置地址端口*/
		void setAddressPort(const QString& address, const ushort& port);

		/*网络拍照*/
		bool networkPhotoGraph();

		Misc::UpdateSfr* getUpdateSfr();

		Nt::SfrServer* getSfrServer();

		/*播放询问对话框*/
		int setPlayQuestionBox(const QString& title, const QString& text, const QPoint& point = QPoint(0, 0));
	signals:
		void setPlayQuestionBoxSignal(const QString&, const QString&, int* result, const QPoint& point);
	protected:
		/*必须重写线程*/
		virtual void run() override = 0;

		/*使用WIFI的必须重写此函数,为checkDvr多态使用*/
		virtual bool getWifiInfo(bool rawData = false, bool showLog = true);

		/*写入网络日志*/
		bool writeNetLog(const char* name, const char* data, size_t size);
	protected:
		/*WIFI*/
		WifiMgr m_wifiMgr;

		/*WIFI信息结构体*/
		WIFIInfo m_wifiInfo = { 0 };
	private:
		/*声音和灯是否打开*/
		bool m_soundLight = false;

		/*VLC*/
		HWND m_vlcHwnd = nullptr;

		libvlc_instance_t* m_vlcInstance = nullptr;

		libvlc_media_t* m_vlcMedia = nullptr;

		libvlc_media_player_t* m_vlcMediaPlayer = nullptr;

		Nt::DvrClient* m_dvrClient = nullptr;

		Nt::SfrServer* m_sfrServer = nullptr;

		/*照片路径*/
		QString m_photoPath = "PHODownload";

		/*视频路径*/
		QString m_videoPath = "EVTDownload";

		/*IP地址*/
		QString m_address = "10.0.0.10";

		/*端口*/
		ushort m_port = 2000;

		/*系统状态报文*/
		int m_sysStatusMsg = DvrTypes::SSM_BAIC_C62X;

		/*SD卡状态*/
		DvrTypes::SdCardStatus m_sdCardStatus = DvrTypes::SCS_NORMAL;

		/*系统状态*/
		DvrTypes::SystemStatus m_systemStatus = DvrTypes::SS_PAUSE_RECORD;

		Misc::UpdateSfr m_updateSfr;

		/*HASH码结构体用于模板判断*/
		struct HashCode {
			/*系统状态*/
			size_t systemStatus;

			/*WIFI状态*/
			size_t wifiStatus;

			/*以太网状态*/
			size_t ethernetStatus;

			/*SD卡状态*/
			size_t sdCardStatus;
		}m_hashCode;

		/*DVR文件列表,详情请查阅通讯协议*/
		struct FileList {
			size_t listCount;
			struct FileInfo {
				ushort index;

				uchar path;

				uchar type;

				uchar suffix;

				uchar reserved[3];

				size_t size;

				size_t date;
			}fileInfo[100];
		};
	};

	/************************************************************************/
	/* TAP Class                                                            */
	/************************************************************************/
	class Tap : public Function {
		Q_OBJECT
	public:
		explicit Tap(QObject* parent = nullptr);

		~Tap();

		virtual bool initInstance();

		virtual bool openDevice();

		virtual bool closeDevice();

		bool checkUSBByJson(const QString& url = "http://172.19.1.2:20001/info");
	protected:
		virtual void run() override = 0;
	private:
		/*串口工具*/
		SerialPort* m_serialPort = nullptr;

		/*TAP左右屏幕处理*/
		void screenUartHandler(const QString& port, const QByteArray& bytes);
	};

	/*
	* Module Class
	*/
	class Module : public Base {
		Q_OBJECT
	public:
		explicit Module(QObject* parent = nullptr);

		~Module();

		virtual bool initInstance();

		bool printLabel(const std::function<bool(void)>& fnc);
	protected:
		virtual void run() override = 0;

		QString getPrinterError();

		TSCPrinterMgr m_printer;
	private:
	};

	template<class T> inline bool Dvr::getAllStatus(T& status)
	{
		bool result = false, success = false;
		do
		{
			const size_t& statusCode = typeid(status).hash_code();
			MsgNode msg[512] = { 0 };
			size_t&& startTime = GetTickCount();
			clearCanBuffer();
			for (;;)
			{
				int size = quickRecvCanMsg(msg, 512, 100);
				for (int i = 0; i < size; i++)
				{
					if (msg[i].id == m_sysStatusMsg)
					{
						if (statusCode == m_hashCode.systemStatus)
						{
							status = static_cast<T>(msg[i].data[0] & 0x07);
							switch (status)
							{
							case DvrTypes::SS_INITIALIZING:setCurrentStatus("系统初始化中", true); break;
							case DvrTypes::SS_GENERAL_RECORD:setCurrentStatus("正常录制", true); break;
							case DvrTypes::SS_PAUSE_RECORD:setCurrentStatus("暂停录制", true); break;
							case DvrTypes::SS_HARDWARE_KEY:setCurrentStatus("紧急录制 按键", true); break;
							case DvrTypes::SS_CRASH_KEY:setCurrentStatus("紧急录制 碰撞", true); break;
							case DvrTypes::SS_UPDATE_MODE:setCurrentStatus("更新模式", true); break;
							case DvrTypes::SS_ERROR:setCurrentStatus("系统故障", true); break;
							default:setCurrentStatus("未知系统状态"); break;
							}
						}
						else if (statusCode == m_hashCode.wifiStatus)
						{
							if (m_sysStatusMsg == DvrTypes::SSM_BAIC_C62X)
							{
								status = static_cast<T>((msg[i].data[0] >> 4) & 0x07);
							}
							else if (m_sysStatusMsg == DvrTypes::SSM_CHJ_M01)
							{
								status = static_cast<T>((msg[i].data[1] >> 0) & 0x07);
							}

							switch (status)
							{
							case DvrTypes::WS_CLOSE:setCurrentStatus("WIFI已关闭", true); break;
							case DvrTypes::WS_INIT:setCurrentStatus("WIFI正在初始化", true); break;
							case DvrTypes::WS_NORMAL:setCurrentStatus("WIFI正常", true); break;
							case DvrTypes::WS_CONNECT:setCurrentStatus("WIFI正在连接", true); break;
							case DvrTypes::WS_ERROR:setCurrentStatus("WIFI错误", true); break;
							default:setCurrentStatus("未知WIFI状态", true); break;
							}

							if (status == DvrTypes::WS_NORMAL)
							{
								if (!getWifiInfo())
								{
									addListItem(getLastError());
									break;
								}
								success = m_wifiMgr.connect(m_wifiInfo);
								addListItem(Q_SPRINTF("连接WIFI %s", OK_NG(success)));
								if (!success)
								{
									addListItem(G_TO_Q_STR(m_wifiMgr.getLastError()));
									break;
								}
								addListItem("正在连接服务端,该过程大约需要1~20秒,请耐心等待...");
								success = m_dvrClient->connect(20);
								status = static_cast<T>(success ? DvrTypes::WS_CONNECTED : DvrTypes::WS_ERROR);
								m_dvrClient->disconnect();
								addListItem(Q_SPRINTF("连接服务端 %s", OK_NG(success)));
								if (success && m_sysStatusMsg == DvrTypes::SSM_CHJ_M01)
								{
									addListItem("等待系统稳定中,大约需要5秒,请耐心等待...");
									msleep(5000);
								}
							}
						}
						else if (statusCode == m_hashCode.ethernetStatus)
						{
							addListItem("正在连接服务端,该过程大约需要1~20秒,请耐心等待...");
							success = m_dvrClient->connect(20);
							status = static_cast<T>(success ? DvrTypes::ES_CONNECT : DvrTypes::ES_ERROR);
							m_dvrClient->disconnect();
							setCurrentStatus(Q_SPRINTF("以太网%s连接", success ? "已" : "未"), true);
							addListItem(Q_SPRINTF("连接服务端 %s", OK_NG(success)));
						}
						else if (statusCode == m_hashCode.sdCardStatus)
						{
							if (m_sysStatusMsg == DvrTypes::SSM_BAIC_C62X)
							{
								status = static_cast<T>(msg[i].data[1] & 0x07);
							}
							else if (m_sysStatusMsg == DvrTypes::SSM_CHJ_M01)
							{
								status = static_cast<T>((msg[i].data[0] >> 3) & 0x07);
							}

							switch (status)
							{
							case DvrTypes::SCS_NORMAL:setCurrentStatus("SD卡正常", true); break;
							case DvrTypes::SCS_NO_SD:setCurrentStatus("请插入SD卡", true); break;
							case DvrTypes::SCS_ERROR:setCurrentStatus("SD卡错误", true); break;
							case DvrTypes::SCS_NOT_FORMAT:setCurrentStatus("SD卡未格式化", true); break;
							case DvrTypes::SCS_INSUFFICIENT:setCurrentStatus("SD卡空间不足", true); break;
							case DvrTypes::SCS_SPEED_LOW:setCurrentStatus("SD卡速度低", true); break;
							case DvrTypes::SCS_USING:setCurrentStatus("SD卡正在使用中", true); break;
							default:setCurrentStatus("未知SD卡状态", true); break;
							}

							if (status == DvrTypes::SCS_USING)
							{
								status = static_cast<T>(DvrTypes::SCS_NORMAL);
							}
						}
						success = true;
						break;
					}
				}

				if (success || GetTickCount() - startTime > 2000)
				{
					break;
				}
			}

			if (!success)
			{
				break;
			}
			result = true;
		} while (false);
		return result;
	}

	template<class T> inline bool Dvr::autoProcessStatus(ulong timeout)
	{
		T status;
		const size_t& statusCode = typeid(status).hash_code();
		bool result = false, success = false;
		do
		{
			size_t&& startTime = GetTickCount();
			while (true)
			{

				if (!getAllStatus<T>(status))
				{
					setLastError("未收到报文或其他错误,请查阅运行日志");
					break;
				}

				DEBUG_INFO_EX("状态 %d", (int)status);
				if (statusCode == m_hashCode.systemStatus)
				{
					if (status == static_cast<T>(DvrTypes::SS_GENERAL_RECORD))
					{
						success = true;
						break;
					}
				}
				else if (statusCode == m_hashCode.wifiStatus)
				{
					if (status == static_cast<T>(DvrTypes::/*WS_NORMAL*/WS_CONNECTED))
					{
						success = true;
						break;
					}
				}
				else if (statusCode == m_hashCode.ethernetStatus)
				{
					if (status == static_cast<T>(DvrTypes::ES_CONNECT))
					{
						success = true;
						break;
					}
				}
				else if (statusCode == m_hashCode.sdCardStatus)
				{
					if (status == static_cast<T>(DvrTypes::SCS_NORMAL))
					{
						success = true;
						break;
					}
				}

				if (success || GetTickCount() - startTime > timeout)
				{
					setLastError("获取状态不满足条件,报错请查阅运行日志");
					break;
				}
			}

			if (!success)
			{
				break;
			}
			result = true;
		} while (false);
		return result;
	}

	template<class T> inline bool Dvr::autoProcessStatus(T value, ulong timeout)
	{
		T status;
		const size_t& statusCode = typeid(status).hash_code();
		bool result = false, success = false;
		do
		{
			size_t&& startTime = GetTickCount();
			while (true)
			{

				if (!getAllStatus<T>(status))
				{
					setLastError("未收到报文或其他错误,请查阅运行日志");
					break;
				}

				DEBUG_INFO_EX("状态 %d,数值 %d", (int)status, (int)value);
				if (statusCode == m_hashCode.systemStatus)
				{
					if (status == value)
					{
						success = true;
						break;
					}
				}
				else if (statusCode == m_hashCode.wifiStatus)
				{
					if (status == value)
					{
						success = true;
						break;
					}
				}
				else if (statusCode == m_hashCode.ethernetStatus)
				{
					if (status == value)
					{
						success = true;
						break;
					}
				}
				else if (statusCode == m_hashCode.sdCardStatus)
				{
					if (status == value)
					{
						success = true;
						break;
					}
				}

				if (success || GetTickCount() - startTime > timeout)
				{
					setLastError("获取状态不满足条件,报错请查阅运行日志");
					break;
				}
			}

			if (!success)
			{
				break;
			}
			result = true;
		} while (false);
		return result;
	}
}

namespace Cc {
	/*MIL采集卡线程*/
	class Mil : public QThread {
		Q_OBJECT
	public:
		/*构造*/
		explicit Mil(QObject* parent = nullptr);

		/*析构*/
		~Mil();

		/*打开MIL设备驱动*/
		bool open(const QString& name, int channel);

		/*关闭MIL设备驱动*/
		void close();

		/*是否打开*/
		bool isOpen();

		/*开始采集*/
		void startCapture();

		/*结束采集*/
		void stopCapture();

		/*获取错误信息*/
		const QString& getLastError();
	protected:
		/*重写run*/
		virtual void run();

		/*设置错误*/
		void setLastError(const QString& error);
	private:
		/*父线程指针*/
		Dt::Function* m_function = nullptr;

		/*MIL定义*/
		MIL_ID MilApplication = M_NULL, MilSystem = M_NULL, MilDisplay = M_NULL;
		MIL_ID MilDigitizer = M_NULL, MilImage = M_NULL, MilImage0 = M_NULL, MilImage2D = M_NULL;

		/*保存错误信息*/
		QString m_lastError = "No Error";

		bool m_capture = false;

		bool m_quit = false;

		bool m_open = false;

		int m_channel[2] = { M_CH0,M_CH1 };
	};

	class CaptureCard : public QObject {
		Q_OBJECT
	public:
		CaptureCard(QObject* parent);

		~CaptureCard();

		const QString& getLastError();

		bool openDevice(int id, int count);

		bool closeDevice();

		bool isOpen();

		bool startCapture();

		bool stopCapture();

		void setFPS(int fps);
	public slots:
		void getImageSlot();
	protected:
		void setLastError(const QString& error);
	private:
		VideoCapture m_video;

		Mat m_mat;

		QTimer m_timer;

		int m_fps = 40;

		QString m_lastError = "No Error";

		Dt::Function* m_function = nullptr;

		bool m_open = false;

		double m_scalew = 1.0f;

		double m_scaleh = 1.0f;
	};
}

/*Network transmission*/
namespace Nt {

	/************************************************************************/
	/* SFR服务端,用于与SFR APP进行通讯,此处用作服务端                       */
	/************************************************************************/
	class SfrServer {
	public:
		SfrServer();

		~SfrServer();

		bool startListen(const ushort& port = 2000);

		bool getSfr(const char* filePath, float& sfr);

		int send(const char* buffer, int len);

		int recv(char* buffer, int len);

		void closeListen();

		const QString& getLastError();

		static void sfrProcThread(void* arg);
	protected:
		void setLastError(const QString& error);
	private:
		SOCKET m_socket = INVALID_SOCKET;

		SOCKET m_client = INVALID_SOCKET;

		sockaddr_in m_sockAddr = { 0 };

		QString m_lastError = "No error";

		bool m_quit = false;
	};

	/************************************************************************/
	/* DVR客户端,用于与DVR服务端通讯                                        */
	/************************************************************************/
	class DvrClient {
	public:
		DvrClient();

		DvrClient(const QString& address, ushort port);

		~DvrClient();

		void setAddressPort(const QString& address, const ushort& port);

		bool connect(int count = 10);

		bool connect(const QString& address, ushort port, int count = 10);

		void disconnect();

		int send(const char* buffer, int len);

		int recv(char* buffer, int len);

		bool sendFrameData(const char* buffer, int len, uchar cmd, uchar sub);

		bool recvFrameData(char* buffer, int* const len);

		bool sendFrameDataEx(const std::initializer_list<char>& buffer, uchar cmd, uchar sub);

		bool sendFrameDataEx(const char* buffer, int len, uchar cmd, uchar sub);

		bool recvFrameDataEx(char* buffer, int* const len, uchar cmd, uchar sub);

		const size_t crc32Algorithm(uchar const* memoryAddr, size_t memoryLen, size_t oldCrc32);

		const char* getAddress();

		const ushort& getPort();

		const QString& getLastError();
	protected:
		void setLastError(const QString& error);
	private:
		QString m_lastError = "No error";

		SOCKET m_socket = INVALID_SOCKET;

		SOCKADDR_IN m_sockAddr = { 0 };

		char m_address[32] = { 0 };

		ushort m_port = 2000;

		bool m_connected = false;

		bool m_disconnected = false;
	};
}

