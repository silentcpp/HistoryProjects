#include "Types.h"
#include "Detection.h"

/************************************************************************/
/* Misc realize                                                         */
/************************************************************************/

bool Misc::isExistKitsPath()
{
	QString pathEnv = QProcessEnvironment::systemEnvironment().value("Path");
	QString kitsPath = MY_KITS_PATH;
	kitsPath = kitsPath.left(kitsPath.length() - 1);
	return pathEnv.contains(kitsPath);
}

bool Misc::writeRunError(const QString& error)
{
	bool result = false;
	do
	{
		QString path = QString(".\\%1\\RUN\\").arg(GET_LOG_DIR());
		if (!Misc::makePath(path))
		{
			break;
		}

		QFile file(path.append(Misc::getCurrentDate(true)).append(".run"));
		if (!file.open(QFile::WriteOnly | QFile::Append | QFile::Text))
		{
			break;
		}
		QTextStream stream(&file);
		stream << Misc::getCurrentTime() << " " << (g_code.isEmpty() ? "未知" : g_code) << " " << error << endl;
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Misc::cvImageToQtImage(IplImage* cv, QImage* qt)
{
	bool result = false;
	do
	{
		if (!cv || !qt)
			break;

		cvCvtColor(cv, cv, CV_BGR2RGB);
		*qt = QImage((uchar*)cv->imageData, cv->width, cv->height, cv->widthStep, QImage::Format_RGB888);
		result = true;
	} while (false);
	return result;
}

bool Misc::cvImageToQtImage(const Mat& mat, QImage& image)
{
	if (mat.empty())
	{
		image = QImage();
		return false;
	}

	cv::Mat temp;
	cv::cvtColor(mat, temp, CV_BGR2RGB);

	image = QImage(temp.data, temp.cols, temp.rows, QImage::Format_RGB888).
		copy(0, 0, temp.cols, temp.rows);

	return true;
}

const QString Misc::getFileNameByUrl(const QString& url)
{
	return url.mid(url.lastIndexOf("/") + 1);
}

const QString Misc::getFileNameByPath(const QString& path)
{
	return path.mid(path.lastIndexOf('\\') + 1);
}

const QString Misc::getCurrentFileName()
{
	QString fileName = "";
	do
	{
		char buffer[MAX_PATH] = { 0 };
		if (!GetModuleFileNameA(NULL, buffer, MAX_PATH))
		{
			break;
		}
		QString fullName(G_TO_Q_STR(buffer));
		fileName = fullName.mid(fullName.lastIndexOf('\\') + 1);
	} while (false);
	return fileName;
}

const QString Misc::getCurrentDir()
{
	char buffer[BUFF_SIZE] = { 0 };
	GetCurrentDirectoryA(BUFF_SIZE, buffer);
	return G_TO_Q_STR(buffer);
}

bool Misc::makePath(const QString& path)
{
	bool result = false;
	do
	{
		if (!QDir(path).exists())
		{
			QDir dir;
			if (!dir.mkpath(path))
			{
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

const QString Misc::_getAppVersion()
{
	QString result = "0.0.0";
	char* nameBuffer = nullptr;
	do
	{
		char fullName[MAX_PATH] = { 0 };
		if (!GetModuleFileNameA(NULL, fullName, MAX_PATH))
		{
			break;
		}

		quint32 nameLen = GetFileVersionInfoSizeA(fullName, 0);
		if (!nameLen)
		{
			break;
		}

		nameBuffer = new(std::nothrow) char[nameLen + 1];
		if (!nameBuffer)
		{
			break;
		}

		bool success = GetFileVersionInfoA(fullName, 0, nameLen, nameBuffer);
		if (!success)
		{
			break;
		}

		struct LanguageCodePage
		{
			WORD language;
			WORD codePage;
		} *translate;

		quint32 queryLen = 0;
		success = VerQueryValue(nameBuffer, (TEXT("\\VarFileInfo\\Translation")), (LPVOID*)&translate, &queryLen);
		if (!success)
		{
			break;
		}
		QString str1, str2;
		str1.setNum(translate->language, 16);
		str2.setNum(translate->codePage, 16);
		str1 = "000" + str1;
		str2 = "000" + str2;
		QString verPath = "\\StringFileInfo\\" + str1.right(4) + str2.right(4) + "\\FileVersion";
		void* queryBuffer = nullptr;
		success = VerQueryValue(nameBuffer, (verPath.toStdWString().c_str()), &queryBuffer, &queryLen);
		if (!success)
		{
			break;
		}
		result = QString::fromUtf16((const unsigned short int*)queryBuffer);
	} while (false);
	SAFE_DELETE_A(nameBuffer);
	return result;
}

const QString Misc::getAppVersion()
{
	static QString version = _getAppVersion();
	return version;
}

void Misc::setAppAppendName(const QString& name)
{
	Misc::Var::appendName = name;
}

const QString Misc::getAppAppendName()
{
	return Misc::Var::appendName;
}

bool Misc::renameAppByVersion(QWidget* widget)
{
	bool result = false;
	do
	{
		DeviceConfig device = JsonTool::getInstance()->getParsedDeviceConfig();
		const QString&& user = JsonTool::getInstance()->getUserConfigValue("用户名");
		if (!Misc::Var::appendName.isEmpty())
		{
			device.modelName.append(Misc::Var::appendName);
		}

		QString title, newName;
		title = newName = QString("%1%2[%3]").arg(device.modelName,
			Dt::Base::getDetectionName(),
			Misc::getAppVersion());

		title = QString("%1[权限:%3]").arg(title, user);

		widget->setWindowTitle(title);

		QString oldName(getCurrentFileName());
		newName.append(".exe");
		if (oldName != newName)
		{
			//QFile::rename(oldName, newName);
			MoveFileEx(Q_TO_WC_STR(oldName), Q_TO_WC_STR(newName), MOVEFILE_REPLACE_EXISTING);
		}
		result = true;
	} while (false);
	return result;
}

bool Misc::startApp(const QString& name, int show, bool absolutely)
{
	bool result = false;
	do
	{
		/*判断是否有附加参数*/
		QString cmdLine;
		if (name.indexOf(" ") != -1)
		{
			cmdLine = name.mid(name.indexOf(" ") + 1);
		}

		QString destProgram = "";
		if (absolutely)
			destProgram = name;
		else
			destProgram = getCurrentDir() + '\\' + name;

		QString destDirectory = destProgram.mid(0, destProgram.lastIndexOf('\\'));

		HINSTANCE hInstance = ShellExecuteW(NULL, L"open", Q_TO_WC_STR(destProgram),
			cmdLine.isEmpty() ? NULL : Q_TO_WC_STR(cmdLine), Q_TO_WC_STR(destDirectory), show);
		if ((int)hInstance <= 32)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Misc::finishApp(const QString& name)
{
	bool result = false;
	do
	{
		QProcess process;
		process.start(QString("cmd.exe /c tasklist | findstr \"%1\"").arg(name));
		process.waitForFinished();

		QString output(process.readAllStandardOutput().data());

		if (output.indexOf(name) == -1)
		{
			break;
		}
		QProcess::execute("cmd.exe", { "/c","taskkill","/im",name,"/f" });
		result = true;
	} while (false);
	return result;
}

const SYSTEMTIME Misc::getLocalTime()
{
	SYSTEMTIME sysTime;
	::GetLocalTime(&sysTime);
	return sysTime;
}

const QString Misc::getCurrentTime(bool fileFormat)
{
	return fileFormat ? QTime::currentTime().toString("hh:mm:ss").remove(':')
		: QTime::currentTime().toString("hh:mm:ss.zzz");
}

const QString Misc::getCurrentDate(bool fileFormat)
{
	return fileFormat ? QDate::currentDate().toString("yyyy-MM-dd").remove('-')
		: QDate::currentDate().toString("yyyy-MM-dd");
}

const QString Misc::getCurrentDateTime(bool fileFormat)
{
	QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	if (fileFormat)
	{
		return dateTime.remove('-').remove(':').remove('.');
	}
	return dateTime;
}

void Misc::getFileListByPath(const QString& path, QStringList& fileList)
{
	QString p;
	WIN32_FIND_DATAW wfd;
	HANDLE handle;
	if ((handle = FindFirstFileW(Q_TO_WC_STR((p = path).append("\\*")), &wfd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (wcscmp(wfd.cFileName, L".") != 0 && wcscmp(wfd.cFileName, L"..") != 0)
				{
					getFileListByPath((p = path).append("\\").append(WC_TO_Q_STR(wfd.cFileName)), fileList);
				}
			}
			else
			{
				fileList.push_back((p = path).append("\\").append(WC_TO_Q_STR(wfd.cFileName)));
			}
		} while (FindNextFileW(handle, &wfd));
		FindClose(handle);
	}
	return;
}

const QStringList Misc::getFileListBySuffixName(const QString& path, const QStringList& suffix)
{
	QStringList src, dst;
	getFileListByPath(path, src);
	int pos;
	for (auto& x : src)
	{
		for (int i = 0; i < suffix.size(); ++i)
		{
			if ((pos = x.lastIndexOf(".")) != -1 && x.mid(pos).toLower() == suffix[i])
			{
				dst.push_back(x);
			}
		}
	}
	return dst;
}

const char* Misc::wideCharToMultiByte(const wchar_t* wide)
{
	char* buffer = nullptr;
	do
	{
		int size = WideCharToMultiByte(CP_OEMCP, 0, wide, -1, NULL, 0, NULL, FALSE);
		if (size <= 0)
		{
			break;
		}

		buffer = NO_THROW_NEW char[size];
		if (!buffer) break;
		memset(buffer, 0x00, size);
		if (WideCharToMultiByte(CP_OEMCP, 0, wide, -1, buffer, size, NULL, FALSE) <= 0)
		{
			SAFE_DELETE_A(buffer);
		}
	} while (false);
	return buffer;
}

const char* Misc::qstringToMultiByte(const QString& str)
{
	wchar_t* buffer = nullptr;
	do
	{
		buffer = NO_THROW_NEW wchar_t[str.length() + 1];
		if (!buffer) break;
		memset(buffer, 0x00, str.length() + 1);
		int size = str.toWCharArray(buffer);
		buffer[size] = '\0';
	} while (false);
	const char* result = wideCharToMultiByte(buffer);
	SAFE_DELETE_A(buffer);
	return result;
}

bool Misc::createShortcut()
{
	QString typeName = GET_TYPE_NAME();
	if (typeName == "未知")
		return false;

	QString fileName = typeName + Dt::Base::getDetectionName() + 
		QString("检测[") + getAppVersion() + QString("].lnk");
	QString linkPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "\\" + fileName;

	if (QDir(linkPath).exists())
		return true;

	wchar_t temp[512] = { 0 };
	GetModuleFileNameW(NULL, temp, sizeof(temp));
	QString fileFullPath = WC_TO_Q_STR(temp, sizeof(temp));
	QFile app(fileFullPath);
	return app.link(linkPath);
}

bool Misc::ping(const QString& address, int times)
{
	QProcess process;
	process.start(QString("ping %1 -n %2").arg(address).arg(times));
	process.waitForFinished();
	return process.exitCode() == 0;
}

bool Misc::ipLive(const QString& address, int port, int timeout)
{
	QTcpSocket tcp;
	tcp.connectToHost(address, port);
	return tcp.waitForConnected(timeout);
}

bool Misc::execute(const QString& cmd, const QStringList& arguments)
{
	return (arguments.size() ? QProcess::execute(cmd,arguments):
		QProcess::execute(cmd)) == 0;
}

bool Misc::setIpAddress(int netCardId, QString ip, QString mask, QString gateway)
{
	bool result = false;
	do
	{
		if (netCardId <= 0)
		{
			break;
		}

		QStringList adapterNameList, descriptionList, ipList, maskList, gatewayList;

		ULONG adapterSize = sizeof(IP_ADAPTER_INFO);
		PIP_ADAPTER_INFO adapterInfo = (PIP_ADAPTER_INFO)new char[adapterSize];

		if (GetAdaptersInfo(adapterInfo, &adapterSize) == ERROR_BUFFER_OVERFLOW)
		{
			delete adapterInfo;
			adapterInfo = (PIP_ADAPTER_INFO)new char[adapterSize];
		}

		if (GetAdaptersInfo(adapterInfo, &adapterSize) != ERROR_SUCCESS)
		{
			break;
		}
		do
		{
			if (adapterInfo->Type == MIB_IF_TYPE_ETHERNET)
			{
				if (strstr(adapterInfo->Description, "PCI"))
				{
					auto addressPtr = &adapterInfo->IpAddressList;
					while (addressPtr)
					{
						ipList.append(addressPtr->IpAddress.String);
						maskList.append(addressPtr->IpMask.String);
						auto gatewayPtr = &adapterInfo->GatewayList;
						while (gatewayPtr)
						{
							gatewayList.append(gatewayPtr->IpAddress.String);
							gatewayPtr = gatewayPtr->Next;
						}
						addressPtr = addressPtr->Next;
					}

					adapterNameList.append(adapterInfo->AdapterName);
					descriptionList.append(adapterInfo->Description);
				}
			}
			adapterInfo = adapterInfo->Next;
		} while (adapterInfo);
		delete[] adapterInfo;

		if (adapterNameList.size() <= 0)
		{
			break;
		}

		//if (netCardId > adapterNameList.size())
		//{
		//	break;
		//}

		int index = 1;
		if (netCardId != 1)
		{
			index = 0;
			for (auto x : descriptionList)
			{
				if (x.contains(Q_SPRINTF("#%d", netCardId)))
				{
					break;
				}
				index++;
			}
		}

		if (ipList.at(index - 1) == ip &&
			maskList.at(index - 1) == mask &&
			gatewayList.at(index - 1) == gateway)
		{
			result = true;
			break;
		}

		QString subKey = QString("SYSTEM\\ControlSet001\\Control\\Network\\"
			"{4D36E972-E325-11CE-BFC1-08002BE10318}\\%1\\Connection")
			.arg(adapterNameList.at(index));

		HKEY key = nullptr;
		LSTATUS status = RegOpenKeyExW(HKEY_LOCAL_MACHINE, Q_TO_WC_STR(subKey), 0,
			KEY_READ, &key);

		if (status != ERROR_SUCCESS)
		{
			break;
		}

		wchar_t data[512] = { 0 };
		DWORD size = 512;
		status = RegQueryValueExW(key, L"Name", 0, 0, (LPBYTE)data, &size);
		if (status != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			break;
		}
		RegCloseKey(key);

		QString cmd = QString("netsh interface ip set address name=\"%1\" "
			"source=static %2 %3 %4").arg(WC_TO_Q_STR(data)).arg(ip, mask, gateway);

		if (!Misc::execute(cmd))
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

/*
* LoadQtlibrary Class Realize
*/
class LoadQtLibrary : public QObject {
public:
	inline LoadQtLibrary(QObject* parent = nullptr)
	{
		if (Misc::isExistKitsPath())
		{
			QApplication::addLibraryPath(m_kitPath + "plugins");
		}
	}
	inline ~LoadQtLibrary() {}
private:
	QString m_kitPath = MY_KITS_PATH;
}_;