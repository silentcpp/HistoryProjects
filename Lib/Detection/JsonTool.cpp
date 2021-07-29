#include "JsonTool.h"
#include "TextData.h"

#include <Can/Can.h>
#include <Uds/Uds.h>

static bool compareList(const QStringList& cmp1, const QStringList& cmp2)
{
	bool result = false;
	do 
	{
		if (cmp1.size() != cmp2.size())
		{
			break;
		}

		bool contains1 = true, contains2 = true;
		for (int i = 0; i < cmp1.size(); i++)
		{
			if (!cmp2.contains(cmp1[i]))
			{
				contains1 = false;
				break;
			}
		}

		for (int i = 0; i < cmp2.size(); i++)
		{
			if (!cmp1.contains(cmp2[i]))
			{
				contains2 = false;
				break;
			}
		}

		if (!contains1 || !contains2)
			break;

		result = true;
	} while (false);
	return result;
}

static bool removeList(const QStringList& list1, QStringList& list2)
{
	bool result = false;
	auto tempList = list2;
	for (auto& x : tempList)
	{
		if (!list1.contains(x))
		{
			result = true;
			list2.removeOne(x);
		}
	}
	return result;
}

JsonTool* JsonTool::m_self = nullptr;

void JsonTool::setLastError(const QString& error)
{
	m_lastError = error;
	if (m_errorList.size() > 1024)
	{
		m_errorList.clear();
	}
	m_errorList.append(error);
}

bool JsonTool::parseDeviceConfigData()
{
	bool result = false, success = true, convert = false;
	do
	{
		int structSize = sizeof(DeviceConfig) / sizeof(QString);

		if (structSize != m_deviceConfigKeyList.size())
		{
			setLastError("设备配置结构体大小与键列表不匹配");
			break;
		}

		if (structSize != m_deviceConfigValueList.size())
		{
			setLastError("设备配置结构体大小与值列表不匹配");
			break;
		}

		QString* valuePtr = reinterpret_cast<QString*>(&m_defConfig.device);
		for (int i = 0; i < m_deviceConfigKeyList.length(); i++, valuePtr++)
		{
			*valuePtr = getDeviceConfigValue(m_deviceConfigKeyList.value(i));
			if (valuePtr->isEmpty())
			{
				success = false;
				setLastError(QString("设备配置[%1]格式错误").arg(m_deviceConfigKeyList.value(i)));
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

bool JsonTool::parseHardwareConfigData()
{
	bool result = false, success = true, convert = false;
	do
	{
		//硬件配置结构体大小,存在数据格式不一致,无法做出校验,如新增键值,需自行校验
		int* valuePtr = reinterpret_cast<int*>(&m_defConfig.hardware);
		for (int i = 0; i < m_hardwareConfigKeyList.length(); i++, valuePtr++)
		{
			if (i == 2)
			{
				m_defConfig.hardware.powerVoltage = getHardwareConfigValue(m_hardwareConfigKeyList.value(i)).toFloat(&convert);
			}
			else if (i == 3)
			{
				m_defConfig.hardware.powerCurrent = getHardwareConfigValue(m_hardwareConfigKeyList.value(i)).toFloat(&convert);
			}
			else
			{
				*valuePtr = getHardwareConfigValue(m_hardwareConfigKeyList.value(i)).toInt(&convert);
			}

			if (!convert)
			{
				success = false;
				setLastError(QString("硬件配置[%1]格式错误").arg(m_hardwareConfigKeyList.value(i)));
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

bool JsonTool::parseRelayPortConfigData()
{
	bool result = false, success = true, convert = false;
	do
	{
		int structSize = sizeof(RelayConfig) / sizeof(int);
		if (structSize != m_relayConfigKeyList.size())
		{
			setLastError("继电器配置结构体大小与键列表不匹配");
			break;
		}

		if (structSize != m_relayConfigValueList.size())
		{
			setLastError("继电器配置结构体大小与值列表不匹配");
			break;
		}

		int* valuePtr = reinterpret_cast<int*>(&m_defConfig.relay);
		for (int i = 0; i < m_relayConfigKeyList.length(); i++, valuePtr++)
		{
			*valuePtr = getRelayConfigValue(m_relayConfigKeyList.value(i)).toInt(&convert);
			if (!convert)
			{
				success = false;
				setLastError(QString("继电器配置[%1]格式错误").arg(m_relayConfigKeyList.value(i)));
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

bool JsonTool::parseUserConfigData()
{
	return true;
}

bool JsonTool::parseImageConfigData()
{
	bool result = false, convert = true;
	do
	{
		int* valuePtr = nullptr;

		for (int i = 0; i < IMAGE_CHECK_COUNT; i++)
		{
			if (i == IMAGE_CHECK_COUNT - 1)
			{
				valuePtr = reinterpret_cast<int*>(&m_defConfig.image);
			}
			else if (i >= SMALL_RECT_ && i <= SMALL_RECT_ + BIG_RECT_ - 1)
			{
				valuePtr = reinterpret_cast<int*>(&(m_defConfig.image.bigRect[i - SMALL_RECT_]));
			}
			else
			{
				valuePtr = reinterpret_cast<int*>(&(m_defConfig.image.smallRect[i]));
			}

			for (int j = 0; j < m_childImageKeyList[i].count(); j++, (j || i == IMAGE_CHECK_COUNT - 1) ? valuePtr++ : valuePtr += sizeof(QString))
			{
				if (j || i == IMAGE_CHECK_COUNT - 1)
				{
					*valuePtr = getImageConfigValue(m_parentImageKeyList[i], m_childImageKeyList[i][j]).toInt(&convert);
				}
				else
				{
					const QString& color = m_defConfig.image.smallRect[i].color = getImageConfigValue(m_parentImageKeyList[i], m_childImageKeyList[i][j]);
					if ((!color.contains("!=") && !color.contains("==")))
					{
						convert = false;
						setLastError(QString("%1[%2],语法错误,\n判断语法,!=黑色(不等于黑色),==黑色(等于黑色)").arg(m_parentImageKeyList[i], m_childImageKeyList[i][j]));
						break;
					}
				}

				if (!convert)
				{
					setLastError(QString("%1[%2],格式错误").arg(m_parentImageKeyList[i], m_childImageKeyList[i][j]));
					break;
				}
			}

			if (!convert)
			{
				break;
			}
		}

		if (!convert)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseRangeConfigData()
{
	bool result = false, success = true;
	do
	{
		int structSize = sizeof(RangeConfig) / (sizeof(float) * 2);
		if (structSize != m_rangeConfigKeyList.size())
		{
			setLastError("范围配置结构体大小与键不匹配");
			break;
		}

		if (structSize != m_rangeConfigValueList.size())
		{
			setLastError("范围配置结构体大小与值不匹配");
			break;
		}

		float* valuePtr = reinterpret_cast<float*>(&m_defConfig.range);
		for (int i = 0; i < m_rangeConfigKeyList.length(); i++, valuePtr++, valuePtr++)
		{
			if (!parseRangeValue(getRangeConfigValue(m_rangeConfigKeyList.value(i)), *valuePtr, *(valuePtr + 1)))
			{
				setLastError(QString("范围配置[%1]格式错误").arg(m_rangeConfigKeyList.value(i)));
				success = false;
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

bool JsonTool::parseThresholdConfigData()
{
	bool result = false, success = true, convert = false;
	do
	{
		int structSize = sizeof(ThresholdConfig) / sizeof(float);
		if (structSize != m_thresholdConfigKeyList.size())
		{
			setLastError("阈值配置结构体大小与键不匹配");
			break;
		}

		if (structSize != m_thresholdConfigValueList.size())
		{
			setLastError("阈值配置结构体大小与值不匹配");
			break;
		}

		float* valuePtr = reinterpret_cast<float*>(&m_defConfig.threshold);
		for (int i = 0; i < m_thresholdConfigKeyList.length(); i++, valuePtr++)
		{
			*valuePtr = getThresholdConfigValue(m_thresholdConfigKeyList.value(i)).toFloat(&convert);
			if (!convert)
			{
				setLastError(QString("阈值配置[%1]格式错误").arg(m_thresholdConfigKeyList.value(i)));
				success = false;
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

bool JsonTool::parseEnableConfigData()
{
	bool result = false, convert = false, success = true;
	do 
	{
		int structSize = sizeof(EnableConfig) / sizeof(int);
		if (structSize != m_enableConfigKeyList.size())
		{
			setLastError("启用配置结构体大小与键不匹配");
			break;
		}

		if (structSize != m_enableConfigValueList.size())
		{
			setLastError("启用配置结构体大小与值不匹配");
			break;
		}

		int* valuePtr = reinterpret_cast<int*>(&m_defConfig.enable);
		for (int i = 0; i < m_enableConfigKeyList.length(); i++, valuePtr++)
		{
			*valuePtr = getEnableConfigValue(m_enableConfigKeyList[i]).toInt(&convert);
			if (!convert)
			{
				setLastError(QString("启用配置[%1]格式错误").arg(m_enableConfigKeyList[i]));
				success = false;
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

bool JsonTool::parseVoltageConfigData()
{
	bool result = false, convert = false, success = true;
	do
	{
		SAFE_DELETE_A(m_hwdConfig.voltage);

		m_hwdConfig.voltage = NO_THROW_NEW VoltageConfig[getVoltageConfigCount() + 1];
		VoltageConfig* voltage = m_hwdConfig.voltage;
		if (!voltage)
		{
			setLastError("电压配置分配内存失败");
			break;
		}

		memset(voltage, 0x00, sizeof(VoltageConfig));

		for (int i = 0; i < getVoltageConfigCount(); i++)
		{
			strcpy(voltage[i].name, Q_TO_C_STR(getParentVoltageConfigKeyList()[i]));
			voltage[i].high = getVoltageConfigValue(getParentVoltageConfigKeyList()[i], "上限").toFloat(&convert);
			if (!convert)
			{
				success = false;
				setLastError("电压配置[上限]格式错误");
				break;
			}
			voltage[i].low = getVoltageConfigValue(getParentVoltageConfigKeyList()[i], "下限").toFloat(&convert);
			if (!convert)
			{
				success = false;
				setLastError("电压配置[下限]格式错误");
				break;
			}
			voltage[i].relay = getVoltageConfigValue(getParentVoltageConfigKeyList()[i], "继电器IO").toInt(&convert);
			if (!convert)
			{
				success = false;
				setLastError("电压配置[继电器IO]格式错误");
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

bool JsonTool::parseKeyVolConfigData()
{
	bool result = false, convert = false, success = true;
	do
	{
		m_hwdConfig.keyVol.hULimit = getKeyVolConfigValue("高电平上限").toFloat(&convert);
		if (!convert)
		{
			setLastError("按键电压配置[高电平上限]格式错误");
			break;
		}

		m_hwdConfig.keyVol.hLLimit = getKeyVolConfigValue("高电平下限").toFloat(&convert);
		if (!convert)
		{
			setLastError("按键电压配置[高电平下限]格式错误");
			break;
		}

		m_hwdConfig.keyVol.lULimit = getKeyVolConfigValue("低电平上限").toFloat(&convert);
		if (!convert)
		{
			setLastError("按键电压配置[低电平上限]格式错误");
			break;
		}

		m_hwdConfig.keyVol.lLLimit = getKeyVolConfigValue("低电平下限").toFloat(&convert);
		if (!convert)
		{
			setLastError("按键电压配置[低电平下限]格式粗我");
			break;
		}

		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseCurrentConfigData()
{
	bool result = false, convert = false, success = true;
	do
	{
		SAFE_DELETE_A(m_hwdConfig.current);

		m_hwdConfig.current = NO_THROW_NEW CurrentConfig[getCurrentConfigCount() + 1];
		CurrentConfig* current = m_hwdConfig.current;
		if (!current)
		{
			setLastError("电流配置分配内存失败");
			break;
		}
		memset(current, 0x00, sizeof(CurrentConfig));
		for (int i = 0; i < getCurrentConfigCount(); i++)
		{
			strcpy(current[i].name, Q_TO_C_STR(getParentCurrentConfigKeyList()[i]));
			current[i].high = getCurrentConfigValue(getParentCurrentConfigKeyList()[i], "上限").toFloat(&convert);
			if (!convert)
			{
				setLastError("电流配置[上限]格式错误");
				break;
			}

			current[i].low = getCurrentConfigValue(getParentCurrentConfigKeyList()[i], "下限").toFloat(&convert);
			if (!convert)
			{
				setLastError("电流配置[下限]格式错误");
				break;
			}

			current[i].voltage = getCurrentConfigValue(getParentCurrentConfigKeyList()[i], "电压").toFloat(&convert);
			if (!convert)
			{
				setLastError("电流配置[电压]格式错误");
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseStaticConfigData()
{
	bool result = false, convert = false;
	do
	{
		m_hwdConfig.staticCurrent.high = getStaticConfigValue("上限").toFloat(&convert);
		if (!convert)
		{
			setLastError("静态电流配置[上限]格式错误");
			break;
		}

		m_hwdConfig.staticCurrent.low = getStaticConfigValue("下限").toFloat(&convert);
		if (!convert)
		{
			setLastError("静态电流配置[下限]格式错误");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::parseResConfigData()
{
	bool result = false, convert = false, success = true;
	do
	{
		SAFE_DELETE_A(m_hwdConfig.res);

		m_hwdConfig.res = NO_THROW_NEW ResConfig[getResConfigCount() + 1];
		ResConfig* res = m_hwdConfig.res;
		if (!res)
		{
			setLastError("电阻配置分配内存失败");
			break;
		}
		memset(res, 0x00, sizeof(ResConfig));
		for (int i = 0; i < getResConfigCount(); i++)
		{
			strcpy(m_hwdConfig.res[i].name, Q_TO_C_STR(getParentResConfigKeyList()[i]));
			m_hwdConfig.res[i].high = getResConfigValue(getParentResConfigKeyList()[i], "上限").toFloat(&convert);
			if (!convert)
			{
				success = false;
				break;
			}

			m_hwdConfig.res[i].low = getResConfigValue(getParentResConfigKeyList()[i], "下限").toFloat(&convert);
			if (!convert)
			{
				success = false;
				break;
			}

			m_hwdConfig.res[i].relay = getResConfigValue(getParentResConfigKeyList()[i], "继电器IO").toInt(&convert);
			if (!convert)
			{
				success = false;
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

bool JsonTool::parseVerConfigData()
{
	bool result = false, convert = false, success = false;
	do
	{
		const char* code[] = { "ASCII", "ASCR4", "INT", "USN", "BIN", "BCD","U08","ASCBCD44" };

		SAFE_DELETE_A(m_udsConfig.ver);

		m_udsConfig.ver = NO_THROW_NEW VersonConfig[getVerConfigCount() + 1];
		VersonConfig* ver = m_udsConfig.ver;
		if (!ver)
		{
			setLastError("版本配置分配内存失败");
			break;
		}

		memset(ver, 0x00, sizeof(VersonConfig));
		for (int i = 0; i < getVerConfigCount(); i++)
		{
			strcpy(ver[i].name, Q_TO_C_STR(getParentVerConfigKeyList()[i]));

			success = true;
			ushort did = getVerConfigValue(getParentVerConfigKeyList()[i], "DID").toUShort(&convert, 16);

			if (!convert)
			{
				success = false;
				setLastError("版本配置,DID格式错误");
				break;
			}

			ver[i].did[0] = did >> 8;
			ver[i].did[1] = did >> 0;

			strcpy(ver[i].setup, Q_TO_C_STR(getVerConfigValue(getParentVerConfigKeyList()[i], "值")));
			strcpy(ver[i].encode, Q_TO_C_STR(getVerConfigValue(getParentVerConfigKeyList()[i], "编码").toUpper()));

			success = false;
			for (int j = 0; j < sizeof(code) / sizeof(char*); j++)
			{
				if (!strcmp(ver[i].encode, code[j]))
				{
					success = true;
					break;
				}
			}

			if (!success)
			{
				setLastError(QString("版本配置[%1]编码格式错误").arg(getParentVerConfigKeyList()[i]));
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

bool JsonTool::parseDtcConfigData()
{
	bool result = false, convert = false, success = true;
	do
	{
		SAFE_DELETE_A(m_udsConfig.dtc);

		m_udsConfig.dtc = NO_THROW_NEW DtcConfig[getDtcConfigCount() + 1];
		DtcConfig* dtc = m_udsConfig.dtc;
		if (!dtc)
		{
			setLastError("诊断故障码配置分配内存失败");
			break;
		}
		memset(dtc, 0x00, sizeof(DtcConfig));
		for (int i = 0; i < getDtcConfigCount(); i++)
		{
			strcpy(m_udsConfig.dtc[i].name, Q_TO_C_STR(getParentDtcConfigKeyList()[i]));
			QString dtc = dtcCategoryConvert(getDtcConfigValue(getParentDtcConfigKeyList()[i], "DTC"));
			if (dtc.isEmpty())
			{
				break;
			}

			size_t bytes = dtc.toUInt(&convert, 16);
			if (!convert)
			{
				setLastError("诊断配置[DTC]格式错误");
				break;
			}

			m_udsConfig.dtc[i].dtc[0] = bytes >> 16;
			m_udsConfig.dtc[i].dtc[1] = bytes >> 8;
			m_udsConfig.dtc[i].dtc[2] = bytes >> 0;

			m_udsConfig.dtc[i].ignore = getDtcConfigValue(getParentDtcConfigKeyList()[i], "忽略").toInt(&convert);
			if (!convert)
			{
				setLastError("诊断配置[忽略]格式错误");
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

QString JsonTool::dtcCategoryConvert(const QString& dtc)
{
	QString result = "";
	bool convert = false;
	do
	{
		int category = -1;
		switch (dtc[0].toLatin1())
		{
		case 'B':category = 0x8; break;
		case 'C':category = 0x4; break;
		case 'P':category = 0x0; break;
		case 'U':category = 0xC; break;
		default:break;
		}

		if (category == -1)
		{
			setLastError("诊断故障码,代码种类不符合规则");
			break;
		}

		category += dtc.mid(1, 1).toInt(&convert);
		if (!convert)
		{
			setLastError("诊断故障码常规转换失败");
			break;
		}
		result = dtc;
		result.replace(dtc.mid(0, 2), QString::number(category, 16).toUpper());
	} while (false);
	return result;
}

JsonTool::JsonTool(QObject* parent)
	: QObject(parent)
{
}

JsonTool::~JsonTool()
{
	SAFE_DELETE_A(m_hwdConfig.current);

	SAFE_DELETE_A(m_hwdConfig.res);

	SAFE_DELETE_A(m_hwdConfig.voltage);

	SAFE_DELETE_A(m_udsConfig.ver);

	SAFE_DELETE_A(m_udsConfig.dtc);
}

bool JsonTool::parseRangeValue(const QString& value, float& min, float& max)
{
	bool result = false;
	do
	{
		QStringList split = value.split("~", QString::SkipEmptyParts);
		if (split.size() != 2)
		{
			break;
		}

		bool convert = false;
		min = split[0].toFloat(&convert);
		if (!convert)
		{
			break;
		}
		max = split[1].toFloat(&convert);
		if (!convert)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

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

const QString& JsonTool::getLastError()
{
	return m_lastError;
}

const QStringList& JsonTool::getErrorList()
{
	return m_errorList;
}

void JsonTool::setFolderName(const QString& name)
{
	m_folderName = name;
}

bool JsonTool::initInstance(bool update, const QString& folderName, const QStringList& fileName)
{
	bool result = false, success = true;
	do
	{
		QString dirName = m_folderName.isEmpty() ? folderName : m_folderName;
		QString jsonPath = QString("%1/JsonFile_%2").arg(dirName, JSON_VERSION);
		QString dcfPath = QString("%1/DcfFile_%2").arg(dirName, DCF_VERSION);

		QStringList pathList = { jsonPath,dcfPath };
		for (int i = 0; i < pathList.count(); i++)
		{
			if (!QDir(pathList[i]).exists())
			{
				QDir dir;
				if (!dir.mkpath(pathList[i]))
				{
					success = false;
					setLastError(QString("创建文件夹%1失败").arg(pathList[i]));
					break;
				}
			}
		}

		if (!success)
		{
			break;
		}

		bool (JsonTool:: * readFnc[])(const QString&) =
		{
			&JsonTool::readDefJsonFile,
			&JsonTool::readHwdJsonFile,
			&JsonTool::readUdsJsonFile,
			&JsonTool::readImgJsonFile,
			&JsonTool::readOthJsonFile
		};

		bool (JsonTool:: * writeFnc[])(const QString&) =
		{
			&JsonTool::writeDefJsonFile,
			&JsonTool::writeHwdJsonFile,
			&JsonTool::writeUdsJsonFile,
			&JsonTool::writeImgJsonFile,
			&JsonTool::writeOthJsonFile
		};

		bool (JsonTool:: * updateFnc[])(const QString&) =
		{
			&JsonTool::updateDefJsonFile,
			&JsonTool::updateHwdJsonFile,
			&JsonTool::updateUdsJsonFile,
			&JsonTool::updateImgJsonFile,
			&JsonTool::updateOthJsonFile
		};

		RUN_BREAK(fileName.size() != sizeof(readFnc) / sizeof(*readFnc) ||
			fileName.size() != sizeof(writeFnc) / sizeof(*writeFnc) ||
			fileName.size() != sizeof(updateFnc) / sizeof(*updateFnc),
			"文件名列表与函数指针数组不对应");

		for (int i = 0; i < fileName.size(); i++)
		{
			const QString file = QString("./%1/%2").arg(jsonPath, fileName.value(i));
			if (!QFileInfo(file).exists() || update)
			{
				if (update ? !(this->*updateFnc[i])(file) : !(this->*writeFnc[i])(file))
				{
					success = false;
					break;
				}
			}

			if (!(this->*readFnc[i])(file))
			{
				success = false;
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

QStringList JsonTool::getAllMainKey()
{
	//此列表顺序不可修改,否则将会导致SettingDlg加载崩溃
	static QStringList keys =
	{
		"设备配置",//0
		"硬件配置",//1
		"继电器配置",//2
		"范围配置",//3
		"阈值配置",//4
		"图像配置",//5
		"按键电压配置",//6
		"电压配置",//7
		"电流配置",//8
		"电阻配置",//9
		"静态电流配置",//10
		"版本配置",//11
		"诊断故障码配置",//12
		"启用配置",//13
		"用户配置"//14
	};
	return keys;
}

QString JsonTool::getLibVersion()
{
	return LIB_VERSION;
}

QString JsonTool::getJsonVersion()
{
	return JSON_VERSION;
}

QString JsonTool::getDcfVersion()
{
	return DCF_VERSION;
}

bool JsonTool::writeDcfFile(const QString& name)
{
	bool result = false;
	do 
	{
		QFile file(name);
		if (!file.open(QFile::WriteOnly))
		{
			setLastError(file.errorString());
			break;
		}

		int length = strlen(TextData::ntscData);
		if (file.write(TextData::ntscData, length) != length)
		{
			setLastError("写入数据长度校验失败");
			break;
		}
		file.close();
		result = true;
	} while (false);
	return result;
}

bool JsonTool::readJsonFile(const QString& name, QJsonObject& rootObj)
{
	bool result = false;
	do 
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::ReadOnly), file.errorString());
		QByteArray bytes = file.readAll();
		file.close();

		QJsonParseError jsonError;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(bytes, &jsonError));
		RUN_BREAK(jsonError.error != QJsonParseError::NoError, jsonError.errorString());
		rootObj = jsonDoc.object();
		result = true;
	} while (false);
	return result;
}

bool JsonTool::writeJsonFile(const QString& name, const QJsonObject& rootObj)
{
	bool result = false;
	do 
	{
		QJsonDocument doc(rootObj);
		QByteArray bytes = doc.toJson();
		QFile file(name);
		RUN_BREAK(!file.open(QFile::WriteOnly), file.errorString());
		if (bytes.length() != file.write(bytes))
		{
			setLastError(QString("写入%1数据校验失败").arg(name));
			file.close();
			break;
		}
		file.close();
		result = true;
	} while (false);
	return result;
}

bool JsonTool::testDefJsonFile(const QString& name)
{
	bool result = false, save = false;
	do
	{
		QJsonObject rootObj;
		RUN_BREAK(!readJsonFile(name, rootObj), "自检读取def.json文件失败," + getLastError())

		QStringList keyList =
		{
			"设备配置",
			"硬件配置",
			"继电器配置",
			"用户配置",
			"范围配置",
			"阈值配置",
			"启用配置"
		};

		QList<QStringList*>memberKeyList = 
		{ 
			&m_deviceConfigKeyList,
			&m_hardwareConfigKeyList,
			&m_relayConfigKeyList,
			&m_userConfigKeyList,
			&m_rangeConfigKeyList,
			&m_thresholdConfigKeyList,
			&m_enableConfigKeyList 
		};

		QList<QStringList*>memberValueList = 
		{
			&m_deviceConfigValueList,
			&m_hardwareConfigValueList,
			&m_relayConfigValueList,
			&m_userConfigValueList,
			&m_rangeConfigValueList,
			&m_thresholdConfigValueList,
			&m_enableConfigValueList
		};

		const QString(JsonTool:: * valueFnc[])(const QString&) =
		{
			&JsonTool::getDeviceConfigDefaultValue,
			&JsonTool::getHardwareConfigDefaultValue,
			&JsonTool::getRelayConfigDefaultValue,
			&JsonTool::getUserConfigDefaultValue,
			&JsonTool::getRangeConfigDefaultValue,
			&JsonTool::getThresholdConfigDefaultValue,
			&JsonTool::getEnableConfigDefaultValue
		};

		for (int i = 0; i < keyList.count(); i++)
		{
			QStringList objectKeyList, loseKeyList, loseValueList;
			if (rootObj.contains(keyList[i]))
			{
				loseKeyList = *memberKeyList[i];
				QJsonObject jsonObject = rootObj.value(keyList[i]).toObject();
				objectKeyList = jsonObject.keys();
				QStringList oldObjectKeyList = objectKeyList;
				if (removeList(*memberKeyList[i], objectKeyList))
				{
					QStringList removeObjList;
					for (int j = 0; j < oldObjectKeyList.size(); j++)
					{
						if (!objectKeyList.contains(oldObjectKeyList[j]))
						{
							removeObjList.push_back(oldObjectKeyList[j]);
						}
					}

					for (auto& x : removeObjList)
					{
						m_errorList.append(QString("%1 未知{ 键 }:{ %2 } 已自动删除").
							arg(keyList[i], x));
						jsonObject.remove(x);
					}
				}

				if (!compareList(*memberKeyList[i], objectKeyList))
				{
					for (int j = 0; j < memberKeyList[i]->size(); j++)
					{
						for (int k = 0; k < objectKeyList.size(); k++)
						{
							if (memberKeyList[i]->at(j) == objectKeyList[k])
							{
								loseKeyList.removeOne(objectKeyList[k]);
							}
						}
					}

					for (int j = 0; j < loseKeyList.size(); j++)
					{
						loseValueList.append((this->*valueFnc[i])(loseKeyList[j]));
					}

					for (int j = 0; j < loseKeyList.size(); j++)
					{
						jsonObject.insert(loseKeyList[j], loseValueList[j]);
						m_errorList.append(QString("%1 丢失{ 键 / 值 }:{ %2 / %3 } 已自动添加").
							arg(keyList[i], loseKeyList[j], loseValueList[j]));
					}
				}

				if (jsonObject != rootObj.value(keyList[i]).toObject())
				{
					save = true;
					rootObj.insert(keyList[i], jsonObject);
				}
			}
		}

		if (save)
		{
			RUN_BREAK(!writeJsonFile(name, rootObj), "自检写入def.json失败,"
				+ getLastError());
		}
		result = true;
	} while (false);
	return result;
}

#define NEW_IMAGE_JSON 1
bool JsonTool::readDefJsonFile(const QString& name)
{
	bool result = false, success = true;
	do
	{
		testDefJsonFile(name);

		QJsonObject rootObj;
		RUN_BREAK(!readJsonFile(name, rootObj), "读取def.json配置文件失败," + getLastError());

#if NEW_IMAGE_JSON
		QStringList keyList = 
		{ 
			"设备配置",
			"硬件配置",
			"继电器配置",
			"用户配置",
			"范围配置",
			"阈值配置",
			"启用配置" 
		};

		QList<QJsonObject*>objList =
		{
			&m_deviceConfigObj,
			&m_hardwareConfigObj,
			&m_relayConfigObj,
			&m_userConfigObj,
			&m_rangeConfigObj,
			&m_thresholdConfigObj,
			&m_enableConfigObj
		};

		bool (JsonTool:: * parseFnc[])() = 
		{
			&JsonTool::parseDeviceConfigData,
			&JsonTool::parseHardwareConfigData,
			&JsonTool::parseRelayPortConfigData,
			&JsonTool::parseUserConfigData,
			&JsonTool::parseRangeConfigData,
			&JsonTool::parseThresholdConfigData,
			&JsonTool::parseEnableConfigData
		};

#else
		QStringList keyList = { "设备配置","硬件配置","继电器配置","用户配置",
			"图像配置","范围配置","阈值配置","启用配置" };

		QList<QJsonObject*>objList = { &m_deviceConfigObj,&m_hardwareConfigObj,&m_relayConfigObj,
		&m_userConfigObj,&m_imageConfigObj,&m_rangeConfigObj,&m_thresholdConfigObj,&m_enableConfigObj };

		bool (JsonTool:: * parseFnc[])() = {
			&JsonTool::parseDeviceConfigData,
			&JsonTool::parseHardwareConfigData,
			&JsonTool::parseRelayPortConfigData,
			&JsonTool::parseUserConfigData,
			&JsonTool::parseImageConfigData,
			&JsonTool::parseRangeConfigData,
			&JsonTool::parseThresholdConfigData,
			&JsonTool::parseEnableConfigData
		};
#endif
		for (int i = 0; i < keyList.count(); i++)
		{
			if (rootObj.contains(keyList[i]))
			{
				*objList[i] = rootObj.value(keyList[i]).toObject();
				if (!(this->*parseFnc[i])())
				{
					success = false;
					break;
				}
			}
			else
			{
				setLastError(QString("%1配置文件未找到对象名%2").arg(name, keyList[i]));
				success = false;
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

bool JsonTool::writeDefJsonFile(const QString& name)
{
	QJsonObject rootObj, deviceConfigObj, hardwareConfigObj,
		relayIoConfigObj, userConfigObj, rangeConfigObj,
		thresholdConfigObj, enableConfigObj;

	/*写设备配置*/
	for (int i = 0; i < m_deviceConfigKeyList.length(); i++)
	{
		deviceConfigObj.insert(m_deviceConfigKeyList[i], m_deviceConfigValueList[i]);
	}

	/*写硬件配置*/
	for (int i = 0; i < m_hardwareConfigKeyList.length(); i++)
	{
		hardwareConfigObj.insert(m_hardwareConfigKeyList[i], m_hardwareConfigValueList[i]);
	}

	/*写继电器IO端口配置*/
	for (int i = 0; i < m_relayConfigKeyList.length(); i++)
	{
		relayIoConfigObj.insert(m_relayConfigKeyList[i], m_relayConfigValueList[i]);
	}

	/*写用户配置*/
	for (int i = 0; i < m_userConfigKeyList.length(); i++)
	{
		userConfigObj.insert(m_userConfigKeyList[i], m_userConfigValueList[i]);
	}

	/*范围配置*/
	for (int i = 0; i < m_rangeConfigKeyList.length(); i++)
	{
		rangeConfigObj.insert(m_rangeConfigKeyList[i], m_rangeConfigValueList[i]);
	}

#if !NEW_IMAGE_JSON
	/*图像配置*/
	QJsonObject childImageCheckObj[IMAGE_CHECK_COUNT];

	for (int i = 0; i < IMAGE_CHECK_COUNT; i++)
	{
		for (int j = 0; j < m_childImageKeyList[i].size(); j++)
		{
			childImageCheckObj[i].insert(m_childImageKeyList[i].value(j), m_childImageValueList[i].value(j));
		}
	}

	QJsonObject imageConfigObj;
	for (int i = 0; i < m_parentImageKeyList.size(); i++)
	{
		imageConfigObj.insert(m_parentImageKeyList.value(i), childImageCheckObj[i]);
	}
#endif

	/*阈值配置*/
	for (int i = 0; i < m_thresholdConfigKeyList.length(); i++)
	{
		thresholdConfigObj.insert(m_thresholdConfigKeyList[i], m_thresholdConfigValueList[i]);
	}

	/*启用配置*/
	for (int i = 0; i < m_enableConfigKeyList.length(); i++)
	{
		enableConfigObj.insert(m_enableConfigKeyList[i], m_enableConfigValueList[i]);
	}

	rootObj.insert("设备配置", deviceConfigObj);
	rootObj.insert("硬件配置", hardwareConfigObj);
	rootObj.insert("范围配置", rangeConfigObj);
	rootObj.insert("用户配置", userConfigObj);
#if !NEW_IMAGE_JSON
	rootObj.insert("图像配置", imageConfigObj);
#endif
	rootObj.insert("继电器配置", relayIoConfigObj);
	rootObj.insert("阈值配置", thresholdConfigObj);
	rootObj.insert("启用配置", enableConfigObj);

	bool result = false;
	do 
	{
		RUN_BREAK(!writeJsonFile(name, rootObj), "写入def.json配置失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::updateDefJsonFile(const QString& name)
{
	QJsonObject rootObj;
	rootObj.insert("设备配置", m_deviceConfigObj);
	rootObj.insert("硬件配置", m_hardwareConfigObj);
	rootObj.insert("范围配置", m_rangeConfigObj);
	rootObj.insert("用户配置", m_userConfigObj);
#if !NEW_IMAGE_JSON
	rootObj.insert("图像配置", m_imageConfigObj);
#endif
	rootObj.insert("继电器配置", m_relayConfigObj);
	rootObj.insert("阈值配置", m_thresholdConfigObj);
	rootObj.insert("启用配置", m_enableConfigObj);

	bool result = false;
	do
	{
		RUN_BREAK(!writeJsonFile(name, rootObj), "更新def.json配置文件失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::readHwdJsonFile(const QString& name)
{
	bool result = false, success = true;
	do
	{
		QJsonObject root;
		RUN_BREAK(!readJsonFile(name, root), "读取hwd.json配置文件失败," + getLastError());

		QStringList keyList = { "电压配置","按键电压配置","电流配置","静态电流配置","电阻配置" };
		
		QList<QJsonObject*> objList = { &m_voltageConfigObj,&m_keyVolConfigObj,&m_currentConfigObj
			,&m_staticConfigObj ,&m_resConfigObj };

		bool (JsonTool:: * parseFnc[])() = { 
			&JsonTool::parseVoltageConfigData,
			&JsonTool::parseKeyVolConfigData,
			&JsonTool::parseCurrentConfigData,
			&JsonTool::parseStaticConfigData,
			&JsonTool::parseResConfigData };

		for (int i = 0; i < keyList.count(); i++)
		{
			if (root.contains(keyList[i]))
			{
				*objList[i] = root.value(keyList[i]).toObject();
				if (!(this->*parseFnc[i])())
				{
					success = false;
					break;
				}
			}
			else
			{
				setLastError(QString("%1配置文件未找到对象名%2").arg(name, keyList[i]));
				success = false;
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

bool JsonTool::writeHwdJsonFile(const QString& name)
{
	bool result = false;
	do
	{
		QJsonObject rootObj, voltageObj, keyVolObj, currentObj, staticObj, resObj;

		/*电压默认配置*/
		QList<QJsonObject> voltageList;
		for (int i = 0; i < 2; i++)
		{
			QJsonObject obj;
			for (int j = 0; j < getChildVoltageConfigKeyList().count(); j++)
			{
				obj.insert(getChildVoltageConfigKeyList()[j], getChildVoltageConfigValueList()[j]);
			}
			voltageList.append(obj);
		}

		voltageObj.insert("1.8V电压", voltageList[0]);
		voltageObj.insert("3.3V电压", voltageList[1]);

		/*按键默认配置*/
		for (int i = 0; i < getKeyVolConfigKeyList().size(); i++)
		{
			keyVolObj.insert(getKeyVolConfigKeyList()[i], getKeyVolConfigValueList()[i]);
		}

		/*电流默认配置*/
		QList<QJsonObject> currentList;
		for (int i = 0; i < 2; i++)
		{
			QJsonObject obj;
			for (int j = 0; j < getChildCurrentConfigKeyList().count(); j++)
			{
				obj.insert(getChildCurrentConfigKeyList()[j], getChildCurrentConfigValueList(i)[j]);
			}
			currentList.append(obj);
		}
		currentObj.insert("12V工作电流", currentList[0]);
		currentObj.insert("16V工作电流", currentList[1]);

		/*静态电流默认配置*/
		for (int i = 0; i < getStaticConfigKeyList().count(); i++)
		{
			staticObj.insert(getStaticConfigKeyList()[i], getStaticConfigValueList()[i]);
		}

		/*RES电阻配置*/
		QList<QJsonObject> resList;
		for (int i = 0; i < 2; i++)
		{
			QJsonObject obj;
			for (int j = 0; j < getChildResConfigKeyList().count(); j++)
			{
				obj.insert(getChildResConfigKeyList()[j], getChildResConfigValueList()[j]);
			}
			resList.append(obj);
		}
		resObj.insert("12V对地电阻", resList[0]);
		resObj.insert("16V对地电阻", resList[1]);

		/*根节点默认配置*/
		rootObj.insert("电压配置", voltageObj);
		rootObj.insert("按键电压配置", keyVolObj);
		rootObj.insert("电流配置", currentObj);
		rootObj.insert("静态电流配置", staticObj);
		rootObj.insert("电阻配置", resObj);

		RUN_BREAK(!writeJsonFile(name, rootObj), "写入hwd.json配置文件失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::updateHwdJsonFile(const QString& name)
{
	bool result = false;
	do
	{
		QJsonObject rootObj;
		rootObj.insert("电压配置", m_voltageConfigObj);
		rootObj.insert("按键电压配置", m_keyVolConfigObj);
		rootObj.insert("电流配置", m_currentConfigObj);
		rootObj.insert("静态电流配置", m_staticConfigObj);
		rootObj.insert("电阻配置", m_resConfigObj);

		RUN_BREAK(!writeJsonFile(name, rootObj), "更新hwd.json配置文件失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::testImgJsonFile(const QString& name)
{
	bool result = false;
	do 
	{
		QJsonObject rootObj;
		RUN_BREAK(!readJsonFile(name, rootObj), "自检读取img.json文件失败," + getLastError());

		if (rootObj.contains("图像配置"))
		{
			QJsonObject parentObj = rootObj.value("图像配置").toObject();
		}

		result = true;
	} while (false);
	return result;
}

bool JsonTool::readImgJsonFile(const QString& name)
{
	bool result = false;
	do 
	{
		QJsonObject rootObj;
		RUN_BREAK(!readJsonFile(name, rootObj), "读取img.json配置文件失败," + getLastError());

		if (!rootObj.contains("图像配置"))
		{
			setLastError(QString("%1配置文件未找到对象名图像配置").arg(name));
			break;
		}

		m_imageConfigObj = rootObj.value("图像配置").toObject();
		if (!parseImageConfigData())
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool JsonTool::writeImgJsonFile(const QString& name)
{
	bool result = false;
	do 
	{
		QJsonObject rootObj;

		QJsonObject childImageCheckObj[IMAGE_CHECK_COUNT];
		for (int i = 0; i < IMAGE_CHECK_COUNT; i++)
		{
			for (int j = 0; j < m_childImageKeyList[i].size(); j++)
			{
				childImageCheckObj[i].insert(m_childImageKeyList[i].value(j), m_childImageValueList[i].value(j));
			}
		}

		QJsonObject imageConfigObj;
		for (int i = 0; i < m_parentImageKeyList.size(); i++)
		{
			imageConfigObj.insert(m_parentImageKeyList.value(i), childImageCheckObj[i]);
		}

		rootObj.insert("图像配置", imageConfigObj);

		RUN_BREAK(!writeJsonFile(name, rootObj), "写入img.json配置失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::updateImgJsonFile(const QString& name)
{
	bool result = false;
	do 
	{
		QJsonObject rootObj;
		rootObj.insert("图像配置", m_imageConfigObj);
		RUN_BREAK(!writeJsonFile(name, rootObj), "更新img.json配置文件失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::readOthJsonFile(const QString& name)
{
	bool result = false;
	do 
	{
		QJsonObject rootObj;
		RUN_BREAK(!readJsonFile(name, rootObj), "读取oth.json配置文件失败," + getLastError());
		RUN_BREAK(!rootObj.contains("其他配置"), "丢失对象[其他配置]");
		m_othConfigObj = rootObj.value("其他配置").toObject();
		result = true;
	} while (false);
	return result;
}

bool JsonTool::writeOthJsonFile(const QString& name)
{
	bool result = false;
	do 
	{
		QJsonObject rootObj;
		rootObj.insert("其他配置",QJsonObject());
		RUN_BREAK(!writeJsonFile(name, rootObj), "写入oth.json配置文件失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::updateOthJsonFile(const QString& name)
{
	return true;
}

bool JsonTool::readUdsJsonFile(const QString& name)
{
	bool result = false, success = false;
	do
	{
		QJsonObject root;
		RUN_BREAK(!readJsonFile(name, root), "读取uds.json配置文件失败," + getLastError());
		if (root.contains("版本配置"))
		{
			m_verConfigObj = root.value("版本配置").toObject();
			parseVerConfigData();
		}

		if (root.contains("诊断配置"))
		{
			m_dtcConfigObj = root.value("诊断配置").toObject();
			parseDtcConfigData();
		}

		result = true;
	} while (false);
	return result;
}

bool JsonTool::writeUdsJsonFile(const QString& name)
{
	bool result = false;
	do
	{
		QJsonObject rootObj, verObj0, verObj1, verObj2,
			dtcObj0, dtcObj1, dtcObj2;
		verObj0.insert("DID", "0xF187");
		verObj0.insert("编码", "ASCII");
		verObj0.insert("值", "A00087710");

		verObj1.insert("DID", "0xF193");
		verObj1.insert("编码", "ASCII");
		verObj1.insert("值", "0.03");

		verObj2.insert("广汽ECU硬件版本号", verObj0);
		verObj2.insert("应用程序版本号", verObj1);

		dtcObj0.insert("DTC", "U100900");
		dtcObj0.insert("忽略", "0");

		dtcObj1.insert("DTC", "U100587");
		dtcObj1.insert("忽略", "0");

		dtcObj2.insert("蓄电池供电电压低于工作阈值", dtcObj0);
		dtcObj2.insert("蓄电池供电电压高于工作阈值", dtcObj1);

		rootObj.insert("版本配置", verObj2);
		rootObj.insert("诊断配置", dtcObj2);

		RUN_BREAK(!writeJsonFile(name, rootObj), "写入uds.json配置文件失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

bool JsonTool::updateUdsJsonFile(const QString& name)
{
	bool result = false;
	do
	{
		QJsonObject rootObj;
		rootObj.insert("版本配置", m_verConfigObj);
		rootObj.insert("诊断配置", m_dtcConfigObj);

		RUN_BREAK(!writeJsonFile(name, rootObj), "更新uds.json配置文件失败," + getLastError());
		result = true;
	} while (false);
	return result;
}

const int JsonTool::getDeviceConfigCount()
{
	return m_deviceConfigObj.count();
}

const QString JsonTool::getDeviceConfigValue(const QString& key)
{
	return m_deviceConfigObj[key].toString();
}

const QStringList& JsonTool::getDeviceConfigKeyList()
{
	return m_deviceConfigKeyList;
}

const DeviceConfig& JsonTool::getParsedDeviceConfig()
{
	return m_defConfig.device;
}

const QJsonObject& JsonTool::getDeviceConfigObj()
{
	return m_deviceConfigObj;
}

bool JsonTool::setDeviceConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		if (key == "条码长度" || key == "采集卡通道数" || key == "采集卡通道号" ||
			key == "CAN波特率" || key == "CAN拓展帧")
		{
			int number = value.toInt(&convert);
			if (!convert)
			{
				setLastError(key + "必须为整数");
				break;
			}

			if (key == "采集卡通道数")
			{
				if (number <= 0 || number > 2)
				{
					setLastError(getDeviceConfigValue("采集卡名称") + key + ",最大支持2个通道同时开启");
					break;
				}
			}

			if (key == "采集卡通道号")
			{
				if (number < 0 || number > 1)
				{
					setLastError(getDeviceConfigValue("采集卡名称") + key + ",仅支持0或者1通道");
					break;
				}
			}
		}
		else if (key == "采集卡名称")
		{
			if (value != MV800_CC && value != MOR_CC && value != ANY_CC)
			{
				setLastError("采集卡仅支持MOR,MV800,ANY");
				break;
			}
		}
		else if (key == "条码判断")
		{
			if (value.isEmpty())
			{
				setLastError("条码判断如果为空,请写NULL");
				break;
			}
		}
		else if (key == "UDS名称")
		{
			if (!Uds::getSupportUds().contains(value))
			{
				setLastError(QString("[%1]不在支持的范围内").arg(value));
				break;
			}
		}
		else if (key == "CAN名称")
		{
			if (!Can::getSupportCan().contains(value))
			{
				setLastError(QString("[%1]不在支持的范围内").arg(value));
				break;
			}
		}

		if (!m_deviceConfigObj.contains(key))
		{
			setLastError(QString("%1非法的键").arg(key));
			break;
		}
		m_deviceConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getDeviceConfigExplain()
{
	static QStringList explain = 
	{ 
		"界面标题", 
		"鼠标悬停查看提示", 
		"ZLG ADV KVASER UART GCANFD",
		"默认:500",
		"0禁用,1启用",
		"MOR MV800 ANY",
		"鼠标悬停查看提示",
		"MV800,AV1是1,AV2是0",
		"前N位字符串", 
		"条码总长度"
	};
	return explain;
}

const QString JsonTool::getDeviceConfigDefaultValue(const QString& key)
{
	QString result = "0";
	for (int i = 0; i < m_deviceConfigKeyList.size(); i++)
	{
		if (m_deviceConfigKeyList[i] == key)
		{
			result = m_deviceConfigValueList.at(i);
			break;
		}
	}
	return result;
}

const QString JsonTool::getHardwareConfigValue(const QString& key)
{
	return m_hardwareConfigObj[key].toString();
}

const int JsonTool::getHardwareConfigCount()
{
	return m_hardwareConfigObj.count();
}

const QStringList& JsonTool::getHardwareConfigKeyList()
{
	return m_hardwareConfigKeyList;
}

const HardwareConfig& JsonTool::getParseHardwareConfig()
{
	return m_defConfig.hardware;
}

bool JsonTool::setHardwareConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toInt(&convert);
		if (!convert)
		{
			setLastError(QString("%1必须为数字").arg(key));
			break;
		}

		if (!m_hardwareConfigObj.contains(key))
		{
			setLastError(QString("%1非法的键").arg(key));
			break;
		}

		m_hardwareConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getHardwareConfigExplain()
{
	static QStringList explain = 
	{ 
		"串口编号",
		"默认:19200",
		"单位:伏(V)",
		"单位:安培(A)",
		"串口编号",
		"默认:19200",
		"串口编号",
		"默认:9600",
		"串口编号",
		"默认:9600",
		"预留拓展",
		"预留拓展",
		"预留拓展",
		"预留拓展",
		"预留拓展",
		"预留拓展",
		"预留拓展",
		"预留拓展"
	};
	return explain;
}

const QString JsonTool::getHardwareConfigDefaultValue(const QString& key)
{
	QString result = "0";
	for (int i = 0; i < m_hardwareConfigKeyList.size(); i++)
	{
		if (m_hardwareConfigKeyList[i] == key)
		{
			result = m_hardwareConfigValueList.at(i);
			break;
		}
	}
	return result;
}

const QString JsonTool::getRelayConfigValue(const QString& key)
{
	return m_relayConfigObj[key].toString();
}

const int JsonTool::getRelayConfigCount()
{
	return m_relayConfigObj.count();
}

const RelayConfig& JsonTool::getParsedRelayConfig()
{
	return m_defConfig.relay;
}

const QStringList& JsonTool::getRelayConfigKeyList()
{
	return m_relayConfigKeyList;
}

bool JsonTool::setRelayConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toInt(&convert);
		if (!convert)
		{
			setLastError(QString("%1必须为整数").arg(key));
			break;
		}

		if (!m_relayConfigObj.contains(key))
		{
			setLastError(QString("%1非法的键").arg(key));
			break;
		}
		m_relayConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getRelayConfigExplain()
{
	static QStringList explain = 
	{ 
		"地线",
		"自适应巡航控制电源",
		"用于检测电流",
		"用于检测电压",
		"用于图像转换",
		"用于紧急录制",
		"用于播放音乐",
		"运行TS亮",
		"结果NG亮",
		"结果OK亮"
	};
	return explain;
}

const QString JsonTool::getRelayConfigDefaultValue(const QString& key)
{
	QString result = "0";
	for (int i = 0; i < m_relayConfigKeyList.size(); i++)
	{
		if (m_relayConfigKeyList[i] == key)
		{
			result = m_relayConfigValueList.at(i);
			break;
		}
	}
	return result;
}

const QStringList& JsonTool::getUserConfigKeyList()
{
	return m_userConfigKeyList;
}

const QStringList& JsonTool::getUserConfigExplain()
{
	static QStringList explain = {"用户名","密码"};
	return explain;
}

const QString JsonTool::getUserConfigValue(const QString& key)
{
	return m_userConfigObj[key].toString();
}

const int JsonTool::getUserConfigCount()
{
	return m_userConfigObj.count();
}

bool JsonTool::setUserConfigValue(const QString& key, const QString& value)
{
	bool result = false;
	do 
	{
		if (!m_userConfigObj.contains(key))
		{
			setLastError(QString("非法的键值[%1]").arg(key));
			break;
		}
		m_userConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

bool JsonTool::getUserPrivileges()
{
	const QString&& userName = getUserConfigValue("用户名").toUpper();
	return (userName == "ROOT" || userName == "INVO");
}

const QString JsonTool::getUserConfigDefaultValue(const QString& key)
{
	QString result = "0";
	for (int i = 0; i < m_userConfigKeyList.size(); i++)
	{
		if (m_userConfigKeyList[i] == key)
		{
			result = m_userConfigValueList.at(i);
			break;
		}
	}
	return result;
}

const QString JsonTool::getRangeConfigValue(const QString& key)
{
	return m_rangeConfigObj[key].toString();
}

const int JsonTool::getRangeConfigCount()
{
	return m_rangeConfigObj.count();
}

const QStringList& JsonTool::getRangeConfigKeyList()
{
	return m_rangeConfigKeyList;
}

const RangeConfig& JsonTool::getParsedRangeConfig()
{
	return m_defConfig.range;
}

bool JsonTool::setRangeConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		auto split = value.split("~",QString::SkipEmptyParts);
		if (split.size() != 2)
		{
			setLastError(QString("%1格式错误,范围格式规则为:[0.0~10.0]").arg(key));
			break;
		}

		for (int i = 0; i < split.size(); i++)
		{
			split[i].toFloat(&convert);
			if (!convert)
			{
				setLastError(QString("%1中的数据,必须为数字").arg(key));
				break;
			}
		}

		if (!convert)
		{
			break;
		}

		if (!m_rangeConfigObj.contains(key))
		{
			setLastError(QString("%1非法的键").arg(key));
			break;
		}
		m_rangeConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getRangeConfigExplain()
{
	static QStringList explain = { "单位:MB(兆字节)","单位:MM(毫米)",
		"单位:MM(毫米)","单位:°(度)","单位:PX(像素)",
		"单位:A(安培)","单位:A(安培)" };
	return explain;
}

const QString JsonTool::getRangeConfigDefaultValue(const QString& key)
{
	QString result = "0";
	for (int i = 0; i < m_rangeConfigKeyList.size(); i++)
	{
		if (m_rangeConfigKeyList[i] == key)
		{
			result = m_rangeConfigValueList.at(i);
			break;
		}
	}
	return result;
}

const QString JsonTool::getThresholdConfigValue(const QString& key)
{
	return m_thresholdConfigObj[key].toString();
}

const int JsonTool::getThresholdConfigCount()
{
	return m_thresholdConfigObj.count();
}

const QStringList& JsonTool::getThresholdConfigKeyList()
{
	return m_thresholdConfigKeyList;
}

const ThresholdConfig& JsonTool::getParsedThresholdConfig()
{
	return m_defConfig.threshold;
}

bool JsonTool::setThresholdConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		float data = value.toFloat(&convert);
		if (!convert)
		{
			setLastError(QString("%1,必须为数字").arg(key));
			break;
		}

		if (key == "启动延时")
		{
			if (data <= 0.1000000001f)
			{
				setLastError(QString("%1,不可小于等于0").arg(key));
				break;
			}
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
	static QStringList explain = { "单位:MS(毫秒)","单位:A(安培)","单位:A(安培)" };
	return explain;
}

const QString JsonTool::getThresholdConfigDefaultValue(const QString& key)
{
	QString result = "0";
	for (int i = 0; i < m_thresholdConfigKeyList.size(); i++)
	{
		if (m_thresholdConfigKeyList[i] == key)
		{
			result = m_thresholdConfigValueList.at(i);
			break;
		}
	}
	return result;
}

const ImageConfig& JsonTool::getParsedImageConfig()
{
	return m_defConfig.image;
}

const int JsonTool::getImageConfigCount()
{
	return m_imageConfigObj.count();
}

const QStringList JsonTool::getParentImageKeyList()
{
	return m_parentImageKeyList;
}

void JsonTool::setChildImageKeyListSubscript(const int& subscript)
{
	m_childImageSubscript = subscript;
}

const QStringList JsonTool::getChildImageKeyList(const int& id)
{
	return m_childImageKeyList[id];
}

const QStringList& JsonTool::getChildImageKeyList()
{
	return m_childImageKeyList[m_childImageSubscript];
}

const QString JsonTool::getImageConfigValue(const QString& parentKey, const QString& childKey)
{
	return m_imageConfigObj.value(parentKey).toObject().value(childKey).toString();
}

bool JsonTool::setImageConfigValue(const QString& parentKey, const QString& childKey, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		if (childKey != "颜色")
		{
			value.toInt(&convert);
			if (!convert)
			{
				setLastError(QString("%1,%2,必须为整数").arg(parentKey, childKey));
				break;
			}
		}

		if (!m_imageConfigObj.contains(parentKey))
		{
			setLastError(QString("%1非法的键").arg(parentKey));
			break;
		}

		QJsonObject object = m_imageConfigObj[parentKey].toObject();
		if (!object.contains(childKey))
		{
			setLastError(QString("%1非法的键").arg(childKey));
			break;
		}
		object[childKey] = value;
		m_imageConfigObj.insert(parentKey, object);
		result = true;
	} while (false);
	return result;
}

const QStringList JsonTool::getImageConfigExplain(const int& i)
{
	static QStringList explain0 = { "1启用,0禁用","1启用,0禁用","1启用,0禁用","1启用,0禁用" };
	static QStringList explain1 = { "判断语法,!=黑色(不等于黑色),==黑色(等于黑色)",
		"三原色:Red(红色)","三原色:Green(绿色)","三原色:Blue(蓝色)","单位:PX(像素)",
		"单位:MM(毫米)","单位:MM(毫米)","单位:MM(毫米)","单位:MM(毫米)" };

	if (i == getImageConfigCount() - 1)
	{
		return explain0;
	}
	return explain1;
}

const QStringList& JsonTool::getImageConfigExplain()
{
	static QStringList explain0 = { "1启用,0禁用","1启用,0禁用","1启用,0禁用","1启用,0禁用" };
	static QStringList explain1 = { "判断语法,!=黑色(不等于黑色),==黑色(等于黑色)",
		"三原色:Red(红色)","三原色:Green(绿色)","三原色:Blue(蓝色)","单位:PX(像素)",
			"单位:MM(毫米)","单位:MM(毫米)","单位:MM(毫米)","单位:MM(毫米)" };

	if (m_childImageSubscript == getImageConfigCount() - 1)
	{
		return explain0;
	}
	return explain1;
}

const int JsonTool::getEnableConfigCount()
{
	return m_enableConfigKeyList.count();
}

const QStringList& JsonTool::getEnableConfigKeyList()
{
	return m_enableConfigKeyList;
}

const QStringList JsonTool::getEnableConfigValueList()
{
	return m_enableConfigValueList;
}

const QString JsonTool::getEnableConfigValue(const QString& key)
{
	return m_enableConfigObj[key].toString();
}

bool JsonTool::setEnableConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toInt(&convert);
		if (!convert)
		{
			setLastError(QString("%1,必须为整数").arg(key));
			break;
		}

		if (value != "0" && value != "1")
		{
			setLastError("该值只能为0或1");
			break;
		}

		if (!m_enableConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}
		m_enableConfigObj[key] = value; 
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getEnableConfigExplain()
{
	static QStringList explain = 
	{ 
		"0禁用,1启用",
		"0禁用,1启用", 
		"0禁用,1启用",
		"0禁用,1启用", 
		"0禁用,1启用",
		"0禁用,1启用",
		"0禁用,1启用",
		"0禁用,1启用",
		"0禁用,1启用",
		"0禁用,1启用",
		"0禁用,1启用" 
	};
	return explain;
}

const QString JsonTool::getEnableConfigDefaultValue(const QString& key)
{
	QString result = "0";
	for (int i = 0; i < m_enableConfigKeyList.size(); i++)
	{
		if (m_enableConfigKeyList[i] == key)
		{
			result = m_enableConfigValueList.at(i);
			break;
		}
	}
	return result;
}

DefConfig* JsonTool::getParsedDefConfig()
{
	return &m_defConfig;
}

const int JsonTool::getVoltageConfigCount()
{
	return m_voltageConfigObj.count();
}

const QStringList& JsonTool::getChildVoltageConfigKeyList()
{
	static QStringList keys = { "上限","下限","继电器IO" };
	return keys;
}

const QStringList& JsonTool::getChildVoltageConfigValueList()
{
	static QStringList explain = { "1.8", "1.0", "1" };
	return explain;
}

const QStringList JsonTool::getParentVoltageConfigKeyList()
{
	return m_voltageConfigObj.keys();
}

const QString JsonTool::getVoltageConfigValue(const QString& parentKey, const QString& childKey)
{
	return m_voltageConfigObj.value(parentKey).toObject().value(childKey).toString();
}

void JsonTool::setVoltageConfigKey(const QString& oldParentKey, const QString& newParentKey)
{
	do 
	{
		if (!m_voltageConfigObj.contains(oldParentKey))
		{
			break;
		}

		QJsonObject object = m_voltageConfigObj[oldParentKey].toObject();
		m_voltageConfigObj.remove(oldParentKey);
		m_voltageConfigObj.insert(newParentKey, object);
	} while (false);
	return;
}

bool JsonTool::setVoltageConfigValue(const QString& parentKey, const QString& childKey, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		if (childKey != "继电器IO")
		{
			value.toFloat(&convert);
			if (!convert)
			{
				setLastError(QString("%1,%2,必须为数字").arg(parentKey, childKey));
				break;
			}
		}
		else
		{
			value.toInt(&convert);
			if (!convert)
			{
				setLastError(QString("%1,%2,必须为整数").arg(parentKey, childKey));
				break;
			}
		}

		if (!m_voltageConfigObj.contains(parentKey))
		{
			setLastError(QString("%1,非法的键").arg(parentKey));
			break;
		}

		QJsonObject object = m_voltageConfigObj[parentKey].toObject();
		if (!object.contains(childKey))
		{
			setLastError(QString("%1,非法的键").arg(childKey));
			break;
		}
		object[childKey] = value;
		m_voltageConfigObj.insert(parentKey, object);
		result = true;
	} while (false);
	return result;
}

QJsonObject& JsonTool::getVoltageConfigObj()
{
	return m_voltageConfigObj;
}

const QStringList& JsonTool::getVoltageConfigExplain()
{
	static QStringList explain = { "单位:V(伏)","单位:V(伏)","继电器接口编号" };
	return explain;
}

const int JsonTool::getKeyVolConfigCount()
{
	return m_keyVolConfigObj.count();
}

const QStringList& JsonTool::getKeyVolConfigKeyList()
{
	static QStringList keys = { "高电平上限","高电平下限","低电平上限","低电平下限" };
	return keys;
}

const QStringList JsonTool::getKeyVolConfigValueList()
{
	return { "14.0","8.0","1.0","0.0" };
}

const QString JsonTool::getKeyVolConfigValue(const QString& key)
{
	return m_keyVolConfigObj.value(key).toString();
}

bool JsonTool::setKeyVolConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toFloat(&convert);
		if (!convert)
		{
			setLastError(QString("%1,必须为数字").arg(key));
			break;
		}

		if (!m_keyVolConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}
		m_keyVolConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getKeyVolConfigExplain()
{
	static QStringList explain = { "单位:V(伏)","单位:V(伏)","单位:V(伏)","单位:V(伏)" };
	return explain;
}

const int JsonTool::getCurrentConfigCount()
{
	return m_currentConfigObj.count();
}

const QStringList JsonTool::getParentCurrentConfigKeyList()
{
	return m_currentConfigObj.keys();
}

const QStringList& JsonTool::getChildCurrentConfigKeyList()
{
	static QStringList keys = { "上限","下限","电压" };
	return keys;
}

const QStringList& JsonTool::getChildCurrentConfigValueList()
{
	static QStringList keys = { "0.0","0.0","0.0" };
	return keys;
}

const QStringList JsonTool::getChildCurrentConfigValueList(const int& i)
{
	QStringList list_[2]{ { "1.0","0.3","12.0" } ,{"1.2","0.4","16.0"} };
	return list_[i > 1 ? 1 : i];
}

const QString JsonTool::getCurrentConfigValue(const QString& parentKey, const QString& childKey)
{
	return m_currentConfigObj.value(parentKey).toObject().value(childKey).toString();
}

void JsonTool::setCurrentConfigKey(const QString& oldParentKey, const QString& newParentKey)
{
	do
	{
		if (!m_currentConfigObj.contains(oldParentKey))
		{
			break;
		}
		QJsonObject object = m_currentConfigObj[oldParentKey].toObject();
		m_currentConfigObj.remove(oldParentKey);
		m_currentConfigObj.insert(newParentKey, object);
	} while (false);
	return;
}

bool JsonTool::setCurrentConfigValue(const QString& parentKey, const QString& childKey, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toFloat(&convert);
		if (!convert)
		{
			setLastError(QString("%1,%2必须为数字").arg(parentKey, childKey));
			break;
		}

		if (!m_currentConfigObj.contains(parentKey))
		{
			setLastError(QString("%1,非法的键").arg(parentKey));
			break;
		}

		QJsonObject object = m_currentConfigObj[parentKey].toObject();
		if (!object.contains(childKey))
		{
			setLastError(QString("%1,非法的键").arg(childKey));
			break;
		}
		object[childKey] = value;
		m_currentConfigObj.insert(parentKey, object);
		result = true;
	} while (false);
	return result;
}

QJsonObject& JsonTool::getCurrentConfigObj()
{
	return m_currentConfigObj;
}

const QStringList& JsonTool::getCurrentConfigExplain()
{
	static QStringList explain = { "单位:A(安培)", "单位:A(安培)", "单位:V(伏)" };
	return explain;
}

const int JsonTool::getStaticConfigCount()
{
	return m_staticConfigObj.count();
}

const QStringList& JsonTool::getStaticConfigKeyList()
{
	static QStringList keys = { "上限","下限" };
	return keys;
}

const QStringList JsonTool::getStaticConfigValueList()
{
	return { "50.0","10.0" };
}

const QString JsonTool::getStaticConfigValue(const QString& key)
{
	return m_staticConfigObj.value(key).toString();
}

bool JsonTool::setStaticConfigValue(const QString& key, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		value.toFloat(&convert);
		if (!convert)
		{
			setLastError(QString("%1,必须为数字").arg(key));
			break;
		}

		if (!m_staticConfigObj.contains(key))
		{
			setLastError(QString("%1,非法的键").arg(key));
			break;
		}
		m_staticConfigObj[key] = value;
		result = true;
	} while (false);
	return result;
}

const QStringList& JsonTool::getStaticConfigExplain()
{
	static QStringList explain = { "单位:μA(微安)","单位:μA(微安)" };
	return explain;
}

const QStringList JsonTool::getParentResConfigKeyList()
{
	return m_resConfigObj.keys();
}

const QStringList& JsonTool::getChildResConfigKeyList()
{
	static QStringList keys = { "上限","下限","继电器IO" };
	return keys;
}

const QStringList& JsonTool::getChildResConfigValueList()
{
	static QStringList keys = { "8000","5000","5" };
	return keys;
}

const int JsonTool::getResConfigCount()
{
	return m_resConfigObj.count();
}

const QString JsonTool::getResConfigValue(const QString& parentKey, const QString& childKey)
{
	return m_resConfigObj.value(parentKey).toObject().value(childKey).toString();
}

void JsonTool::setResConfigKey(const QString& oldParentKey, const QString& newParentKey)
{
	do 
	{
		if (!m_resConfigObj.contains(oldParentKey))
		{
			break;
		}

		QJsonObject object = m_resConfigObj[oldParentKey].toObject();
		m_resConfigObj.remove(oldParentKey);
		m_resConfigObj.insert(newParentKey, object);
	} while (false);
	return;
}

bool JsonTool::setResConfigValue(const QString& parentKey, const QString& childKey, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		if (childKey != "继电器IO")
		{
			value.toInt(&convert);
			if (!convert)
			{
				setLastError(QString("%1,%2,必须为整数").arg(parentKey, childKey));
				break;
			}
		}
		else
		{
			value.toFloat(&convert);
			if (!convert)
			{
				setLastError(QString("%1,%2,必须为整数").arg(parentKey, childKey));
				break;
			}
		}

		if (!m_resConfigObj.contains(parentKey))
		{
			setLastError(QString("%1,非法的键").arg(parentKey));
			break;
		}

		QJsonObject object = m_resConfigObj[parentKey].toObject();
		if (!object.contains(childKey))
		{
			setLastError(QString("%1,非法的键").arg(childKey));
			break;
		}
		object[childKey] = value;
		m_resConfigObj.insert(parentKey, object);
		result = true;
	} while (false);
	return result;
}

QJsonObject& JsonTool::getResConfigObj()
{
	return m_resConfigObj;
}

const QStringList& JsonTool::getResConfigExplain()
{
	static QStringList explain = { "单位:Ω(欧姆)","单位:Ω(欧姆)","继电器接口编号" };
	return explain;
}

HwdConfig* JsonTool::getParsedHwdConfig()
{
	return &m_hwdConfig;
}

const int JsonTool::getVerConfigCount()
{
	return m_verConfigObj.count();
}

const QStringList JsonTool::getParentVerConfigKeyList()
{
	return m_verConfigObj.keys();
}

const QStringList& JsonTool::getChildVerConfigKeyList()
{
	static QStringList keys = { "DID","编码","值" };
	return keys;
}

const QStringList& JsonTool::getChildVerConfigValueList()
{
	static QStringList keys = { "0xFFFF","ASCII","00000000" };
	return keys;
}

const QString JsonTool::getVerConfigValue(const QString& parentKey, const QString& childKey)
{
	return m_verConfigObj.value(parentKey).toObject().value(childKey).toString();
}

void JsonTool::setVerConfigKey(const QString& oldParentKey, const QString& newParentKey)
{
	do 
	{
		if (!m_verConfigObj.contains(oldParentKey))
		{
			break;
		}

		QJsonObject object = m_verConfigObj[oldParentKey].toObject();
		m_verConfigObj.remove(oldParentKey);
		m_verConfigObj.insert(newParentKey, object);
	} while (false);
	return;
}

bool JsonTool::setVerConfigValue(const QString& parentKey, const QString& childKey, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		QString newValue = value;

		if (childKey == "DID")
		{
			if (!(newValue.contains("0x") || newValue.contains("0X")))
			{
				if (newValue.length() == 4)
				{
					newValue.insert(0, "0x");
				}
				else
				{
					setLastError(QString("%1,%2格式错误,参照格式0xF16C").arg(parentKey, childKey));
					break;
				}
			}
			else
			{
				if (!(newValue.length() == 6))
				{
					setLastError(QString("%1,%2格式错误,参照格式0xF16C").arg(parentKey, childKey));
					break;
				}
			}

			newValue.toInt(&convert, 16);
			if (!convert)
			{
				setLastError(QString("%1,%2格式错误,参照格式0xF16C").arg(parentKey, childKey));
				break;
			}
		}
		else if (childKey == "编码")
		{
			QStringList data = { "ASCII","ASCR4","INT","USN","BIN","BCD","U08","ASCBCD44" };
			if (!data.contains(newValue))
			{
				setLastError(QString("%1,%2不支持的格式").arg(childKey, newValue));
				break;
			}
		}

		if (!m_verConfigObj.contains(parentKey))
		{
			setLastError(QString("%1,非法的键").arg(parentKey));
			break;
		}

		QJsonObject object = m_verConfigObj[parentKey].toObject();
		if (!object.contains(childKey))
		{
			setLastError(QString("%1,非法的键").arg(childKey));
			break;
		}
		object[childKey] = newValue;
		m_verConfigObj.insert(parentKey, object);
		result = true;
	} while (false);
	return result;
}

QJsonObject& JsonTool::getVerConfigObj()
{
	return m_verConfigObj;
}

const QStringList& JsonTool::getVerConfigExplain()
{
	static QStringList explain = 
	{ 
		"数据标识符",
		"支持编码[ASCII ASCR4 INT USN BIN BCD U08 ASCBCD44]",
		"标识符数据" 
	};
	return explain;
}

const int JsonTool::getDtcConfigCount()
{
	return m_dtcConfigObj.count();
}

const QStringList JsonTool::getParentDtcConfigKeyList()
{
	return m_dtcConfigObj.keys();
}

const QStringList& JsonTool::getChildDtcConfigKeyList()
{
	static QStringList keys = { "DTC","忽略" };
	return keys;
}

const QStringList& JsonTool::getChildDtcConfigValueList()
{
	static QStringList keys = { "U100000","0" };
	return keys;
}

const QString JsonTool::getDtcConfigValue(const QString& parentKey, const QString& childKey)
{
	return m_dtcConfigObj.value(parentKey).toObject().value(childKey).toString();
}

void JsonTool::setDtcConfigKey(const QString& oldParentKey, const QString& newParentKey)
{
	do 
	{
		if (!m_dtcConfigObj.contains(oldParentKey))
		{
			break;
		}

		QJsonObject object = m_dtcConfigObj[oldParentKey].toObject();
		m_dtcConfigObj.remove(oldParentKey);
		m_dtcConfigObj.insert(newParentKey, object);
	} while (false);
	return;
}

bool JsonTool::setDtcConfigValue(const QString& parentKey, const QString& childKey, const QString& value)
{
	bool result = false, convert = false;
	do 
	{
		if (childKey == "DTC")
		{
			if (dtcCategoryConvert(value).isEmpty())
			{
				setLastError("DTC不符合编码规则");
				break;
			}
		}
		else
		{
			value.toInt(&convert);
			if (!convert)
			{
				setLastError("忽略必须为整数");
				break;
			}
		}

		if (!m_dtcConfigObj.contains(parentKey))
		{
			setLastError(QString("%1,非法的键").arg(parentKey));
			break;
		}

		QJsonObject object = m_dtcConfigObj[parentKey].toObject();
		if (!object.contains(childKey))
		{
			setLastError(QString("%1,非法的键").arg(childKey));
			break;
		}
		object[childKey] = value;
		m_dtcConfigObj.insert(parentKey, object);
		result = true;
	} while (false);
	return result;
}

QJsonObject& JsonTool::getDtcConfigObj()
{
	return m_dtcConfigObj;
}

const QStringList& JsonTool::getDtcConfigExplain()
{
	static QStringList explain =  { "诊断故障码","1启用,0禁用" };
	return explain;
}

UdsConfig* JsonTool::getParsedUdsConfig()
{
	return &m_udsConfig;
}

const QString JsonTool::getOthConfigValue(const QString& key)
{
	return m_othConfigObj.value(key).toString();
}

const int JsonTool::getOthConfigCount()
{
	return m_othConfigObj.count();
}

//void JsonTool::setSkipItem(const SkipItem& item, bool skip)
//{
//	if (item > 0xff)
//		return;
//	m_skipItemVec[item] = skip;
//}

bool JsonTool::getSkipItem(const SkipItem& item)
{
	bool result = false;
	switch (item)
	{
	case SkipItem::SI_JC:
		result = m_defConfig.enable.codeJudge;
		break;
	case SkipItem::SI_QS:
		result = m_defConfig.enable.queryStation;
		break;
	case SkipItem::SI_SN:
		result = m_defConfig.enable.snReadWrite;
		break;
	case SkipItem::SI_DATE:
		result = m_defConfig.enable.dateReadWrite;
		break;
	default:
		break;
	}
	return result;
}

//void JsonTool::deleteSkipSymbol(QString& code)
//{
//	QString temp = code;
//	for (int i = 0; i < temp.length();)
//	{
//		bool exist = false;
//		if (temp.mid(i * 2, 2) == SKIP_QS_SYMBOL)
//		{
//			setSkipItem(SI_QS, true);
//			exist = true;
//		}
//
//		if (temp.mid(i * 2, 2) == SKIP_SN_SYMBOL)
//		{
//			setSkipItem(SI_SN, true);
//			exist = true;
//		}
//
//		if (temp.mid(i * 2, 2) == SKIP_DATE_SYMBOL)
//		{
//			setSkipItem(SI_DATE, true);
//			exist = true;
//		}
//
//		if (exist)
//		{
//			i = 0;
//			temp = temp.remove(temp.mid(i * 2, 2));
//		}
//		else
//			i++;
//	}
//	code = temp;
//}

//bool JsonTool::getSkipCode()
//{
//	return m_defConfig.device.codeJudge == "NULL" &&
//		m_defConfig.device.codeLength.toInt() == 0;
//}

