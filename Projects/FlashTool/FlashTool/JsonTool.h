#pragma once
#pragma execution_character_set("utf-8")

/************************************************************************/
/* JSON配置文件解析类                                                   */
/************************************************************************/
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileInfo>
#include <QDir>

#define SUPER_PASSWORD "i am superman"

/*单通道电源*/
#define IT6832 "IT6832"

/*三通道电源*/
#define IT6302 "IT6302"

#define NO_THROW_NEW new(std::nothrow)

#define SAFE_DELETE(X)\
if (X)\
{\
delete X;\
X = nullptr;\
}

#define SAFE_DELETE_A(X) \
if (X)\
{\
delete[] X;\
X = nullptr;\
}

/*以下结构体确保数据类型一直,方便解析*/

/*设备配置*/
struct DeviceConfig {
	/*电源类型*/
	QString powerType;

	/*是否启用电源*/
	QString openPower;

	/*是否启用电流限制*/
	QString currentLimit;

	/*是否启用继电器*/
	QString openRelay;

	/*是否条码去重*/
	QString codeRepeat;

	/*跳过0xff*/
	QString jump0xff;
};

/*硬件配置*/
struct HardwareConfig {
	/*电源串口号,默认:19200*/
	int powerPort;

	/*电源波特率*/
	int powerBaud;

	/*电源通道数*/
	int powerChannel;

	/*电源延时*/
	int powerDelay;

	/*继电器串口号,COM20为20*/
	int relayPort;

	/*继电器波特率,默认:19200*/
	int relayBaud;

	/*继电器上下电延时*/
	int relayDelay;
};

/*阈值配置*/
struct ThresholdConfig {
	/*电源电压*/
	float powerVoltage;

	/*电源电流*/
	float powerCurrent;
};

/************************************************************************/
/* 继电器IO口配置用于JSON                                               */
/************************************************************************/
struct RelayConfig {
	/*继电器IO口*/
	int port;

	/*是否启用IO*/
	int enable;
};

/************************************************************************/
/* 文件配置                                                          */
/************************************************************************/
struct FileConfig {
	/*文件路径*/
	QString path;

	/*节点名称*/
	QString nodeName;

	/*条码长度*/
	int codeLength;

	/*条码规则*/
	QString codeRule;

	/*保存BIN数据*/
	QByteArray data;

	/*地址长度*/
	int addressLength;

	/*数据slave*/
	int dataSlave;

	/*校验slave*/
	int checkSlave;

	/*烧录模式*/
	int burnMode;

	/*疯狂模式*/
	int speedMode;

	/*底层库读取延时*/
	int libReadDelay;

	/*底层库写入延时*/
	int libWriteDelay;

	/*应用层读取延时*/
	int appReadDelay;

	/*应用层写入延时*/
	int appWriteDelay;

	/*重启延时*/
	int rebootDelay;

	/*设备速度*/
	int deviceSpeed;

	/*设备超时*/
	int deviceTimeout;

	/*配置是否有效*/
	bool valid;

	/*校验断电*/
	int checkOutage;
};

/************************************************************************/
/* JsonTool类                                                           */
/************************************************************************/
class JsonTool : public QObject
{
	Q_OBJECT
public:
	/*拷贝构造删除*/
	JsonTool(const JsonTool&) = delete;

	/*赋值构造删除*/
	JsonTool& operator=(const JsonTool&) = delete;

	/*获取单例*/
	static JsonTool* getInstance();

	/*删除单例*/
	static void deleteInstance();

	/*初始化Json工具*/
	bool initInstance(bool update = false, const QString& fileName = "FlashConfig.json");

	/*获取错误*/
	const QString& getLastError();

	/*获取所有主键*/
	const QStringList& getAllMainKey();

	/*获取烧录模式*/
	const QString& getBurnModeTips();

	const QString& getFilePathTips();
	/************************************************************************/
	/* DeviceConfig                                                         */
	/************************************************************************/

	/*获取设备配置对象*/
	const QJsonObject& getDeviceConfigObj();

	/*通过键获取设备配置值*/
	const QString getDeviceConfigValue(const QString& key);

	/*通过键设置设备配置值*/
	bool setDeviceConfigValue(const QString& key, const QString& value);

	/*获取设备配置键列表*/
	const QStringList& getDeviceConfigKeyList();

	/*获取设备配置值列表*/
	const QStringList& getDeviceConfigValueList();

	/*获取设备对象元素数量*/
	const int getDeviceConfigCount();

	/*获取已解析的设备配置*/
	DeviceConfig* getParsedDeviceConfig();

	/*获取设备配置说明*/
	const QStringList& getDeviceConfigExplain();

	/*打印已解析的设备配置*/
	void printDeviceConfigData();

	/*打印已解析的设备配置*/
	void printDeviceConfigData(const DeviceConfig& deviceConfig);

	/************************************************************************/
	/* HardwareConfig                                                       */
	/************************************************************************/
	/*获取硬件配置数量*/
	const int getHardwareConfigCount();
	
	/*获取硬件配置值*/
	const QString getHardwareConfigValue(const QString& key);

	/*获取硬件配置键*/
	const QStringList& getHardwareConfigKeyList();

	/*获取硬件配置值*/
	const QStringList& getHardwareConfigValueList();

	/*获取硬件配置说明*/
	const QStringList& getHardwareConfigExplain();

	/*设置硬件配置值*/
	bool setHardwareConfigValue(const QString& key, const QString& value);

	/*获取已解析的硬件配置*/
	HardwareConfig* getParsedHardwareConfig();

	/************************************************************************/
	/* ThresholdConfig                                                      */
	/************************************************************************/
	/*获取阈值配置数量*/
	const int getThresholdConfigCount();

	/*获取阈值配值*/
	const QString getThresholdConfigValue(const QString& key);

	/*获取阈值配置键列表*/
	const QStringList& getThresholdConfigKeyList();

	/*获取阈值配置值列表*/
	const QStringList& getThresholdConfigValueList();

	/*设置阈值配值*/
	bool setThresholdConfigValue(const QString& key, const QString& value);

	/*获取阈值配置说明*/
	const QStringList& getThresholdConfigExplain();

	/*获取已解析的阈值配置*/
	ThresholdConfig* getParsedThresholdConfig();

	/************************************************************************/
	/* RelayConfig                                                    */
	/************************************************************************/

	/*获取继电器IO口对象*/
	const QJsonObject& getRelayConfigObj();

	/*通过键获取继电器配置值*/
	const QString getRelayConfigValue(const QString& key);

	/*通过键设置继电器配置值*/
	bool setRelayConfigValue(const QString& key, const QString& value);

	/*获取继电器键列表*/
	const QStringList& getRelayConfigKeyList();

	/*获取继电器值列表*/
	const QStringList& getRelayConfigValueList();

	/*获取继电器配置数量*/
	const int getRelayConfigCount();

	/*获取继电器配置说明*/
	const QStringList& getRelayConfigExplain();

	/*获取已解析的IO口配置*/
	RelayConfig* getParsedRelayConfig();


	/************************************************************************/
	/* UserConfig                                                           */
	/************************************************************************/

	/*获取用户配置键列表*/
	const QStringList& getUserConfigKeyList();

	/*获取用户配置值列表*/
	const QStringList& getUserConfigValueList();

	/*通过键获取用户配置值*/
	const QString getUserConfigValue(const QString& key);

	/*获取用户配置数量*/
	const int getUserConfigCount();

	/*设置用户值*/
	bool setUserConfigValue(const QString& key, const QString& value);

	/*获取用户配置说明*/
	const QStringList& getUserConfigExplain();

	/************************************************************************/
	/* FileConfig                                                           */
	/************************************************************************/
	
	/*获取文件配置数量*/
	const int getFileConfigCount();

	/*获取文件配置对象*/
	QJsonObject& getFileConfigObj();

	/*获取父键列表*/
	const QStringList getParentFileConfigKeyList();

	/*获取文件配置键列表*/
	const QStringList& getFileConfigKeyList();

	/*获取文件配置值列表*/
	const QStringList& getFileConfigValueList();

	/*获取文件配置值*/
	const QString getFileConfigValue(const QString& parentKey, const QString& childKey);

	/*设置文件配置键*/
	bool setFileConfigKey(const QString& oldKey, const QString& newKey);

	/*设置文件配置值*/
	bool setFileConfigValue(const QString& parentKey, const QString& childKey, const QString& value);

	/*获取已解析的文件配置*/
	bool getParsedFileConfig(const QString& nodeName);

	/*获取文件配置说明*/
	const QStringList& getFileConfigExplain();

	FileConfig* getParsedFileConfig();

	FileConfig* getParsedAllFileConfig();

	void printFileConfig();
protected:
	/*设置错误*/
	void setLastError(const QString& err);

	/*读取Json配置文件*/
	bool readJsonFile(const QString& name);

	/*写入默认Json配置文件*/
	bool writeJsonFile(const QString& name);

	/*更新Json配置文件*/
	bool updateJsonFile(const QString& name);

	/*解析设备配置数据*/
	bool parseDeviceConfigData();

	/*解析硬件配置数据*/
	bool parseHardwareConfigData();

	/*解析阈值配置数据*/
	bool parseThresholdConfigData();

	/*解析继电器配置数据*/
	bool parseRelayConfigData();

	/*解析文件配置数据*/
	bool parseFileConfigData();

	/*解析用户配置数据*/
	bool parseUserConfigData() { return true; };
private:
	/*构造*/
	inline JsonTool(QObject* parent = nullptr) {};

	/*析构*/
	inline ~JsonTool() {};

	/*静态指针*/
	static JsonTool* m_self;

	/*ROOT对象*/
	QJsonObject m_root;

	/*设备配置对象*/
	QJsonObject m_deviceConfigObj;

	/*硬件配置对象*/
	QJsonObject m_hardwareConfigObj;

	/*阈值配置对象*/
	QJsonObject m_thresholdConfigObj;

	/*继电器配置对象*/
	QJsonObject m_relayConfigObj;

	/*文件配置对象*/
	QJsonObject m_fileConfigObj;

	/*父BIN文件键列表*/
	QStringList m_parentFileKeyList;

	/*用户配置对象*/
	QJsonObject m_userConfigObj;

	/*获取错误*/
	QString m_lastError = "No Error";

	/*设备配置*/
	DeviceConfig m_deviceConfig;

	/*硬件配置*/
	HardwareConfig m_hardwareConfig;

	/*阈值配置*/
	ThresholdConfig m_thresholdConfig;

	/*继电器配置结*/
	RelayConfig m_relayConfig[15];

	/*文件配置,用于烧录使用*/
	FileConfig m_fileConfig;

	/*文件所有配置,只用于显示*/
	FileConfig* m_allFileConfig = nullptr;

	/*设备配置键*/
	QStringList m_deviceConfigKeyList = {
		"电源类型",//0
		"启用电源",//1
		"电流限制",//2
		"启用继电器",//3
		"条码去重",//4
		"跳过0xFF"
	};

	/*设备配置值*/
	QStringList m_deviceConfigValueList = {
		IT6302,//0
		"1",//1
		"0",//2
		"0",//3
		"0",//4
		"0"
	};

	/*硬件配置键*/
	QStringList m_hardwareConfigKeyList = {
		"电源串口",//2
		"电源波特率",//3
		"电源通道数",//4
		"电源延时",//5
		"继电器串口",//6
		"继电器波特率",//7
		"继电器延时"//8
	};

	/*硬件配置值*/
	QStringList m_hardwareConfigValueList = {
		"1",//2
		"9600",//3
		"2",//4
		"300",//5
		"2",//6
		"19200",//7
		"300"//8
	};

	/*阈值配置键*/
	QStringList m_thresholdConfigKeyList = {
		"电源电压",//1
		"电源电流"//2
	};

	/*阈值配置值*/
	QStringList m_thresholdConfigValueList = {
		"12.0",//1
		"0.1"//2
	};

	/*继电器键*/
	QStringList m_relayConfigKeyList = {
		"端口0",//1
		"端口1",//2
		"端口2",//3
		"端口3",//4
		"端口4",//5
		"端口5",//6
		"端口6",//7
		"端口7",//8
		"端口8",//9
		"端口9",//10
		"端口10",//11
		"端口11",//12
		"端口12",//13
		"端口13",//14
		"端口14",//15
	};

	/*继电器值*/
	QStringList m_relayConfigValueList = {
		"0",//1
		"0",//2
		"0",//3
		"0",//4
		"0",//5
		"0",//6
		"0",//7
		"0",//8
		"0",//9
		"0",//10
		"0",//11
		"0",//12
		"0",//13
		"0",//14
		"0"//15
	};

	QStringList m_fileConfigKeyList = {
		"文件路径",//1
		"条码长度",//7
		"条码规则",//2
		"地址长度",//3
		"读写地址",//4
		"校验地址",//5
		"烧录模式",//6
		"极速模式",//13
		"底层读取",//8
		"底层写入",//9
		"应层读取",//10
		"应层写入",//12
		"重启延时",//11
		"设备速率",
		"设备超时",
		"校验断电"
	};

	QStringList m_fileConfigValueList = {
		"Config\\Bin\\A39-HSYNC.bin",//1
		"3",//7
		"HD",//2
		"7",//3
		"0x34",//4
		"0x34",//5
		"1",//6
		"0",//13
		"2",//8
		"2",//9
		"1",//10
		"1",//12
		"2000",//11
		"400",
		"150",
		"1"
	};

	QStringList m_userConfigKeyList = {
		"用户名",
		"密码"
	};

	QStringList m_userConfigValueList = {
		"invo",
		"123456"
	};
};
