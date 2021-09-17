#include "Utility.h"
#include <Windows.h>
#include <wininet.h>
#include <process.h>

#pragma comment(lib,"version.lib")
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"wininet.lib")

using namespace Utility;

class LoadQtLibrary : public QObject {
public:
	inline LoadQtLibrary(QObject* parent = nullptr)
	{
		if (existKitsPath())
		{
			QApplication::addLibraryPath(m_kitPath + "plugins");
		}
	}

	inline bool existKitsPath()
	{
		QString pathEnv = QProcessEnvironment::systemEnvironment().value("Path");
		QString kitsPath = m_kitPath;
		kitsPath = kitsPath.left(kitsPath.length() - 1);
		return pathEnv.contains(kitsPath);
	}
private:
	QString m_kitPath = "C:\\Windows\\MyKits\\";
}_;

void Utility::setDebugInfo(bool enable)
{
	Var::debugInfo = enable;
}

void Utility::setLastError(const QString& error)
{
	Var::lastError = error;
}

const QString& Utility::getLastError()
{
	return Var::lastError;
}

QString Utility::getFileNameByUrl(const QString& url)
{
	return url.mid(url.lastIndexOf("/") + 1);
}

QString Utility::getFileNameByPath(const QString& path)
{
	return path.mid(path.lastIndexOf('\\') + 1);
}

QString Utility::getCurrentFileName()
{
	QString fileName = "";
	do
	{
		char buffer[MAX_PATH] = { 0 };
		if (!GetModuleFileNameA(NULL, buffer, MAX_PATH))
		{
			setLastError("获取文件路径失败");
			break;
		}
		QString fullName(G_TO_Q_STR(buffer));
		fileName = fullName.mid(fullName.lastIndexOf('\\') + 1);
	} while (false);
	return fileName;
}

QString Utility::getCurrentDir()
{
	char buffer[BUFF_SIZE] = { 0 };
	GetCurrentDirectoryA(BUFF_SIZE, buffer);
	return G_TO_Q_STR(buffer);
}

bool Utility::makePath(const QString& path)
{
	bool result = false;
	do
	{
		if (!QDir(path).exists())
		{
			QDir dir;
			if (!dir.mkpath(path))
			{
				setLastError("创建路径失败");
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

bool Utility::existPath(const QString& path)
{
	return QDir(path).exists();
}

bool Utility::makeDir(const QString& dir)
{
	bool result = false;
	do
	{
		if (!QDir(dir).exists())
		{
			if (!QDir().mkdir(dir))
			{
				setLastError("创建目录失败");
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

bool Utility::existDir(const QString& dir)
{
	return QDir(dir).exists();
}

QString Utility::_getAppVersion()
{
	QString result = "0.0.0";
	char* nameBuffer = nullptr;
	do
	{
		char fullName[MAX_PATH] = { 0 };
		RUN_BREAK(!GetModuleFileNameA(NULL, fullName, MAX_PATH), "获取文件路径失败");

		quint32 nameLen = GetFileVersionInfoSizeA(fullName, 0);
		RUN_BREAK(!nameLen, "获取文件版本信息大小失败");

		nameBuffer = new(std::nothrow) char[nameLen + 1];
		RUN_BREAK(!nameBuffer, "文件版本信息大小分配内存失败");

		bool success = GetFileVersionInfoA(fullName, 0, nameLen, nameBuffer);
		RUN_BREAK(!success, "获取文件版本信息失败");

		struct LanguageCodePage
		{
			WORD language;
			WORD codePage;
		} *translate;

		quint32 queryLen = 0;
		success = VerQueryValue(nameBuffer, (TEXT("\\VarFileInfo\\Translation")), (LPVOID*)&translate, &queryLen);
		RUN_BREAK(!success, "查询注册表版本信息值[Translation]失败");

		QString str1, str2;
		str1.setNum(translate->language, 16);
		str2.setNum(translate->codePage, 16);
		str1 = "000" + str1;
		str2 = "000" + str2;
		QString verPath = "\\StringFileInfo\\" + str1.right(4) + str2.right(4) + "\\FileVersion";
		void* queryBuffer = nullptr;
		success = VerQueryValue(nameBuffer, (verPath.toStdWString().c_str()), &queryBuffer, &queryLen);
		RUN_BREAK(!success, "查询注册表版本信息值[FileVersion]失败");
		result = QString::fromUtf16((const unsigned short int*)queryBuffer);
	} while (false);
	SAFE_DELETE_A(nameBuffer);
	return result;
}

const QString& Utility::getAppVersion()
{
	static QString version = _getAppVersion();
	return version;
}

void Utility::setAppAppendName(const QString& appendName)
{
	Utility::Var::appendName = appendName;

}

void Utility::setAppAppendPos(bool appendPos)
{
	Utility::Var::appendPos = appendPos;
}

QString Utility::getAppAppendName()
{
	return Utility::Var::appendName;
}

bool Utility::getAppAppendPos()
{
	return Utility::Var::appendPos;
}

bool Utility::renameAppByVersion(QWidget* widget, const QString& appendName, bool appendPos)
{
	bool result = false;
	do
	{
		QString current = widget->windowTitle();
		QString title, newName;

		if (!Var::appendName.isEmpty())
		{
			current = QString("%1%2[%3]").arg(Var::appendPos ? Var::appendName : current)
				.arg(Var::appendPos ? current : Var::appendName).arg(getAppVersion());
		}
		else
		{
			current = QString("%1%2[%3]").arg(appendPos ? appendName : current)
				.arg(appendPos ? current : appendName).arg(getAppVersion());
		}

		title = newName = current;
		widget->setWindowTitle(title);

		QString oldName(getCurrentFileName());
		newName.append(".exe");
		if (oldName != newName)
		{
			MoveFileEx(Q_TO_WC_STR(oldName), Q_TO_WC_STR(newName), MOVEFILE_REPLACE_EXISTING);
		}
		result = true;
	} while (false);
	return result;
}

bool Utility::startApp(const QString& name, const int& show, bool absolutely)
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
			setLastError(Q_SPRINTF("启动失败,错误代码:%lu", ::GetLastError()));
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Utility::finishApp(const QString& name)
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
			setLastError("未查询到进程名:" + name);
			break;
		}
		QProcess::execute("cmd.exe", { "/c","taskkill","/im",name,"/f" });
		result = true;
	} while (false);
	return result;
}

QString Utility::getCurrentTime(bool fileFormat)
{
	return fileFormat ? QTime::currentTime().toString("hh:mm:ss").remove(':')
		: QTime::currentTime().toString("hh:mm:ss.zzz");
}

QString Utility::getCurrentDate(bool fileFormat)
{
	return fileFormat ? QDate::currentDate().toString("yyyy-MM-dd").remove('-')
		: QDate::currentDate().toString("yyyy-MM-dd");
}

QString Utility::getCurrentDateTime(bool fileFormat)
{
	QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	if (fileFormat)
	{
		return dateTime.remove('-').remove(':').remove('.');
	}
	return dateTime;
}

void Utility::getFileListByPath(const QString& path, QStringList& fileList)
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

QStringList Utility::getFileListBySuffixName(const QString& path, const QStringList& suffix)
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

char* Utility::wideCharToMultiByte(const wchar_t* wide)
{
	char* buffer = nullptr;
	do
	{
		int size = WideCharToMultiByte(CP_OEMCP, 0, wide, -1, NULL, 0, NULL, FALSE);
		if (size <= 0)
		{
			setLastError("计算长度失败");
			break;
		}

		buffer = NO_THROW_NEW char[size];
		if (!buffer) break;
		memset(buffer, 0x00, size);
		if (WideCharToMultiByte(CP_OEMCP, 0, wide, -1, buffer, size, NULL, FALSE) <= 0)
		{
			SAFE_DELETE_A(buffer);
			setLastError("转换失败");
		}
	} while (false);
	return buffer;
}

wchar_t* Utility::multiByteToWideChar(const char* multi)
{
	wchar_t* buffer = nullptr;
	do
	{
		int size = MultiByteToWideChar(CP_ACP, 0, multi, -1, NULL, 0);
		if (size <= 0)
		{
			setLastError("计算长度失败");
			break;
		}
		buffer = NO_THROW_NEW wchar_t[size];
		if (!buffer)
		{
			setLastError("分配内存失败");
			break;
		}

		if (MultiByteToWideChar(CP_ACP, 0, multi, -1, buffer, size) <= 0)
		{
			setLastError("转换失败");
			SAFE_DELETE_A(buffer);
		}
	} while (false);
	return buffer;
}

bool Utility::ping(const char* address, const int& times)
{
	QProcess process;
	process.start(Q_SPRINTF("ping %s -n %d", address, times));
	process.waitForFinished();
	return process.exitCode() == 0;
}

bool Utility::compareList(const QStringList& cmp1, const QStringList& cmp2)
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

bool Utility::removeList(const QStringList& list1, QStringList& list2)
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

bool Utility::httpDownload(const char* url, int timeout, const std::function<void(long, const char*)>& callback)
{
	struct UrlInfo
	{
		char url[512];
		std::function<void(long, const char*)>callback;
		int wait;
		HANDLE handle0;
		HANDLE handle1;
		CRITICAL_SECTION cs;
		char name[512];
		bool finish;
		bool timeout;
	};

	UrlInfo* pinfo = new UrlInfo;
	memset(pinfo, 0, sizeof(UrlInfo));
	strcpy(pinfo->url, url);
	pinfo->wait = timeout;
	pinfo->callback = callback;
	const char* ptr = strrchr(url, '/');
	strcpy(pinfo->name, ptr ? ptr + 1 : "unknown");

	InitializeCriticalSection(&pinfo->cs);

	pinfo->handle0 = (HANDLE)_beginthreadex(NULL, 0, [](PVOID args)->UINT
		{
			UrlInfo* pinfo = static_cast<UrlInfo*>(args);

			DeleteUrlCacheEntryA(pinfo->url);
			HRESULT result = URLDownloadToFileA(NULL, pinfo->url, pinfo->name, 0, NULL);

			pinfo->finish = true;

			if (!pinfo->timeout && pinfo->callback)
			{
				EnterCriticalSection(&pinfo->cs);
				pinfo->callback(result, pinfo->name);
				LeaveCriticalSection(&pinfo->cs);
			}

			_endthreadex(0);
			return result;
		}, (PVOID)pinfo, 0, NULL);

	pinfo->handle1 = (HANDLE)_beginthreadex(NULL, 0, [](PVOID args)->UINT
		{
			UrlInfo* pinfo = static_cast<UrlInfo*>(args);
			DWORD start = GetTickCount();
			while (true)
			{
				EnterCriticalSection(&pinfo->cs);
				if (pinfo->finish || GetTickCount() - start > pinfo->wait)
				{
					if (!pinfo->finish)
					{
						if (pinfo->callback)
						{
							pinfo->callback(S_FALSE, pinfo->name);
						}

						pinfo->timeout = true;

						while (!pinfo->finish)
						{
							Sleep(1000);
						}
						DeleteFileA(pinfo->name);
					}
					LeaveCriticalSection(&pinfo->cs);
					break;
				}
				LeaveCriticalSection(&pinfo->cs);
				Sleep(100);
			}
			CloseHandle(pinfo->handle0);
			CloseHandle(pinfo->handle1);
			DeleteCriticalSection(&pinfo->cs);
			delete pinfo;
			pinfo = nullptr;
			_endthreadex(0);
			return 0;
		}, (PVOID)pinfo, 0, NULL);
	return true;
}

bool Utility::initConsoleWindow(const QString& title)
{
	bool result = false;
	do
	{
		RUN_BREAK(!AllocConsole(), "分配控制台失败");
		SetConsoleTitleW(Q_TO_WC_STR(title));
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		if (output != INVALID_HANDLE_VALUE)
			SetConsoleTextAttribute(output, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		RUN_BREAK(!freopen("CONOUT$", "w", stderr), "重定向输出流stderr失败");
		qDebug() << "初始化控制台成功";
		qDebug() << "重定向stderr流成功";
		RUN_BREAK(!freopen("CONOUT$", "w", stdout), "重定向输出流stdout失败");
		qDebug() << "重定向stdout流成功";
		result = true;
	} while (false);
	return result;
}

bool Utility::exitConsoleWindow()
{
	return FreeConsole() == TRUE;
}

uint Utility::getTimeStamp(const QString& dt1, const QString& dt2)
{
	uint result = -1;
	do
	{
		QDateTime qdt1 = QDateTime::fromString(dt1, Qt::ISODate);
		QDateTime qdt2 = QDateTime::fromString(dt2, Qt::ISODate);
		RUN_BREAK(!(qdt1.isValid() && qdt2.isValid()), "日期时间格式错误");
		uint t1 = qdt1.toTime_t(), t2 = qdt2.toTime_t();
		result = (t1 < t2) ? (t2 - t1) : (t1 - t2);
	} while (false);
	return result;
}

void Utility::minuteCountdown(int totalMinute, int currentSecond, int& minute, int& second)
{
	minute = second = 0;

	int mseconds = totalMinute * 60 * 1000 - currentSecond * 1000;
	if (mseconds < 0)
		return;

	int seconds = mseconds /= 1000;

	int minutes = 0;
	if (seconds >= 60)
	{
		minutes = seconds / 60;
		seconds = seconds - minutes * 60;
	}
	minute = minutes;
	second = seconds;
	return;
}

QString Utility::getAppNameVersion(const QString& fileName)
{
	QString temp = QFileInfo(fileName).fileName();
	int index1 = temp.indexOf("[") + 1;
	int index2 = temp.indexOf("]");
	if (index1 == -1 || index2 == -1)
	{
		Utility::setLastError("版本名称格式错误");
		return QString();
	}
	return temp.mid(index1, index2 - index1);
}

int Utility::versionToNumber(const QString& appName)
{
	QString version = getAppNameVersion(appName);
	if (version.isEmpty())
	{
		version = appName;
	}

	QStringList dataList = version.split(".");
	if (dataList.size() != 4)
	{
		Utility::setLastError("版本数值格式错误");
		return -1;
	}

	int num[] = { 1000000,10000,100,1 }, sum = 0;
	for (int i = 0; i < dataList.size(); i++)
	{
		sum += dataList[i].toInt() * num[i];
	}
	return sum;
}

