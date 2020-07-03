#include "JsonTool.h"

JsonTool* JsonTool::m_self = nullptr;

JsonTool* JsonTool::getInstance()
{
	if (!m_self)
	{
		m_self = NO_THROW_NEW JsonTool;
	}
	return m_self;
}

void JsonTool::deleteInstance()
{
	SAFE_DELETE(m_self);
}

bool JsonTool::initInstance(bool update, const QString& name)
{
	bool result = false;
	do 
	{
		QString&& binPath = "./Config/Bin";

		if (!QDir(binPath).exists())
		{
			QDir dir;
			if (!dir.mkpath(binPath))
			{
				setLastError(QString("创建%1文件夹失败").arg(binPath));
				break;
			}
		}

		QString&& fileName = QString("./Config/%1").arg(name);
		if (!QFileInfo(fileName).exists() || update)
		{
			if (update ? !updateJsonFile(fileName) : !writeJsonFile(fileName))
			{
				break;
			}
		}

		if (!readJsonFile(fileName))
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

const QString& JsonTool::getLastError()
{
	return m_lastError;
}

const QStringList& JsonTool::getAllMainKey()
{
	static QStringList mainKey({ "设备配置","硬件配置","继电器配置","阈值配置","用户配置" ,"文件配置" });
	return mainKey;
}

const QString& JsonTool::getBurnModeTips()
{
	static QString modeKey = "0.ATC_016_SET 0x30\n1.CTC_016_SET 0x30\n2.CTC_019_SET 0x34,0x36\n3.EEP_AXS340 0x90\n4.FLASH_AXS340 0x90\n"
		"5.NET_AXS340\n6.CTC_CHANGAN_IMS 0x34\n7.EEP_GEELY_BX11 0x90\n8.CTC_EP30TAP_DMS 0x34\n9.ATC_BYD_OV7958 0x80";
	return modeKey;
}

const QString& JsonTool::getFilePathTips()
{
	static QString pathKey = "本地路径:\n例:Config\\Bin\\XXX.YYY\n其中\"Config\\Bin\\\"这个是本地文件路径,\n\"XXX\"为文件名,\".YYY\"为后缀名.\n\n"
		"网络路径:\n例:\\\\192.168.2.2\\Bin\\XXX.YYY\n其中\"\\\\192.168.2.2\\Bin\\\"这个是网络文件路径,\n\"XXX\"为文件名,\".YYY\"为后缀名.";
	return pathKey;
}

/************************************************************************/
/* DeviceConfig                                                         */
/************************************************************************/
const QJsonObject& JsonTool::getDeviceConfigObj()
{
	return m_deviceConfigObj;
}

const QString JsonTool::getDeviceConfigValue(const QString& key)
{
	return m_deviceConfigObj[key].toString();
}

bool JsonTool::setDeviceConfigValue(const QString& key,const QString& value)
{
	bool result = false, convert = true;
	do 
	{
		if (key == "电源类型")
		{
			if (value != IT6302 && value != IT6832)
			{
				setLastError(QString("%1,仅支持%2和%3").arg(key, IT6302, IT6832));
				break;
			}
		}
		else
		{
			if (value != "0" && value != "1")
			{
				setLastError(QString("%1,只能为0或者1").arg(key));
				break;
			}
		}

		if (!m_deviceConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}

		m_deviceConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getDeviceConfigKeyList()
{
	return m_deviceConfigKeyList;
}

const QStringList& JsonTool::getDeviceConfigValueList()
{
	return m_deviceConfigValueList;
}

const int JsonTool::getDeviceConfigCount()
{
	return m_deviceConfigKeyList.count();
}

DeviceConfig* JsonTool::getParsedDeviceConfig()
{
	return &m_deviceConfig;
}

const QStringList& JsonTool::getDeviceConfigExplain()
{
	static QStringList explain({ "仅支持IT6832,IT6302","0禁用,1启用","0禁用,1启用","0禁用,1启用","0禁用,1启用",
		"0禁用,1启用,仅支持019摄像头烧录,实验性阶段" });
	return explain;
}

void JsonTool::printDeviceConfigData()
{
	QStringList keys = m_deviceConfigObj.keys();
	for (int i = 0; i < m_deviceConfigObj.count(); i++)
	{
		qDebug() << keys[i] << " " << m_deviceConfigObj[keys[i]].toString() << endl;
	}
}

void JsonTool::printDeviceConfigData(const DeviceConfig& deviceConfig)
{
	//qDebug() << "电源类型:" << deviceConfig.powerType << endl;
	//qDebug() << "电源波特率:" << deviceConfig.powerBaud << endl;
	//qDebug() << "电源通道数:" << deviceConfig.powerChannel << endl;
	//qDebug() << "电源电流:" << deviceConfig.powerCurrent << endl;
	//qDebug() << "电源限流:" << deviceConfig.currentLimit << endl;
	//qDebug() << "电源延时:" << deviceConfig.powerDelay << endl;
	//qDebug() << "电源状态:" << deviceConfig.powerEnable << endl;
	//qDebug() << "电源串口号:" << deviceConfig.powerPort << endl;
	//qDebug() << "电源电压:" << deviceConfig.powerVoltage << endl;
	//qDebug() << "继电器波特率:" << deviceConfig.relayBaud << endl;
	//qDebug() << "继电器延时:" << deviceConfig.relayDelay << endl;
	//qDebug() << "继电器串口号:" << deviceConfig.relayPort << endl;
	//qDebug() << "继电器状态:" << deviceConfig.relayEnable << endl;
	//qDebug() << "条码重复:" << deviceConfig.codeRepeat << endl;
}

/************************************************************************/
/* HardwareConfig                                                       */
/************************************************************************/
const int JsonTool::getHardwareConfigCount()
{
	return m_hardwareConfigKeyList.count();
}

const QString JsonTool::getHardwareConfigValue(const QString& key)
{
	return m_hardwareConfigObj[key].toString();
}

const QStringList& JsonTool::getHardwareConfigKeyList()
{
	return m_hardwareConfigKeyList;
}

const QStringList& JsonTool::getHardwareConfigValueList()
{
	return m_hardwareConfigValueList;
}

const QStringList& JsonTool::getHardwareConfigExplain()
{
	static QStringList explain({ "设备串口号","IT6302,9600;IT6832,19200",
		"IT6302,3通道;IT6832,1通道","电源上下电延时,单位(ms)","设备串口号","默认19200","继电器闭合延时,单位(ms)" });
	return explain;
}

bool JsonTool::setHardwareConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toInt(&convert);
		if (!convert)
		{
			setLastError(QString("%1,只能为整数").arg(key));
			break;
		}

		if (key == "电源通道数")
		{
			if (value.toInt() > 2 || value.toInt() < 1)
			{
				setLastError(QString("%1,范围仅支持1~2").arg(key));
				break;
			}
		}

		if (!m_hardwareConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}
		
		m_hardwareConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

HardwareConfig* JsonTool::getParsedHardwareConfig()
{
	return &m_hardwareConfig;
}

const int JsonTool::getThresholdConfigCount()
{
	return m_thresholdConfigKeyList.count();
}

const QString JsonTool::getThresholdConfigValue(const QString& key)
{
	return m_thresholdConfigObj[key].toString();
}

const QStringList& JsonTool::getThresholdConfigKeyList()
{
	return m_thresholdConfigKeyList;
}

const QStringList& JsonTool::getThresholdConfigValueList()
{
	return m_thresholdConfigValueList;
}

bool JsonTool::setThresholdConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toFloat(&convert);
		if (!convert)
		{
			setLastError(QString("%1,只能为数字").arg(key));
			break;
		}

		if (!m_thresholdConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}

		m_thresholdConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getThresholdConfigExplain()
{
	static QStringList explain({ "单位:伏(V)","单位:安培(A)" });
	return explain;
}

ThresholdConfig* JsonTool::getParsedThresholdConfig()
{
	return &m_thresholdConfig;
}

/************************************************************************/
/* RelayConfig                                                          */
/************************************************************************/
const QJsonObject& JsonTool::getRelayConfigObj()
{
	return m_relayConfigObj;
}

const QString JsonTool::getRelayConfigValue(const QString& key)
{
	return m_relayConfigObj[key].toString();
}

bool JsonTool::setRelayConfigValue(const QString& key, const QString& value)
{
	bool result = false;
	do 
	{
		if (value != "0" && value != "1")
		{
			setLastError(QString("%1,必须为0或者1").arg(key));
			break;
		}

		if (!m_relayConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}
		m_relayConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}


const QStringList& JsonTool::getRelayConfigKeyList()
{
	return m_relayConfigKeyList;
}

const QStringList& JsonTool::getRelayConfigValueList()
{
	return m_relayConfigValueList;
}


const int JsonTool::getRelayConfigCount()
{
	return	m_relayConfigKeyList.count();
}

const QStringList& JsonTool::getRelayConfigExplain()
{
	static QStringList explain { "0禁用,1启用","0禁用,1启用", "0禁用,1启用", "0禁用,1启用", "0禁用,1启用", "0禁用,1启用",
	"0禁用,1启用", "0禁用,1启用", "0禁用,1启用", "0禁用,1启用", "0禁用,1启用", "0禁用,1启用", "0禁用,1启用",
	"0禁用,1启用", "0禁用,1启用" };
	return explain;
}


RelayConfig* JsonTool::getParsedRelayConfig()
{
	return m_relayConfig;
}

/************************************************************************/
/* UserConfig                                                           */
/************************************************************************/
const QStringList& JsonTool::getUserConfigKeyList()
{
	return m_userConfigKeyList;
}

const QStringList& JsonTool::getUserConfigValueList()
{
	return m_userConfigValueList;
}

const QString JsonTool::getUserConfigValue(const QString& key)
{
	return m_userConfigObj[key].toString();
}

const int JsonTool::getUserConfigCount()
{
	return m_userConfigKeyList.count();
}

bool JsonTool::setUserConfigValue(const QString& key, const QString& value)
{
	bool result = false;
	do 
	{
		if (!m_userConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}

		m_userConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getUserConfigExplain()
{
	static QStringList explain({ "认证账号","认证密码" });
	return explain;
}

/************************************************************************/
/* FileConfig                                                           */
/************************************************************************/
const int JsonTool::getFileConfigCount()
{
	return m_fileConfigObj.count();
}

QJsonObject& JsonTool::getFileConfigObj()
{
	return m_fileConfigObj;
}

const QStringList JsonTool::getParentFileConfigKeyList()
{
	return m_fileConfigObj.keys();
}

const QStringList& JsonTool::getFileConfigKeyList()
{
	return m_fileConfigKeyList;
}

const QStringList& JsonTool::getFileConfigValueList()
{
	return m_fileConfigValueList;
}

const QString JsonTool::getFileConfigValue(const QString& parentKey, const QString& childKey)
{
	return m_fileConfigObj.value(parentKey).toObject()[childKey].toString();
}

bool JsonTool::setFileConfigKey(const QString& oldKey, const QString& newKey)
{
	bool result = false;
	do 
	{
		if (newKey.mid(0, 9) == "[请编辑节点名称]")
		{
			result = true;
			break;
		}

		if (newKey.isEmpty())
		{
			setLastError("主键不可以为空");
			break;
		}

		if (!m_fileConfigObj.contains(oldKey))
		{
			setLastError(QString("%1,非法的键").arg(oldKey));
			break;
		}
		QJsonObject object = m_fileConfigObj[oldKey].toObject();
		m_fileConfigObj.remove(oldKey);
		m_fileConfigObj.insert(newKey, object);
		result = true;
	} while (false);
	return result;
}

bool JsonTool::setFileConfigValue(const QString& parentKey, const QString& childKey, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		if (value == "[参数待编辑]")
		{
			result = true;
			break;
		}

		if (value.isEmpty())
		{
			setLastError(QString("%1,不可以为空").arg(childKey));
			break;
		}

		if (!m_fileConfigObj.contains(parentKey))
		{
			setLastError(QString("非法的父键,%1").arg(parentKey));
			break;
		}

		if (childKey != "文件路径" && childKey != "条码规则")
		{
			if (childKey == "读写地址" || childKey == "校验地址")
			{
				if (!(value.contains("0x") || value.contains("0X")))
				{
					setLastError(QString("%1格式错误,例子:格式为0x30").arg(childKey));
					break;
				}

				value.toInt(&convert, 16);
				if (!convert)
				{
					setLastError(QString("%1格式错误,例子:格式为0x30").arg(childKey));
					break;
				}
			}
			else
			{
				int number = value.toInt(&convert);
				if (!convert)
				{
					setLastError(QString("%1格式错误,参数只能为整数").arg(childKey));
					break;
				}

				if (childKey == "极速模式" || childKey == "校验断电")
				{
					if (number < 0 || number > 1)
					{
						setLastError(QString("%1,只能为0或者1").arg(childKey));
						break;
					}
				}
			}
		}
		else
		{
			if (childKey == "文件路径")
			{
				if (!QFileInfo(value).isFile())
				{
					setLastError(QString("%1,无效的文件路径").arg(childKey));
					break;
				}
			}
		}

		QJsonObject object = m_fileConfigObj[parentKey].toObject();
		if (!object.contains(childKey))
		{
			setLastError(QString("非法的子键,%1").arg(childKey));
			break;
		}

		object[childKey] = value;
		m_fileConfigObj.insert(parentKey, object);
		result = true;
	} while (false);
	return result;
}

bool JsonTool::getParsedFileConfig(const QString& nodeName)
{
	bool result = false, success = false;

	do 
	{
		if (nodeName == SUPER_PASSWORD)
		{
			result = true;
			break;
		}

		for (int i = 0; i < getFileConfigCount(); i++)
		{
			if (m_allFileConfig[i].nodeName == nodeName)
			{
				m_fileConfig = m_allFileConfig[i];

				if (!m_fileConfig.valid)
				{
					setLastError(QString("[%1]节点无效,\n请进入调试模式进行编辑").arg(nodeName));
					break;
				}

				/*此处不可以使用memcpy,会进行类浅拷贝,导致崩溃*/
				//memcpy(&m_fileConfig, &m_allFileConfig[i], sizeof(FileConfig));

				QFile file(m_fileConfig.path);
				if (!file.open(QFile::ReadOnly))
				{
					m_fileConfig.valid = false;
					setLastError(QString("[%1]\n打开%2文件失败,%3").arg(nodeName, m_fileConfig.path, file.errorString()));
					break;
				}

				m_fileConfig.data = file.readAll();
				if (m_fileConfig.data.size() != file.size())
				{
					m_fileConfig.valid = false;
					setLastError(QString("[%1]\n读取%2校验错误").arg(nodeName, m_fileConfig.path));
					file.close();
					break;
				}
				success = true;
				file.close();
				break;
			}

			if (i == getFileConfigCount() - 1)
			{
				setLastError(QString("未找到[%1]节点,\n请进入调试模式进行添加").arg(nodeName));
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

const QStringList& JsonTool::getFileConfigExplain()
{
	static QStringList explain({ "详情鼠标停留此处","总条码长度","判断前N个字符串,如果是空写NULL","slave地址长度,默认7位","读写slave地址","校验slave地址",
		"详情鼠标停留此处","0禁用,1启用;如果启用底层库延时将使用,默认0","底层库读取延时(单位:ms),默认0","底层库写入延时(单位:ms),默认0",
		"应用层读取延时(单位:ms),默认0","应用层写入延时(单位:ms),默认0","模块启动成功时间(单位:ms),默认3000ms",
		"烧录器速率,100kHz~800kHz,默认400kHz","烧录器超时,默认150ms","0禁用,1启用;校验数据重新上电,默认1" });
	return explain;
}

FileConfig* JsonTool::getParsedFileConfig()
{
	return &m_fileConfig;
}

FileConfig* JsonTool::getParsedAllFileConfig()
{
	return m_allFileConfig;
}

void JsonTool::printFileConfig()
{
	qDebug() << "文件路径:" << m_fileConfig.path << endl;
	qDebug() << "条码长度:" << m_fileConfig.codeLength << endl;
	qDebug() << "条码规则:" << m_fileConfig.codeRule << endl;
	qDebug() << "地址长度:" << m_fileConfig.addressLength << endl;
	qDebug("读写地址:0x%x\n", m_fileConfig.dataSlave);
	qDebug("校验地址:0x%x\n", m_fileConfig.checkSlave);
	qDebug() << "烧录模式:" << m_fileConfig.burnMode << endl;
	qDebug() << "极速模式:" << m_fileConfig.speedMode << endl;
	qDebug() << "底层读取:" << m_fileConfig.libReadDelay << endl;
	qDebug() << "底层写入:" << m_fileConfig.libWriteDelay << endl;
	qDebug() << "应层读取:" << m_fileConfig.appReadDelay << endl;
	qDebug() << "应层写入:" << m_fileConfig.appWriteDelay << endl;
	qDebug() << "重启延时:" << m_fileConfig.rebootDelay << endl;
	qDebug() << "设备速率:" << m_fileConfig.deviceSpeed << endl;
	qDebug() << "设备超时:" << m_fileConfig.deviceTimeout << endl;
	qDebug() << endl << endl;
}

/************************************************************************/
/* protected function                                                   */
/************************************************************************/
void JsonTool::setLastError(const QString& err)
{
#ifdef QT_DEBUG
	qDebug() << __FUNCTION__ << " " << err << endl;
#endif
	m_lastError = err;
}

bool JsonTool::readJsonFile(const QString& name)
{
	bool result = false, success = true;
	do
	{
		QFile file(name);
		if (!file.open(QIODevice::ReadOnly))
		{
			setLastError(file.errorString());
			break;
		}

		QByteArray bytes = file.readAll();
		file.close();
		
		QJsonParseError jsonError;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(bytes, &jsonError));
		if (jsonError.error != QJsonParseError::NoError)
		{
			setLastError(jsonError.errorString());
			break;
		}

		QJsonObject rootObj = jsonDoc.object();

		QList<QJsonObject*> objectList = { 
			&m_deviceConfigObj,
			&m_hardwareConfigObj,
			&m_relayConfigObj,
			&m_thresholdConfigObj,
			&m_userConfigObj,
			&m_fileConfigObj
		};

		bool (JsonTool:: * parseFnc[])() = { 
			&JsonTool::parseDeviceConfigData,
			&JsonTool::parseHardwareConfigData,
			&JsonTool::parseRelayConfigData,
			&JsonTool::parseThresholdConfigData,
			&JsonTool::parseUserConfigData,
			&JsonTool::parseFileConfigData
		};


		for (int i = 0; i < getAllMainKey().count(); i++)
		{
			if (rootObj.contains(getAllMainKey()[i]))
			{
				*objectList[i] = rootObj.value(getAllMainKey()[i]).toObject();
				if (!(this->*parseFnc[i])())
				{
					success = false;
					setLastError(QString("[%1]解析失败").arg(getAllMainKey()[i]));
					break;
				}
			}
			else
			{
				success = false;
				setLastError(QString("[%1]节点丢失").arg(getAllMainKey()[i]));
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

bool JsonTool::writeJsonFile(const QString& name)
{
	QJsonObject rootObj, deviceConfigObj, hardwareConfigObj,thresholdConfigObj,relayConfigObj;
	QJsonObject parentBinFileConfigObj, childBinFileConfigObj, userConfigObj;

	/*写设备配置*/
	for (int i = 0; i < getDeviceConfigCount(); i++)
	{
		deviceConfigObj.insert(getDeviceConfigKeyList()[i], getDeviceConfigValueList()[i]);
	}
	
	/*写硬件配置*/
	for (int i = 0; i < getHardwareConfigCount(); i++)
	{
		hardwareConfigObj.insert(getHardwareConfigKeyList()[i], getHardwareConfigValueList()[i]);
	}

	/*写继电器配置*/
	for (int i = 0; i < getRelayConfigCount(); i++)
	{
		relayConfigObj.insert(getRelayConfigKeyList()[i], getRelayConfigValueList()[i]);
	}
	
	/*写阈值配置*/
	for (int i = 0; i < getThresholdConfigCount(); i++)
	{
		thresholdConfigObj.insert(getThresholdConfigKeyList()[i], getThresholdConfigValueList()[i]);
	}

	/*写文件配置信息*/
	for (int i = 0; i < m_fileConfigKeyList.count(); i++)
	{
		childBinFileConfigObj.insert(m_fileConfigKeyList[i], m_fileConfigValueList[i]);
	}

	parentBinFileConfigObj.insert("A39-HSYNC", childBinFileConfigObj);

	/*写用户配置信息*/
	for (int i = 0; i < getUserConfigCount(); i++)
	{
		userConfigObj.insert(getUserConfigKeyList()[i], getUserConfigValueList()[i]);
	}

	rootObj.insert("设备配置", deviceConfigObj);
	
	rootObj.insert("硬件配置", hardwareConfigObj);

	rootObj.insert("继电器配置", relayConfigObj);
	
	rootObj.insert("阈值配置", thresholdConfigObj);

	rootObj.insert("文件配置", parentBinFileConfigObj);

	rootObj.insert("用户配置", userConfigObj);

	bool result = false;
	do
	{
		QJsonDocument doc(rootObj);
		QByteArray bytes = doc.toJson();
		QFile file(name);
		if (!file.open(QIODevice::WriteOnly))
		{
			setLastError(file.errorString());
			break;
		}
		if (bytes.count() != file.write(bytes))
		{
			file.close();
			setLastError("写入配置文件校验失败");
			break;
		}
		file.close();
		result = true;
	} while (false);
	return result;
}

bool JsonTool::updateJsonFile(const QString& name)
{
	bool result = false;
	
	QJsonObject rootObj;
	
	rootObj.insert("设备配置", m_deviceConfigObj);

	rootObj.insert("硬件配置", m_hardwareConfigObj);

	rootObj.insert("继电器配置", m_relayConfigObj);

	rootObj.insert("阈值配置", m_thresholdConfigObj);

	rootObj.insert("文件配置", m_fileConfigObj);

	rootObj.insert("用户配置", m_userConfigObj);

	do
	{
		QJsonDocument doc(rootObj);
		QByteArray bytes = doc.toJson();
		QFile file(name);
		if (!file.open(QIODevice::WriteOnly))
		{
			setLastError(file.errorString());
			break;
		}

		if (bytes.count() != file.write(bytes))
		{
			file.close();
			setLastError("写入配置文件校验失败");
			break;
		}
		file.close();
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseDeviceConfigData()
{
	bool result = false, success = true;
	do
	{
		QString* valuePtr = reinterpret_cast<QString*>(&m_deviceConfig);
		for (int i = 0; i < getDeviceConfigCount(); i++, valuePtr++)
		{
			*valuePtr = getDeviceConfigValue(getDeviceConfigKeyList()[i]);
			if (valuePtr->isEmpty())
			{
				*valuePtr = "数据错误";
				success = false;
			}
		}

		if (!success)
		{
			setLastError("解析设备配置数据错误");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseHardwareConfigData()
{
	bool result = false, convert = false, success = true;
	do 
	{
		int* valuePtr = reinterpret_cast<int*>(&m_hardwareConfig);
		for (int i = 0; i < getHardwareConfigCount(); i++, valuePtr++)
		{
			*valuePtr = getHardwareConfigValue(getHardwareConfigKeyList()[i]).toInt(&convert);
			if (!convert)
			{
				success = false;
			}
		}

		if (!success)
		{
			setLastError("解析硬件配置数据失败");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseThresholdConfigData()
{
	bool result = false, convert = false, success = true;
	do 
	{
		float* valuePtr = reinterpret_cast<float*>(&m_thresholdConfig);
		for (int i = 0; i < getThresholdConfigCount(); i++, valuePtr++)
		{
			*valuePtr = getThresholdConfigValue(getThresholdConfigKeyList()[i]).toFloat(&convert);
			if (!convert)
			{
				success = false;
			}
		}

		if (!success)
		{
			setLastError("解析阈值配置数据失败");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseRelayConfigData()
{
	bool result = true, convert = false, success = true;;
	do
	{
		for (int i = 0; i < getRelayConfigCount(); i++)
		{
			m_relayConfig[i].port = i;
			m_relayConfig[i].enable = getRelayConfigValue(getRelayConfigKeyList()[i]).toInt(&convert);
			if (!convert)
			{
				success = false;
			}
		}

		if (!success)
		{
			setLastError("解析继电器配置数据失败");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseFileConfigData()
{
	bool resutl = false, valid = true, convert = false;
	do 
	{
		SAFE_DELETE_A(m_allFileConfig);

		m_allFileConfig = new(std::nothrow) FileConfig[getFileConfigCount()];
		if (!m_allFileConfig)
		{
			setLastError("文件配置分配内存失败");
			break;
		}
		
		for (int i = 0; i < getFileConfigCount(); i++)
		{
			valid = true;

			m_allFileConfig[i].path = getFileConfigValue(getFileConfigObj().keys()[i], "文件路径");

			m_allFileConfig[i].nodeName = getFileConfigObj().keys()[i];
			
			m_allFileConfig[i].codeLength = getFileConfigValue(getFileConfigObj().keys()[i], "条码长度").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].codeRule = getFileConfigValue(getFileConfigObj().keys()[i], "条码规则");
			
			m_allFileConfig[i].addressLength = getFileConfigValue(getFileConfigObj().keys()[i], "地址长度").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].dataSlave = getFileConfigValue(getFileConfigObj().keys()[i], "读写地址")
				.toInt(&convert, 16) >> (8 - m_allFileConfig[i].addressLength);
			if (!convert) valid = false;

			m_allFileConfig[i].checkSlave = getFileConfigValue(getFileConfigObj().keys()[i], "校验地址")
				.toInt(&convert, 16) >> (8 - m_allFileConfig[i].addressLength);
			if (!convert) valid = false;

			m_allFileConfig[i].burnMode = getFileConfigValue(getFileConfigObj().keys()[i], "烧录模式").toInt(&convert);
			if (!convert) valid = false;
			
			m_allFileConfig[i].speedMode = getFileConfigValue(getFileConfigObj().keys()[i], "极速模式").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].libReadDelay = getFileConfigValue(getFileConfigObj().keys()[i], "底层读取").toInt(&convert);
			if (!convert) valid = false;
			
			m_allFileConfig[i].libWriteDelay = getFileConfigValue(getFileConfigObj().keys()[i], "底层写入").toInt(&convert);
			if (!convert) valid = false;
			
			m_allFileConfig[i].appReadDelay = getFileConfigValue(getFileConfigObj().keys()[i], "应层读取").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].appWriteDelay = getFileConfigValue(getFileConfigObj().keys()[i], "应层写入").toInt(&convert);
			if (!convert) valid = false;
			
			m_allFileConfig[i].rebootDelay = getFileConfigValue(getFileConfigObj().keys()[i], "重启延时").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].deviceSpeed = getFileConfigValue(getFileConfigObj().keys()[i], "设备速率").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].deviceTimeout = getFileConfigValue(getFileConfigObj().keys()[i], "设备超时").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].checkOutage = getFileConfigValue(getFileConfigObj().keys()[i], "校验断电").toInt(&convert);
			if (!convert) valid = false;

			m_allFileConfig[i].valid = valid;
		}
		resutl = true;
	} while (false);
	return resutl;
}
