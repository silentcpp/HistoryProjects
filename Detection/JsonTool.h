#pragma once
/************************************************************************/
/* 此文件用于管理检测框架配置文件读写修改                               */
/************************************************************************/
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <memory>
#include <Common/Types.h>

#define Q_TO_C_STR(X) X.toStdString().c_str()

#define NO_THROW_NEW new(std::nothrow)

#define SAFE_DELETE_A(X)\
if (X)\
{\
	delete[] X;\
	X = nullptr;\
}

#define SAFE_DELETE(X)\
if (X)\
{\
	delete X;\
	X = nullptr;\
}

/************************************************************************/
/* 设备配置用于															*/
/************************************************************************/
typedef struct DeviceConfig
{
	/*机种名*/
	QString modelName;

	/*UDS名称*/
	QString udsName;

	/*CAN名称*/
	QString canName;

	/*采集卡名称*/
	QString captureName;

	/*检测名称*/
	QString detectionName;

	/*条码判断*/
	QString codeJudge;

	/*条码长度*/
	QString codeLength;
}deviceConfig_t;

/************************************************************************/
/* 硬件配置                                                             */
/************************************************************************/
typedef struct HardwareConfig
{
	/*电源串口号*/
	int powerPort;

	/*电源波特率*/
	int powerBaud;

	/*电源电压*/
	float powerVoltage;

	/*继电器串口号,COM20为20*/
	int relayPort;

	/*继电器波特率,默认:19200*/
	int relayBaud;

	/*电压表串口号*/
	int voltagePort;

	/*电压表波特率,默认:9600*/
	int voltageBaud;

	/*静态电流表串口号*/
	int staticPort;

	/*静态电流表波特率*/
	int staticBaud;

	/*拓展串口1*/
	int expandCom1;

	/*拓展波特率1*/
	int expandBaud1;

	/*拓展串口2*/
	int expandCom2;

	/*拓展波特率2*/
	int expandBaud2;

	/*拓展串口3*/
	int expandCom3;

	/*拓展波特率3*/
	int expandBaud3;

	/*拓展串口4*/
	int expandCom4;

	/*拓展波特率*/
	int expandBaud4;
}hardwareConfig_t;

/************************************************************************/
/* 继电器IO口配置用于JSON                                               */
/************************************************************************/
typedef struct RelayConfig {
	/*GND IO口*/
	int gnd;

	/*ACC/IG IO口*/
	int acc;

	/*静态电流IO口*/
	int staticCur;

	/*硬按键IO口*/
	int key;

	/*转接板IO口*/
	int pinboard;

	/*LED灯泡*/
	int led;

	/*音响*/
	int sound;
}relayConfig_t;

/************************************************************************/
/* 矩形框结构体定义,用于前后左右摄像头和中间大矩形框                    */
/************************************************************************/
typedef struct RectConfig
{
	/*颜色*/
	QString color;

	/*红*/
	int red;

	/*绿*/
	int green;

	/*蓝*/
	int blue;

	/*误差*/
	int deviation;

	/*起始X*/
	int startX;

	/*起始Y*/
	int startY;

	/*宽*/
	int width;

	/*高*/
	int height;
}rectConfig_t;

#define SMALL_RECT_  4

#define BIG_RECT_ 2

#define IMAGE_CHECK_COUNT  7
/************************************************************************/
/* 图像配置结构体定义                                                    */
/************************************************************************/
typedef struct ImageConfig
{
	/*忽略RGB*/
	int ignoreRgb;

	/*是否显示小图矩形框*/
	int showSmall;

	/*是否显示大图矩形框*/
	int showBig;

	/*是否保存日志*/
	int saveLog;

	/*小矩形框配置*/
	rectConfig_t smallRect[SMALL_RECT_];

	/*大矩形框配置*/
	rectConfig_t bigRect[BIG_RECT_];
}imageConfig_t;

/************************************************************************/
/* 范围配置结构体定义                                                   */
/************************************************************************/
typedef struct RangeConfig
{
	/*DVR网速速率*/
	float minNetworkSpeed;
	float maxNetworkSpeed;

	/*DVR光轴X*/
	float minRayAxisX;
	float maxRayAxisX;

	/*DVR光轴Y*/
	float minRayAxisY;
	float maxRayAxisY;

	/*DVR角度*/
	float minRayAxisA;
	float maxRayAxisA;

	/*解像度*/
	float minSfr;
	float maxSfr;
}rangeConfig_t;

typedef struct ThresholdConfig
{
	/*CAN唤醒电流阈值*/
	float canRouse;

	/*CAN休眠电流阈值*/
	float canSleep;
}thresholdConfig_t;

/*启用配置*/
struct EnableConfig
{
	/*解锁对话框*/
	int unlockDlg;

	/*错误消息对话框,运行失败最终提示*/
	int errorDlg;

	/*CAN日志*/
	int saveCanLog;

	/*忽略失败,运行中不让其失败*/
	int ignoreFailure;

	/*输出CAN日志*/
	int outputRunLog;

	/*运行日志,整个程序运行中的日志*/
	int saveRunLog;
};

/*默认配置*/
struct DefConfig {
	DeviceConfig device;

	HardwareConfig hardware;
	
	RelayConfig relay;
	
	ImageConfig image;
	
	RangeConfig range;
	
	ThresholdConfig threshold;

	EnableConfig enable;
};

#define HWD_BUF 64
struct VoltageConfig
{
	/*检测结果*/
	bool result;

	/*检测值*/
	float read;

	/*上限*/
	float high;

	/*下限*/
	float low;

	/*继电器IO*/
	int relay;

	/*名称*/
	char name[HWD_BUF];
};

struct CurrentConfig
{
	/*检测结果*/
	bool result;

	/*检测值*/
	float read;

	/*上限*/
	float high;

	/*下限*/
	float low;

	/*电源电压*/
	float voltage;

	/*名称*/
	char name[HWD_BUF];
};

struct StaticConfig
{
	/*检测结果*/
	bool result;

	/*检测值*/
	float read;

	/*上限*/
	float high;

	/*下限*/
	float low;
};

struct KeyVolConfig
{
	/*高电平结果*/
	bool hResult;

	/*低电平结果*/
	bool lResult;

	/*高电平检测值*/
	float hRead;

	/*低电平检测值*/
	float lRead;

	/*高电平上限*/
	float hULimit;

	/*高电平下限*/
	float hLLimit;

	/*低电平上限*/
	float lULimit;

	/*低电平下限*/
	float lLLimit;
};

struct ResConfig
{
	/*检测结果*/
	bool result;

	/*检测值*/
	float read;

	/*上限*/
	float high;

	/*下限*/
	float low;

	/*继电器IO*/
	int relay;

	/*名称*/
	char name[HWD_BUF];
};

typedef struct HwdConfig
{
	VoltageConfig* voltage;
	ResConfig* res;
	CurrentConfig* current;
	StaticConfig	staticCurrent;
	KeyVolConfig	keyVol;
}hwdConfig_t;

/************************************************************************/
/* UDS定义                                                              */
/************************************************************************/

struct VersonConfig
{
	/*DID*/
	uchar did[4];

	/*编码*/
	char encode[HWD_BUF];

	/*配置值*/
	char setup[HWD_BUF];

	/*名称*/
	char name[HWD_BUF];

	/*大小*/
	int size;

	/*读取值*/
	char read[HWD_BUF];

	/*结果*/
	bool result;
};

struct DtcConfig
{
	/*是否忽略*/
	bool ignore;

	/*是否存在*/
	bool exist;

	/*DTC*/
	uchar dtc[4];

	/*名称*/
	char name[HWD_BUF];
};

typedef struct UdsConfig
{
	VersonConfig* ver;
	DtcConfig* dtc;
}udsConfig_t;


/************************************************************************/
/* CanSender定义                                                        */
/************************************************************************/
#define MAX_MSG_COUNT 256

enum SendType {
	ST_Period,

	ST_Event,

	ST_PE,
};

struct CanMsg {
	bool bValid;

	SendType emST;

	int iCycle;

	MsgNode msg;

	int iTime;

	int iSendCount;
};


/************************************************************************/
/* JsonTool定义                                                         */
/************************************************************************/
class JsonTool : public QObject
{
	Q_OBJECT
private:
	/*构造*/
	JsonTool(QObject* parent = nullptr);

	/*析构*/
	~JsonTool();

	/*保存错误信息*/
	QString m_lastError = "No Error";

	/*静态指针*/
	static JsonTool* m_self;

	/*设备配置对象*/
	QJsonObject m_deviceConfigObj;

	/*硬件配置对象*/
	QJsonObject m_hardwareConfigObj;

	/*继电器IO配置*/
	QJsonObject m_relayConfigObj;

	/*范围配置*/
	QJsonObject m_rangeConfigObj;

	/*用户配置对象*/
	QJsonObject m_userConfigObj;

	/*图像父配置对象*/
	QJsonObject m_imageConfigObj;

	/*阈值配置对象*/
	QJsonObject m_thresholdConfigObj;

	/*启用配置对象*/
	QJsonObject m_enableConfigObj;

	/*默认配置*/
	DefConfig m_defConfig;

	/*硬件检测结构体*/
	HwdConfig m_hwdConfig = { 0 };

	/*电压配置*/
	QJsonObject m_voltageConfigObj;

	/*按键配置*/
	QJsonObject m_keyVolConfigObj;

	/*电流配置*/
	QJsonObject m_currentConfigObj;

	/*静态电流配置*/
	QJsonObject m_staticConfigObj;

	/*电阻配置*/
	QJsonObject m_resConfigObj;

	/*UDS结构体*/
	UdsConfig m_udsConfig = { 0 };

	/*版本配置*/
	QJsonObject m_verConfigObj;

	/*DTC配置*/
	QJsonObject m_dtcConfigObj;

	/*CanSender配置*/
	QJsonObject m_canMsgObj;

	CanMsg m_canMsg[MAX_MSG_COUNT] = { 0 };
protected:
	/*电压*/
	/*设备配置键列表*/
	QStringList m_deviceConfigKeyList = {
		"机种名称",
		"UDS名称",//0
		"CAN名称",//1
		"采集卡名称",
		"检测名称",
		"条码判断",
		"条码长度"
	};

	/*设备配置值列表*/
	QStringList m_deviceConfigValueList = {
		"未知",
		"GuangQiA56",//0
		"ZLG",//1
		"MV800",
		"功能",
		"ABC",
		"6"
	};

	/*硬件配置键列表*/
	QStringList m_hardwareConfigKeyList{
		"电源串口",//2
		"电源波特率",//3
		"电源电压",//4
		"继电器串口",//6
		"继电器波特率",//7
		"电压表串口",//8
		"电压表波特率",//9
		"静流表串口",//10
		"静流表波特率",//11
		"拓展串口1",//12
		"拓展波特率1",//13
		"拓展串口2",//14
		"拓展波特率2",//15
		"拓展串口3",//16
		"拓展波特率3",//17
		"拓展串口4",
		"拓展波特率4"
	};

	/*硬件配置值列表*/
	QStringList m_hardwareConfigValueList{
		"4",//2
		"19200",//3
		"12",//4
		"5",//6
		"19200",//7
		"2",//8
		"9600",//9	
		"3",//10
		"9600",//11
		"6",//12
		"9600",//13
		"7",//14
		"9600",//15
		"8",//16
		"9600",//17
		"9",
		"9600"
	};

	/*继电器IO配置键列表*/
	QStringList m_relayConfigKeyList = {
		"GND",//10
		"ACC",//11
		"静态电流表",//12
		"硬按键",//13
		"转接板",//14
		"跑马灯",
		"音箱"
	};

	/*继电器IO配置值列表*/
	QStringList m_relayConfigValueList = {
		"0",//10
		"2",//11
		"1",//12
		"3",//13
		"4",//14
		"6",
		"7"
	};

	/*范围配置键列表*/
	QStringList m_rangeConfigKeyList = {
		"网速",//1
		"光轴X坐标",//2
		"光轴Y坐标",//3
		"光轴角度",//4
		"解像度"//5
	};

	/*范围配置值列表*/
	QStringList m_rangeConfigValueList = {
		"2.00~5.00",//1
		"800.0~1100.0",//2
		"400.0~600.0",//3
		"5.0~20.0",//4
		"0.0~1000.0"//5
	};

	/*用户配置键列表*/
	/*ROOT用户权限0,用于此程序开发者*/
	/*INVO用户权限1,用于现场调试者*/
	/*TEST用户权限2,用于作业员*/

	QStringList m_userConfigKeyList = {
		"用户名",
		"密码"
	};

	/*用户配置值列表*/
	QStringList m_userConfigValueList = {
		"INVO",
		"1."
	};

	/*父图像键列表*/
	QStringList m_parentImageKeyList = {
		"前小图矩形框",
		"后小图矩形框",
		"左小图矩形框",
		"右小图矩形框",
		"前大图矩形框",
		"后大图矩形框",
		"检测启用状态"
	};

	/*子图像键列表*/
	QStringList m_childImageKeyList[IMAGE_CHECK_COUNT] = {
		QStringList{"颜色",("R"),("G"),("B"),("误差"),("X坐标"),("Y坐标"),("宽"),("高")},
		QStringList{"颜色",("R"),("G"),("B"),("误差"),("X坐标"),("Y坐标"),("宽"),("高")},
		QStringList{"颜色",("R"),("G"),("B"),("误差"),("X坐标"),("Y坐标"),("宽"),("高")},
		QStringList{"颜色",("R"),("G"),("B"),("误差"),("X坐标"),("Y坐标"),("宽"),("高")},
		QStringList{"颜色",("R"),("G"),("B"),("误差"),("X坐标"),("Y坐标"),("宽"),("高")},
		QStringList{"颜色",("R"),("G"),("B"),("误差"),("X坐标"),("Y坐标"),("宽"),("高")},
		QStringList{"忽略RGB","显示小图","显示大图","保存日志"}
	};

	/*子图像值列表*/
	QStringList m_childImageValueList[IMAGE_CHECK_COUNT] = {
		QStringList{"!=黑色",("201"),("212"),("85"),("100"),("55"),("20"),("50"),("80")},
		QStringList{"!=黑色",("255"),("255"),("255"),("100"),("75"),("380"),("40"),("60")},
		QStringList{"!=黑色",("176"),("58"),("177"),("100"),("5"),("100"),("40"),("180")},
		QStringList{"!=黑色",("164"),("78"),("7"),("100"),("120"),("130"),("40"),("180")},
		QStringList{"!=黑色",("153"),("212"),("81"),("100"),("320"),("80"),("110"),("250")},
		QStringList{"!=黑色",("113"),("50"),("34"),("100"),("300"),("50"),("110"),("250")},
		QStringList{"1","0","0","0"}
	};

	int m_childImageSubscript = 0;

	/*阈值键列表*/
	QStringList m_thresholdKeyList =
	{
		"CAN唤醒电流",
		"CAN休眠电流"
	};

	/*阈值值列表*/
	QStringList m_thresholdValueList = {
		"0.3",
		"0.005"
	};

	/*启用配置键列表*/
	QStringList m_enableConfigKeyList = {
		"解锁对话框",//1
		"错误对话框",//2
		"保存CAN日志",//3
		"忽略失败",//4
		"输出运行日志",
		"保存运行日志"//5
	};

	/*启用配置值列表*/
	QStringList m_enableConfigValueList = {
		"0",//1
		"1",//2
		"0",//3
		"0",//4
		"0",//5
		"0"
	};
protected:
	/*设置错误*/
	void setLastError(const QString& err);

	/*解析范围*/
	bool parseRangeValue(const QString& value, float& min, float& max);

	/*解析设备配置数据*/
	bool parseDeviceConfigData();

	/*解析硬件配置数据*/
	bool parseHardwareConfigData();

	/*解析继电器IO口配置*/
	bool parseRelayPortConfigData();

	/*解析用户配置*/
	bool parseUserConfigData();

	/*解析图像检测配置数据*/
	bool parseImageConfigData();

	/*解析范围配置数据*/
	bool parseRangeConfigData();

	/*解析阈值配置数据*/
	bool parseThresholdConfigData();

	/*解析启用配置数据*/
	bool parseEnableConfigData();

	/************************************************************************/
	/* 硬件检测配置                                                         */
	/************************************************************************/
	/*解析电压配置*/
	bool parseVoltageConfigData();

	/*解析LED配置*/
	bool parseKeyVolConfigData();

	/*解析电流配置*/
	bool parseCurrentConfigData();

	/*解析静态电流配置*/
	bool parseStaticConfigData();

	/*解析电阻配置*/
	bool parseResConfigData();

	/************************************************************************/
	/* UDS检测配置                                                          */
	/************************************************************************/
	/*解析版本配置*/
	bool parseVerConfigData();

	/*解析DTC配置*/
	bool parseDtcConfigData();

	/*DTC种类转换*/
	const QString dtcCategoryConvert(const QString& dtc);

	/************************************************************************/
	/* CanSender配置                                                        */
	/************************************************************************/

	bool parseCanMsgData();
public:
	/************************************************************************/
	/* 基本操作                                                             */
	/************************************************************************/
	/*拷贝构造删除*/
	JsonTool(const JsonTool&) = delete;

	/*赋值构造删除*/
	JsonTool& operator=(const JsonTool&) = delete;

	/*获取单例*/
	static JsonTool* getInstance();

	/*删除单例*/
	static void deleteInstance();

	/*获取错误信息*/
	const QString& getLastError();

	/*初始化实例*/
	bool initInstance(bool update = false, const QString& folderName = "Config", const QStringList& fileName = { "def.json","hwd.json","uds.json","can.json" });

	/*获取所有主键*/
	const QStringList getAllMainKey();

	/************************************************************************/
	/*读写配置文件操作                                                      */
	/************************************************************************/

	/************************************************************************/
	/* DEF                                                                  */
	/************************************************************************/
	/*读取json配置文件*/
	bool readDefJsonFile(const QString& name = QString("def.json"));

	/*写入默认json配置文件*/
	bool writeDefJsonFile(const QString& name = QString("def.json"));

	/*更新默认json配置文件*/
	bool updateDefJsonFile(const QString& name = QString("def.json"));

	/************************************************************************/
	/* HWD                                                                  */
	/************************************************************************/
	/*读取硬件json配置文件*/
	bool readHwdJsonFile(const QString& name = QString("hwd.json"));

	/*写入硬件json配置文件*/
	bool writeHwdJsonFile(const QString& name = QString("hwd.json"));

	/*更新硬件json配置文件*/
	bool updateHwdJsonFile(const QString& name = QString("hwd.json"));

	/************************************************************************/
	/* UDS                                                                  */
	/************************************************************************/
	/*读取uds json 配置文件*/
	bool readUdsJsonFile(const QString& name = QString("uds.json"));

	/*写入uds json 配置文件*/
	bool writeUdsJsonFile(const QString& name = QString("uds.json"));

	/*更新uds json 配置文件*/
	bool updateUdsJsonFile(const QString& name = QString("uds.json"));

	/************************************************************************/
	/* CAN                                                                  */
	/************************************************************************/
	/*读取can json 配置文件*/
	bool readCanJsonFile(const QString& name = QString("can.json"));

	/*写入can json 配置文件*/
	bool writeCanJsonFile(const QString& name = QString("can.json"));

	/*更新can json 配置文件*/
	bool updateCanJsonFile(const QString& name = QString("can.json"));

	/************************************************************************/
	/* 设备配置操作                                                         */
	/************************************************************************/

	/*获取设备对象元素数量*/
	const int getDeviceConfigCount();

	/*通过键获取设备配置值*/
	const QString getDeviceConfigValue(const QString& key);

	/*获取设备对象键*/
	const QStringList getDeviceConfigKeyList();

	/*获取已解析的设备配置*/
	const deviceConfig_t& getParsedDeviceConfig();

	/*获取Json对象*/
	const QJsonObject& getDeviceConfigObj();

	/*设置设备配置值*/
	bool setDeviceConfigValue(const QString& key, const QString& value);

	/*获取设备说明*/
	const QStringList getDeviceConfigExplain();
	/************************************************************************/
	/* 硬件配置操作                                                         */
	/************************************************************************/

	/*通过键获取硬件配置值*/
	const QString getHardwareConfigValue(const QString& key);

	/*获取硬件对象元素数量*/
	const int getHardwareConfigCount();

	/*获取硬件对象键*/
	const QStringList getHardwareConfigKeyList();

	/*获取已解析的硬件配置*/
	const hardwareConfig_t& getParseHardwareConfig();

	/*设置硬件配置值*/
	bool setHardwareConfigValue(const QString& key, const QString& value);

	/*获取硬件说明*/
	const QStringList getHardwareConfigExplain();
	/************************************************************************/
	/* 继电器配置操作                                                       */
	/************************************************************************/
	/*通过键获取继电器IO配置值*/
	const QString getRelayConfigValue(const QString& key);

	/*获取继电器对象元素数量*/
	const int getRelayConfigCount();

	/*获取已解析的继电器IO配置*/
	const relayConfig_t& getParsedRelayConfig();

	/*获取继电器对象键*/
	const QStringList getRelayConfigKeyList();

	/*设置继电器配置值*/
	bool setRelayConfigValue(const QString& key, const QString& value);

	/*获取继电器说明*/
	const QStringList getRelayConfigExplain();
	/************************************************************************/
	/* 用户配置操作                                                         */
	/************************************************************************/
	/*通过键获取用户配置值*/
	const QString getUserConfigValue(const QString& key);

	/*获取用户配置数量*/
	const int getUserConfigCount();

	void setUserConfigValue(const QString& key, const QString& value);
	/************************************************************************/
	/* 范围配置操作                                                         */
	/************************************************************************/
	/*通过键获取范围配置值*/
	const QString getRangeConfigValue(const QString& key);

	/*获取范围对象元素数量*/
	const int getRangeConfigCount();

	/*获取范围键*/
	const QStringList getRangeConfigKeyList();

	/*获取已解析的范围配置*/
	const rangeConfig_t& getParsedRangeConfig();

	/*设置范围配置值*/
	bool setRangeConfigValue(const QString& key, const QString& value);

	/*获取范围配置说明*/
	const QStringList getRangeConfigExplain();
	/************************************************************************/
	/* 阈值配置操作                                                         */
	/************************************************************************/
	/*通过键获取阈值配置值*/
	const QString getThresholdConfigValue(const QString& key);

	/*获取阈值对象元素数量*/
	const int getThresholdConfigCount();

	/*阈值键*/
	const QStringList getThresholdConfigKeyList();

	/*获取已解析的阈值配置*/
	const thresholdConfig_t& getParsedThresholdConfig();

	/*设置阈值配置值*/
	bool setThresholdConfigValue(const QString& key, const QString& value);

	/*获取阈值配置说明*/
	const QStringList getThresholdConfigExplain();
	/************************************************************************/
	/* 图像配置操作                                                         */
	/************************************************************************/
	/*获取已解析的图像配置*/
	const imageConfig_t& getParsedImageConfig();

	/*获取父图像配置数量*/
	const int getImageConfigCount();

	/*获取父图像键列表*/
	const QStringList getParentImageKeyList();

	void setChildImageKeyListSubscript(const int& subscript);

	/*获取子图像键列表*/
	const QStringList getChildImageKeyList(const int& id);

	const QStringList getChildImageKeyList();

	/*获取子图像配置值*/
	const QString getImageConfigValue(const QString& parentKey, const QString& childKey);

	/*不允许设置图像配置键*/
	inline void setImageConfigKey(const QString& oldParentKey, const QString& newParentKey) {};

	/*设置图像配置值*/
	bool setImageConfigValue(const QString& parentKey, const QString& childKey, const QString& value);

	/*获取图像配置说明*/
	const QStringList getImageConfigExplain(const int& i);

	const QStringList getImageConfigExplain();
	/************************************************************************/
	/* 启用配置操作                                                         */
	/************************************************************************/
	/*获取启用配置数量*/
	const int getEnableConfigCount();

	/*获取启用配置键列表*/
	const QStringList getEnableConfigKeyList();

	/*获取启用配置值列表*/
	const QStringList getEnableConfigValueList();

	/*获取启用配置值*/
	const QString getEnableConfigValue(const QString& key);

	/*设置启用配置值*/
	bool setEnableConfigValue(const QString& key, const QString& value);

	/*获取启用配置说明*/
	const QStringList getEnableConfigExplain();

	/************************************************************************/
	/* 获取以上总配置                                                       */
	/************************************************************************/
	DefConfig* getParsedDefConfig();

	/************************************************************************/
	/* 电压配置操作                                                         */
	/************************************************************************/
	/*获取电压配置数量*/
	const int getVoltageConfigCount();

	/*获取子电压配置键*/
	const QStringList getChildVoltageConfigKeyList();

	/*获取子电压配置默认值*/
	const QStringList getChildVoltageConfigValueList();

	/*获取父电压配置键*/
	const QStringList getParentVoltageConfigKeyList();

	/*获取电压配置值*/
	const QString getVoltageConfigValue(const QString& parentKey, const QString& childKey);
	
	/*设置电压配置键*/
	void setVoltageConfigKey(const QString& oldParentKey, const QString& newParentKey);

	/*设置电压配置值*/
	bool setVoltageConfigValue(const QString& parentKey, const QString& childKey, const QString& value);

	/*获取电压JSON对象*/
	QJsonObject& getVoltageConfigObj();

	/*获取电压配置说明*/
	const QStringList getVoltageConfigExplain();

	/************************************************************************/
	/* 按键电压配置操作                                                     */
	/************************************************************************/
	/*获取按键电压数量*/
	const int getKeyVolConfigCount();

	/*获取按键电压配置键*/
	const QStringList getKeyVolConfigKeyList();

	/*获取按键电压配置值*/
	const QStringList getKeyVolConfigValueList();

	/*获取按键电压配置值*/
	const QString getKeyVolConfigValue(const QString& key);

	/*设置按键电压值*/
	bool setKeyVolConfigValue(const QString& key, const QString& value);

	/*获取按键电压配置说明*/
	const QStringList getKeyVolConfigExplain();

	/*按键电压*/
	/************************************************************************/
	/* 电流配置操作                                                         */
	/************************************************************************/
	/*获取父电流配置键列表*/
	const QStringList getParentCurrentConfigKeyList();

	/*获取子电流配置键列表*/
	const QStringList getChildCurrentConfigKeyList();
	
	/*获取电流配置值列表*/
	const QStringList getChildCurrentConfigValueList();

	/*获取电流配置值列表*/
	const QStringList getChildCurrentConfigValueList(const int& i);

	/*获取电流配置数量*/
	const int getCurrentConfigCount();

	/*获取电流配置值*/
	const QString getCurrentConfigValue(const QString& parentKey, const QString& childKey);

	/*设置电流配置键*/
	void setCurrentConfigKey(const QString& oldParentKey, const QString& newParentKey);

	/*设置电流配置值*/
	bool setCurrentConfigValue(const QString& parentKey, const QString& childKey, const QString& value);

	/*获取电流JSON配置对象*/
	QJsonObject& getCurrentConfigObj();

	/*获取电流配置说明*/
	const QStringList getCurrentConfigExplain();
	/************************************************************************/
	/* 静态电流配置操作                                                     */
	/************************************************************************/

	/*获取静态电流数量*/
	const int getStaticConfigCount();

	/*静态电流配置键列表*/
	const QStringList getStaticConfigKeyList();

	/*静态电流配置值列表*/
	const QStringList getStaticConfigValueList();

	/*获取静态电流表值*/
	const QString getStaticConfigValue(const QString& key);

	/*设置静态电流配置值*/
	bool setStaticConfigValue(const QString& key, const QString& value);

	/*获取静态电流说明*/
	const QStringList getStaticConfigExplain();

	/************************************************************************/
	/* 电阻配置操作                                                         */
	/************************************************************************/
	/*获取父电阻配置键*/
	const QStringList getParentResConfigKeyList();

	/*获取子电阻配置键*/
	const QStringList getChildResConfigKeyList();

	/*获取电阻配置值*/
	const QStringList getChildResConfigValueList();

	/*获取电阻配置数量*/
	const int getResConfigCount();

	/*获取电阻配置值*/
	const QString getResConfigValue(const QString& parentKey, const QString& childKey);

	/*设置电阻配置键*/
	void setResConfigKey(const QString& oldParentKey, const QString& newParentKey);

	/*设置电阻配置值*/
	bool setResConfigValue(const QString& parentKey, const QString& childKey, const QString& value);

	/*获取电阻JSON配置对象*/
	QJsonObject& getResConfigObj();

	/*获取电阻配置说明*/
	const QStringList getResConfigExplain();

	/************************************************************************/
	/* 获取以上总配置                                                       */
	/************************************************************************/
	/*获取已解析的硬件检测信息配置*/
	HwdConfig* getParsedHwdConfig();

	/************************************************************************/
	/* 版本配置操作                                                          */
	/************************************************************************/
	/*获取版本配置数量*/
	const int getVerConfigCount();

	/*获取父版本配置键*/
	const QStringList getParentVerConfigKeyList();

	/*获取子版本配置键*/
	const QStringList getChildVerConfigKeyList();

	/*获取子版本配置值*/
	const QStringList getChildVerConfigValueList();

	/*获取版本配置值*/
	const QString getVerConfigValue(const QString& parentKey, const QString& childKey);

	/*设置版本配置键*/
	void setVerConfigKey(const QString& oldParentKey, const QString& newParentKey);

	/*设置版本配置值*/
	bool setVerConfigValue(const QString& parentKey, const QString& childKey, const QString& value);

	/*获取版本JSON配置对象*/
	QJsonObject& getVerConfigObj();

	/*获取版本配置说明*/
	const QStringList getVerConfigExplain();

	/************************************************************************/
	/* 诊断故障码配置操作                                                   */
	/************************************************************************/
	/*获取故障码配置数量*/
	const int getDtcConfigCount();

	/*获取父故障码键*/
	const QStringList getParentDtcConfigKeyList();

	/*获取子故障码键*/
	const QStringList getChildDtcConfigKeyList();

	/*获取子故障码值*/
	const QStringList getChildDtcConfigValueList();

	/*获取故障码值*/
	const QString getDtcConfigValue(const QString& parentKey, const QString& childKey);

	/*设置诊断故障码配置键*/
	void setDtcConfigKey(const QString& oldParentKey, const QString& newParentKey);

	/*设置诊断故障码配置值*/
	bool setDtcConfigValue(const QString& parentKey, const QString& childKey, const QString& value);
	
	/*获取诊断故障码JSON配置对象*/
	QJsonObject& getDtcConfigObj();

	/*获取诊断故障码说明*/
	const QStringList getDtcConfigExplain();


	/************************************************************************/
	/* 获取以上总配置                                                       */
	/************************************************************************/
	/*获取已解析的UDS信息配置*/
	UdsConfig* getParsedUdsConfig();

	/************************************************************************/
	/* CanSender配置,此配置为预留配置,后期使用在做处理                      */
	/************************************************************************/
	/*获取CAN报文数量*/
	const int getCanMsgCount();

	/*获取CAN报文键列表*/
	const QStringList getCanMsgKeyList();

	/*获取CAN报文值*/
	const QString getCanMsgValue(const QString& parentKey, const QString& childKey);

	/*设置CAN报文键*/
	void setCanMsgKey(const QString& oldParentKey, const QString& newParentKey);

	/*设置CAN报文值*/
	void setCanMsgValue(const QString& parentKey, const QString& childKey, const QString& value);

	/*获取已解析的CAN报文*/
	const CanMsg* getParsedCanMsg();

	/*获取CAN报文JSON配置对象*/
	QJsonObject& getCanMsgObj();
};

