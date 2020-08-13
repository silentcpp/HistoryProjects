#pragma once
#include "Types.h"
#pragma warning(disable:4838)
#pragma execution_character_set("utf-8")

/************************************************************************/
/* namespace declare                                                    */
/************************************************************************/
namespace Cc {
	void WINAPI Mv800Proc(const uchar* head, const uchar* bits, LPVOID param);
}

namespace Nt {
	class DvrClient;

	class SfrServer;
}

namespace Misc {
	namespace Var {
		static QString appendName;
	}

	/*Cv图像转Qt图像*/
	bool cvImageToQtImage(IplImage* cv, QImage* qt);

	/*通过URL获取文件名*/
	const QString getFileNameByUrl(const QString& url);

	/*通过路径获取文件名*/
	const QString getFileNameByPath(const QString& path);

	/*获取当前文件名*/
	const QString getCurrentFileName();

	/*获取当前目录*/
	const QString getCurrentDir();

	/*创建路径*/
	bool makePath(const QString& path);

	/*获取APP版本号*/
	const QString getAppVersion();
	
	/*设置APP附加名*/
	void setAppAppendName(const QString& name);

	/*获取APP附加名*/
	const QString getAppAppendName();

	/*通过版本号重命名APP*/
	bool renameAppByVersion(QWidget* widget);

	/*启动应用程序*/
	bool startApp(const QString& name, const int& show);

	/*结束应用程序*/
	bool finishApp(const QString& name);

	/*获取当前时间*/
	const QString getCurrentTime(bool fileFormat = false);

	/*获取当前日期*/
	const QString getCurrentDate(bool fileFormat = false);

	/*获取当前时间日期*/
	const QString getCurrentDateTime(bool fileFormat = false);

	/*通过路径获取文件列表*/
	void getFileListByPath(const QString& path, QStringList& fileList);

	/*通过后缀名获取文件列表*/
	const QStringList getFileListBySuffixName(const QString& path, const QStringList& suffix);

	class ThemeFactory {
	public:
		/*构造*/
		inline ThemeFactory() {}

		/*析构*/
		inline ~ThemeFactory() {}

		/*获取主题列表*/
		inline static const QStringList getThemeList()
		{
			return QStyleFactory::keys();
		}

		/*随机选择一个主题*/
		inline static void randomTheme()
		{
			setTheme(getThemeList().value(qrand() % getThemeList().size()));
		}

		/*设置主题*/
		inline static void setTheme(const QString& theme = QString("Fusion"))
		{
			qApp->setStyle(QStyleFactory::create(theme));
			QPalette palette;
			palette.setColor(QPalette::Window, QColor(53, 53, 53));
			palette.setColor(QPalette::WindowText, Qt::white);
			palette.setColor(QPalette::Base, QColor(15, 15, 15));
			palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
			palette.setColor(QPalette::ToolTipBase, Qt::white);
			palette.setColor(QPalette::ToolTipText, Qt::white);
			palette.setColor(QPalette::Text, Qt::white);
			palette.setColor(QPalette::Button, QColor(53, 53, 53));
			palette.setColor(QPalette::ButtonText, Qt::white);
			palette.setColor(QPalette::BrightText, Qt::red);
			palette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
			palette.setColor(QPalette::HighlightedText, Qt::black);
			qApp->setPalette(palette);
		}

		/*设置边框为圆角*/
		inline static void setBorderRadius(QWidget* widget)
		{
			QBitmap bmp(widget->size());
			bmp.fill();
			QPainter p(&bmp);
			p.setPen(Qt::NoPen);
			p.setBrush(Qt::black);
			p.drawRoundedRect(bmp.rect(), 20, 20);
			widget->setMask(bmp);
		}
	};
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
		Base(QObject* parent = nullptr);

		/*虚析构*/
		virtual ~Base();

		/*获取错误*/
		const QString& getLastError();

		/*设置测试顺序*/
		void setTestSequence(const int& testSequence);

		/*设置检测类型*/
		void setDetectionType(const BaseTypes::DetectionType& type);

		/*获取检测类型*/
		const BaseTypes::DetectionType& getDetectionType();

		/*初始化实例*/
		virtual bool initInstance();

		/*初始化控制台窗口*/
		bool initConsoleWindow();

		/*退出控制台窗口*/
		void exitConsoleWindow();

		/*打开设备*/
		virtual bool openDevice();

		/*关闭设备*/
		virtual bool closeDevice();

		/*准备测试,重载1*/
		virtual bool prepareTest(LaunchProc launchProc = nullptr, void* args = nullptr);

		/*准备测试,重载2*/
		virtual bool prepareTest(LaunchProcEx lauProcEx, void* args, const int& request = 0, MsgProc msgProc = nullptr);

		/*
		 准备测试,重载3
		 @param1,总线状态报文ID
		 @param2,启动超时
		 @notice,如果不需要等待ECU完全启动则param3,4忽略
		 @param3,完全启动请求
		 @param4,完全启动处理
		 @return,bool
		 */
		virtual bool prepareTest(const int& id, const ulong& delay = 20000U, const int& req = 0, MsgProc msgProc = nullptr);

		/*设置启动延时*/
		void setStartDelay(const size_t& delay);

		/*结束测试*/
		virtual bool finishTest(bool success);

		/*保存日志*/
		virtual bool saveLog(bool success);
		
		/*检测电流*/
		virtual bool checkCurrent();

		/*检测静态电流*/
		virtual bool checkStaticCurrent(const ulong& delay = 6000U);

		/*检测电压*/
		virtual bool checkVoltage();

		/*清除DTC*/
		virtual bool clearDtc();

		/*检测版本号*/
		virtual bool checkVersion();

		/*检测DTC*/
		virtual bool checkDtc();
		
		/*输出CAN日志*/
		void outputCanLog(bool enable = true);

		/*保存CAN日志*/
		void saveCanLog(bool enable = true);

		/*设置CAN日志名*/
		void setCanLogName(const QString& detectionName, const QString& modelName, const QString& code);

		/*刷新CAN日志缓冲区*/
		void flushCanLogBuffer();

		/*清空CAN接收缓冲区*/
		void clearCanRecvBuffer();

		/*快速接收CAN消息*/
		const int quickRecvCanMsg(MsgNode* msgNode, const int& maxSize, const int& ms);

		/*自动处理CAN消息*/
		bool autoProcessCanMsg(const int& id, const int& request, MsgProc msgProc, const ulong& delay = 10000U);

		/*自动模板CAN函数*/
		bool autoTemplateCanFnc(const char* name, const int& id, const int& req, MsgProc proc, MsgList msg = {}, const ulong& delay = 0);

		/************************************************************************/
		/* Get Local Function                                                   */
		/************************************************************************/
		static IConnMgr* getCanConnect();

		static CanSender* getCanSender();

		const float& getCanRouseCur() const;

		CItechSCPIMgr& getPower();

		static bool getOutputRunLog() { return m_outputRunLog; };

		/************************************************************************/
		/* UDS                                                                  */
		/************************************************************************/

		/*设置访问等级*/
		void setAccessLevel(const int& udsLevel);

		/*设置诊断会话*/
		void setDiagnosticSession(const int& udsSession);

		/*还原访问等级*/
		void restoreAccessLevel();

		/*还原诊断会话*/
		void restoreDiagnosticSession();

		/*进入安全访问*/
		bool enterSecurityAccess(const uchar& session = 0x03, const uchar& access = 0x01);

		/*通过DID读数据*/
		bool readDataByDid(const uchar& did0, const uchar& did1, int* size, uchar* data);

		/*通过DID写数据*/
		bool writeDataByDid(const uchar& did0, const uchar& did1, const int& size, const uchar* data);

		/*通过DID写数据,拓展版本*/
		bool writeDataByDidEx(const uchar* routine, const uchar& did0, const uchar& did1, const int& size, const uchar* data);

		/*通过DID确认数据*/
		bool confirmDataByDid(const uchar& did0, const uchar& did1, const int& size, const uchar* data);

		/*获取UDS最终错误*/
		const QString getUdsLastError();

		/************************************************************************/
		/* Log                                                                  */
		/************************************************************************/

		/*初始化检测日志*/
		void initDetectionLog();

		void setDetectionLog(const BaseTypes::DetectionLog& log = BaseTypes::DL_ALL, const std::function<void(const int&)>& fnc = nullptr);

		/*创建日志文件*/
		const QString createLogFile(bool success);

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
		void setScanCodeDlg(bool show = true);

		/*设置结束对话框*/
		void setUnlockDlg(bool show = true);

		/*消息对话框,只可以在子线程中使用*/
		void setMessageBox(const QString& title, const QString& text);

		/*消息对话框,拓展版*/
		void setMessageBoxEx(const QString& title, const QString& text, const QPoint& point = QPoint(0, 0));

		/*询问对话框,只可以在子线程中使用*/
		bool setQuestionBox(const QString& title, const QString& text, bool auth = false);

		/*询问对话框,拓展版*/
		bool setQuestionBoxEx(const QString& title, const QString& text, const QPoint& point = QPoint(0, 0));

		/*设置测试结果*/
		void setTestResult(const BaseTypes::TestResult& testResult);

		/*设置当前状态*/
		void setCurrentStatus(const QString& status, bool systemStatus = false);

		/*列表控件中增加一个元素*/
		void addListItem(const QString& item, bool logItem = true);

		/*列表控件中增加一个元素,拓展版*/
		void addListItemEx(const QString& item);

		/*清空列表控件*/
		void clearListItem();

		/*认证信号*/
		bool setAuthDlg(const int& flag = 0);
	public:
		/*保存错误*/
		static QString m_lastError;

		/*日志链表*/
		static QList<QString> m_logList;
	protected:
		/*线程是否退出*/
		bool m_quit = false;

		/*是否连接*/
		bool m_connect = false;

		/*测试顺序*/
		int m_testSequence = TS_NO;

		/*所用时间*/
		size_t m_elapsedTime = 0;

		/*统计产品*/
		size_t m_total = 1;

		/*检测类型*/
		BaseTypes::DetectionType m_detectionType = BaseTypes::DT_AVM;

		/*JSON工具类*/
		JsonTool* m_jsonTool = nullptr;

		/*默认配置*/
		DefConfig* m_defConfig = nullptr;

		/*硬件检测配置 */
		HwdConfig* m_hwdConfig = nullptr;

		/*UDS检测配置*/
		UdsConfig* m_udsConfig = nullptr;

		/*电源类*/
		CItechSCPIMgr m_power;

		/*16路继电器类*/
		CMRDO16KNMgr m_relay;

		/*电压表类*/
		CVoltageTestMgr m_voltage;

		/*CAN连接工厂*/
		CConnFactory m_canConnFactory;

		/*CAN连接管理*/
		static IConnMgr* m_canConnMgr;

		/*UDS工厂*/
		CUdsFactory m_udsFactory;

		/*UDS申请管理*/
		IUdsApplyMgr* m_udsApplyMgr = nullptr;

		/*CAN发送者*/
		static CanSender m_canSender;

	protected:
		/*设置错误信息,重载1*/
		void setLastError(const QString& error);

		/*设置错误信息,重载2*/
		void setLastError(const QString& error, bool addItem, bool msgBox = false);

		/*UDS编码转换*/
		bool udsEncodeConvert(VersonConfig* config);

		/*获得忠告*/
		static const char* getAdvice();
	private:
		/*UDS等级*/
		int m_udsLevel = SAL_LEVEL1;

		/*UDS会话*/
		int m_udsSession = 0x03;

		/*启动延时*/
		size_t m_startDelay = 15000;

		/*输出运行日志*/
		static bool m_outputRunLog;
	signals:
		/*更新图像信号*/
		void updateImageSignal(const QImage& image);

		/*设置消息对话框信号*/
		void setMessageBoxSignal(const QString& title, const QString& text);

		/*设置消息对话框拓展版信号*/
		void setMessageBoxExSignal(const QString& title, const QString& text, const QPoint& point);

		/*设置询问对话框信号*/
		void setQuestionBoxSignal(const QString& title, const QString& text, bool* result, bool auth);

		/*设置询问对话框拓展版信号*/
		void setQuestionBoxExSignal(const QString& title, const QString& text, bool* result, const QPoint& point);

		/*设置测试结果信号*/
		void setTestResultSignal(const BaseTypes::TestResult& result);

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

		/*认证信号*/
		void setAuthDlgSignal(bool* result, const int& flag);
	};

	/************************************************************************/
	/* Hardware Class                                                       */
	/************************************************************************/
	class Hardware :public Base {
		Q_OBJECT
	public:
		Hardware(QObject* parent = nullptr);

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
		Function(QObject* parent = nullptr);

		/*析构*/
		~Function();

		/*友元*/
		friend void WINAPI Cc::Mv800Proc(const uchar* head, const uchar* bits, LPVOID param);

		/*初始化实例*/
		virtual bool initInstance();

		/*打开设备*/
		virtual bool openDevice();

		/*关闭设备*/
		virtual bool closeDevice();

		/*检测CAN唤醒休眠,重载1[已废弃]*/
		virtual bool checkCanRouseSleep(const MsgNode& msg, const ulong& delay, LaunchProc launchProc, void* args);

		/*检测CAN唤醒休眠,重载2[已废弃]*/
		virtual bool checkCanRouseSleep(const MsgNode& msg, const ulong& delay, LaunchProcEx lauProcEx, void* args, const int& request = 0, MsgProc msgProc = nullptr);
		
		/*
		 *检测CAN唤醒休眠,重载3
		 *@param1,唤醒报文
		 *@param2,报文延时
		 *@param3,总线状态报文ID
		 *@param4,唤醒成功请求
		 *@param5,lambda
		 *@return,bool
		*/
		virtual bool checkCanRouseSleep(const MsgNode& msg, const ulong& delay, const int& id, const int& req = 0, MsgProc msgProc = nullptr);
		
		/************************************************************************/
		/* 图像控制                                                              */
		/************************************************************************/

		/*设置采集卡属性*/
		void setCaptureCardAttribute();

		/*开始采集卡采集数据*/
		bool startCaptureCard();

		/*停止采集卡采集数据*/
		bool endCaptureCard();

		/*循环抓图,效率最高*/
		bool cycleCapture();

		/*保存分析图像*/
		bool saveAnalyzeImage(const QString& name, const IplImage* image, const CvSize& size);

		/*在图像上画矩形*/
		inline void drawRectOnImage();

		/*在图像上检测矩形*/
		bool checkRectOnImage(IplImage* cvImage, const rectConfig_t& rectConfig, QString& colorData);

		/*设置矩形类型*/
		void setRectType(const FcTypes::RectType& rectType = FcTypes::RT_SMALL);

		/*获取矩形类型*/
		const FcTypes::RectType& getRectType();

		/*还原矩形类型*/
		void restoreRectType();

		/*更新图像*/
		void updateImage(const QImage& image);

		/*显示图像*/
		void showImage(const IplImage* image, const QString& name = "image");

		/*设置CANID*/
		void setCanId(const int& id);

		/*设置Mil采集卡通道ID*/
		void setMilChannelId(const int& id);

		/*设置Mv800采集卡通道ID*/
		void setMv800ChannelId(const int& id);

		/************************************************************************/
		/* Get                                                                  */
		/************************************************************************/
		inline MilCC* getMil() { return &m_mil; };

		inline CMV800Mgr* getMv800() { return &m_mv800; }

		inline bool isCapture() { return m_capture; };
		
		inline const int& getMilChannelId() { return m_milChannelId; }

		inline const int& getMv800ChannelId() { return m_mv800ChannelId; }
		
		inline const FcTypes::CardConfig& getCardConfig() { return m_cardConfig; };
	public slots:
		void getChannelImageSlot(const int& channelID, const IplImage* image);
	protected:
		/*必须重写线程*/
		virtual void run() override = 0;

		/*目标分析图像*/
		IplImage* m_cvAnalyze = nullptr;

		/*
		 *自动回收,用于处理下载下来的视频和照片,导致占用的问题
		 *@param1,路径列表
		 *@param2,后缀名列表
		 *@param3,几个月回收一次
		 *@return,void
		*/
		void autoRecycle(const QStringList& path,
			const QStringList& suffixName = { ".mp4",".jpg",".png",".bmp" },
			const int& interval = 3);

		/*启用自动回收*/
		void enableRecycle(bool enable) { m_autoRecycle = enable; };

		/*设置回收后缀名*/
		void setRecycleSuffixName(const QStringList& suffixName) { m_recycleSuffixName = suffixName; }

		/*设置回收间隔月*/
		void setRecycleIntervalMonth(const int& interval) { m_recycleIntervalMonth = interval; }
	private:
		/*类型*/
		FcTypes::RectType m_rectType = FcTypes::RT_NO;

		/*控件显示图像*/
		IplImage* m_cvPainting = nullptr;

		/*MIL采集卡*/
		MilCC m_mil;

		/*MV800采集卡*/
		CMV800Mgr m_mv800;

		/*采集卡结构体*/
		FcTypes::CardConfig m_cardConfig;

		/*抓图*/
		bool m_capture = false;

		/*CANID*/
		int m_canId = 0;

		/*启用自动回收*/
		bool m_autoRecycle = true;

		/*回收后缀名*/
		QStringList m_recycleSuffixName = {};

		/*回收间隔月*/
		int m_recycleIntervalMonth = -1;

		/*MIL采集卡通道ID*/
		int m_milChannelId = 0;

		/*MV800采集卡通道ID,AV2是0,AV1是1*/
		int m_mv800ChannelId = 1;
	};

	/************************************************************************/
	/* AVM Class                                                            */
	/************************************************************************/
	class Avm : public Function {
		Q_OBJECT
	public:
		/*构造*/
		Avm(QObject* parent = nullptr);

		/*析构*/
		~Avm();

		/*初始化实例*/
		virtual bool initInstance();

		/*通过按键触发AVM*/
		void tiggerAVMByKey();

		/*设置led灯*/
		void setLedLight(bool _switch);

		/*使用报文检测AVM*/
		bool checkAVMUseMsg(const MsgNode& msg, const ulong& delay, const int& id, const int& req, MsgProc msgProc);

		/*检测AVM使用按键,重载1[已废弃]*/
		bool checkAVMUseKey(LaunchProc launchProc, RequestProc requestProc, void* args, const int& request, const ulong& delay = 0U);

		/*检测AVM使用按键,重载2[已废弃]*/
		bool checkAVMUseKey(LaunchProcEx launchProcEx, void* args, ReqList lauList, MsgProc lauFnc, RequestProcEx requestProcEx,
			ReqList reqList, MsgProc reqFnc, const ulong& delay = 0U);

		/*检测AVM使用按键,重载3
		 *@param1,总线状态报文ID
		 *@param2,启动成功请求
		 *@param3,lambda
		 *@param4,如果无法获取启动成功状态,则次处填写延时,否则0
		 *@param5,进入全景请求
		 *@param6,lambda
		 *@return,bool
		*/
		bool checkAVMUseKey(const int& id, const int& req0, MsgProc msgProc0, const ulong& delay, const int& req1, MsgProc msgProc1);

		/*检测AVM前后视图,重载1[已废弃]*/
		bool checkAVMFRView(MsgList msgList, const ulong& msgDelay, RequestProc requestProc = nullptr, void* args = nullptr, const int& request = 0);

		/*检测AVM前后视图,重载2[已废弃]*/
		bool checkAVMFRView(MsgList msgList, const ulong& msgDelay, RequestProcEx reqProcEx, void* args, ReqList reqList, MsgProc reqFnc);

		/*检测AVM前后视图,重载3
		 *@notice,[F]代表前,[R]代表后
		 *@param1,前后景报文列表
		 *@param2,报文延时
		 *@param3,接收ID
		 *@param4,请求列表
		 *@param5,lambda
		 *@return,bool
		 */
		bool checkAVMFRView(MsgList msgList, const ulong& msgDelay, const int& id, ReqList reqList, MsgProc msgProc);
	protected:
		/*必须重写线程*/
		virtual void run() override = 0;
	private:
	};

	/************************************************************************/
	/* DVR Class                                                            */
	/************************************************************************/
	class Dvr :public Function {
		Q_OBJECT
	public:
		/*构造*/
		Dvr(QObject* parent = nullptr);

		/*虚析构*/
		~Dvr();

		/*初始化实例*/
		virtual bool initInstance();

		/*开始测试*/
		virtual bool prepareTest(LaunchProc launchProc = nullptr, void* args = nullptr);

		/*结束测试*/
		virtual bool finishTest(bool success);

		/*开始时间同步*/
		virtual void startTimeSync();

		/*停止时间同步*/
		virtual void stopTimeSync();

		/*获取DVR所有状态*/
		template<class T>bool getAllStatus(T& status);

		/*自动处理DVR状态*/
		template<class T>bool autoProcessStatus();

		/*设置声音和灯光*/
		bool setSoundLight(bool enable);

		/*声音和灯光是否开启*/
		bool getSoundLigth();

		/*设置vlc媒体播放句柄*/
		void setVlcMediaHwnd(HWND vlcHwnd);

		/*使用vlc库调用rtsp播放文件*/
		bool vlcRtspStart(const QString& url);

		/*停止rtsp播放*/
		bool vlcRtspStop();

		/*DVR网络通讯协议算法*/
		const size_t crc32Algorithm(uchar const* memoryAddr, const size_t& memoryLen, const size_t& oldCrc32);

		/*此函数处理的结果不正确,不要使用*/
		bool crcVerify(const uchar* data, const size_t& length, const size_t& oldCrc32);

		/*获取文件列表,重载1*/
		bool getFileUrl(QString& url, const DvrTypes::FilePath& filePath, const QString& address, const ushort& port);

		/*获取文件列表,重载2*/
		bool getFileUrl(QString& url, const DvrTypes::FilePath& filePath);

		/*下载紧急录制文件,重载1*/
		bool downloadFile(const QString& url, const QString& dirName, bool isVideo = true);

		/*下载紧急录制文件,重载2*/
		bool downloadFile(const QString& url, const DvrTypes::FileType& types);

		/*设置下载文件目录*/
		void setDownloadFileDir(const DvrTypes::FileType& types, const QString& dirName);

		/*检测DVR光轴*/
		bool checkRayAxis(const QString& url, const QString& dirName);

		/*获取DVR解像度*/
		bool checkSfr(const QString& url, const QString& dirName);

		/*
		 *检测光轴及图像解析度
		 *@param1,拍照报文
		 *@param2,报文延时
		 *@param3,发送报文类型
		 *@param4,报文次数
		 *@param5,接收报文ID
		 *@param6,请求结果
		 *@param7,lambda
		 *@return,bool
		*/
		bool checkRayAxisSfr(const MsgNode& msg, const int& delay, const SendType& st, const int& count, const int& id, const int& req, MsgProc proc);

		/*格式化DVR SD卡*/
		bool formatSdCard(const DvrTypes::FormatSdCard& flag);

		/*设置地址端口*/
		void setAddressPort(const QString& address, const ushort& port);
	protected:
		/*必须重写线程*/
		virtual void run() override = 0;

		/*写入网络日志*/
		bool writeNetLog(const char* name, const char* data, const size_t& size);
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
	private:
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
		Tap(QObject* parent = nullptr);

		~Tap();

		virtual bool initInstance();

		virtual bool openDevice();

		virtual bool closeDevice();

		bool checkUSBByJson(const QString& url = "http://172.19.1.2:20001/info");
	protected:
		virtual void run() override = 0;
	private:
		/*串口工具*/
		SerialPortTool* m_serialPortTool = nullptr;

		/*TAP左右屏幕处理*/
		void screenUartHandler(const QString& port,const QByteArray& bytes);
	};

	/************************************************************************/
	/* Module Class                                                         */
	/************************************************************************/
	class Module : public Dvr {
		Q_OBJECT
	public:
		Module(QObject* parent = nullptr);

		~Module();
	protected:

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
			m_canConnMgr->ClearRecBuffer();
			for (;;)
			{
				int size = m_canConnMgr->QuickReceive(msg, 512, 100);
				for (int i = 0; i < size; i++)
				{
					if (msg[i].id == 0x5A0)
					{
						if (statusCode == m_hashCode.systemStatus)
						{
							status = static_cast<T>(msg[i].ucData[0] & 0x07);
							switch (status)
							{
							case DvrTypes::SS_INITIALIZING:setCurrentStatus("系统初始化中", true); break;
							case DvrTypes::SS_GENERAL_RECORD:setCurrentStatus("正常录制", true); break;
							case DvrTypes::SS_PAUSE_RECORD:setCurrentStatus("暂停录制[缺少SD卡]", true); break;
							case DvrTypes::SS_HARDWARE_KEY:setCurrentStatus("紧急录制 按键", true); break;
							case DvrTypes::SS_CRASH_KEY:setCurrentStatus("紧急录制 碰撞", true); break;
							case DvrTypes::SS_UPDATE_MODE:setCurrentStatus("更新模式", true); break;
							case DvrTypes::SS_ERROR:setCurrentStatus("系统故障", true); break;
							default:break;
							}
						}
						else if (statusCode == m_hashCode.wifiStatus)
						{
							status = static_cast<T>((msg[i].ucData[0] >> 4) & 0x07);
							switch (status)
							{
							case DvrTypes::WS_CLOSE:setCurrentStatus("WIFI已关闭", true); break;
							case DvrTypes::WS_INIT:setCurrentStatus("WIFI正在初始化", true); break;
							case DvrTypes::WS_NORMAL:setCurrentStatus("WIFI正常", true); break;
							case DvrTypes::WS_CONNECT:setCurrentStatus("WIFI正在连接", true); break;
							case DvrTypes::WS_ERROR:setCurrentStatus("WIFI错误", true); break;
							default:break;
							}
						}
						else if (statusCode == m_hashCode.ethernetStatus)
						{
							if (m_dvrClient->connectServer("10.0.0.10", 2000, 30))
							{
								setCurrentStatus("以太网已连接", true);
								status = static_cast<T>(DvrTypes::ES_CONNECT);
							}
							else
							{
								setCurrentStatus("以太网未连接", true);
								status = static_cast<T>(DvrTypes::ES_ERROR);
							}
							m_dvrClient->closeConnect();
						}
						else if (statusCode == m_hashCode.sdCardStatus)
						{
							status = static_cast<T>(msg[i].ucData[1] & 0x07);
							switch (status)
							{
							case DvrTypes::SCS_NORMAL:setCurrentStatus("SD卡正常", true); break;
							case DvrTypes::SCS_NO_SD:setCurrentStatus("请插入SD卡", true); break;
							case DvrTypes::SCS_ERROR:setCurrentStatus("SD卡错误", true); break;
							default:break;
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

	template<class T> inline bool Dvr::autoProcessStatus()
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
					setLastError("未收到CAN报文,请检查供电");
					break;
				}

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
					if (status == static_cast<T>(DvrTypes::WS_NORMAL))
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

				if (success || GetTickCount() - startTime >= 20000)
				{
					setLastError("未获取到任何状态,请确认产品CAN矩阵是否正确");
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

/*Network transmission*/
namespace Nt {
	/************************************************************************/
	/* SFR服务端,用于与SFR APP进行通讯,此处用作服务端                       */
	/************************************************************************/
	class SfrServer {
	public:
		SOCKET m_socket;

		SOCKET m_client;

		sockaddr_in m_sockAddr;

		QString m_lastError = "No error";

		bool m_quit = false;
	protected:
		void setLastError(const QString& err);
	public:
		SfrServer();

		~SfrServer();

		bool startListen(const ushort& port = 2000);

		bool getSfr(const QString& filePath, float& sfr);

		int send(SOCKET socket, char* buffer, int len);

		int recv(SOCKET socket, char* buffer, int len);

		void closeServer();

		const QString& getLastError();
	};

	/************************************************************************/
	/* DVR客户端,用于与DVR服务端通讯                                        */
	/************************************************************************/
	class DvrClient {
	private:
		QString m_lastError = "No error";

		SOCKET m_socket;

		SOCKADDR_IN m_sockAddr;

		char m_ipAddr[32] = {};

		ushort m_port;

		bool m_init = false;

		bool m_close = false;
	protected:
		void setLastError(const QString& err);
	public:
		DvrClient();

		~DvrClient();

		bool connectServer(const char* ip, const ushort& port,const int& count = 10);

		int send(char* buffer, int len);

		int recv(char* buffer, const uchar& cmd, const uchar& sub);

		const char* getIpAddr();

		const ushort& getPort();

		void closeConnect();

		const QString& getLastError();
	};
}

