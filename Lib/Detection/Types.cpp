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
		QString path = QString(".\\%1\\RUN\\").arg(GET_DT_DIR());
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

bool Misc::cvImageToQtImage(Mat* mat, QImage* qt)
{
	bool result = false;
	do
	{
		if (!mat || !qt)
			break;

		cvtColor(*mat, *mat, CV_BGR2RGB);
		*qt = QImage(mat->data, mat->cols, mat->rows, QImage::Format_RGB888);
		result = true;
	} while (false);
	return result;
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
		title = newName = QString("%1%2检测[%3]").arg(device.modelName, GET_DT_TYPE(), Misc::getAppVersion());
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

bool Misc::startApp(const QString& name, const int& show, bool absolutely)
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

	QString fileName = typeName + GET_DT_TYPE() + QString("检测[") + getAppVersion() + QString("].lnk");
	QString linkPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "\\" + fileName;

	if (QDir(linkPath).exists())
		return true;

	wchar_t temp[512] = { 0 };
	GetModuleFileNameW(NULL, temp, sizeof(temp));
	QString fileFullPath = WC_TO_Q_STR(temp, sizeof(temp));
	QFile app(fileFullPath);
	return app.link(linkPath);
}

bool Misc::saveBitmapToFile(HBITMAP hBitmap, const QString& fileName)
{
	HDC     hDC;
	//当前分辨率下每象素所占字节数          
	int     iBits;
	//位图中每象素所占字节数          
	WORD     wBitCount;
	//定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数              
	DWORD     dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	//位图属性结构              
	BITMAP     Bitmap;
	//位图文件头结构          
	BITMAPFILEHEADER     bmfHdr;
	//位图信息头结构              
	BITMAPINFOHEADER     bi;
	//指向位图信息头结构                  
	LPBITMAPINFOHEADER     lpbi;
	//定义文件，分配内存句柄，调色板句柄              
	HANDLE     fh, hDib, hPal, hOldPal = NULL;

	//计算位图文件每个像素所占字节数              
	hDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else  if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;

	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 0;

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

	//为位图内容分配内存              
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	//     处理调色板                  
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//     获取该调色板下新的像素值              
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
		(BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	//恢复调色板                  
	if (hOldPal)
	{
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	//创建位图文件                  
	fh = CreateFileW(Q_TO_WC_STR(fileName), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return false;

	//     设置位图文件头              
	bmfHdr.bfType = 0x4D42;     //     "BM"              
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	//     写入位图文件头              
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	//     写入位图文件其余内容              
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	//清除                  
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return true;
}

bool Misc::ping(const char* address, const int& times)
{
	QProcess process;
	process.start(Q_SPRINTF("ping %s -n %d", address, times));
	process.waitForFinished();
	return process.exitCode() == 0;
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