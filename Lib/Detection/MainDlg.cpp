#include "MainDlg.h"
using namespace Dt;

void MainDlg::closeEvent(QCloseEvent* event)
{
	QMessageBox::question(this, "友情提示", "你确定要退出吗?") == QMessageBox::Yes
		? event->accept() : event->ignore();
}

void MainDlg::setLastError(const QString& error)
{
	DEBUG_INFO() << error;
	m_lastError = error;
}

MainDlg::MainDlg(Dt::Base* thread, QWidget* parent)
{
	m_base = thread;
	if (!initInstance())
	{
		QMessageBox::warning(this, "初始化失败", getLastError());
	}
}

MainDlg::~MainDlg()
{
	if (m_isExistSettingDlg)
	{
		m_settingDlg->setAttribute(Qt::WA_DeleteOnClose, false);
		SAFE_DELETE(m_settingDlg);
	}

	SAFE_DELETE(m_scanCodeDlg);

	SAFE_DELETE(m_unlockDlg);

	SAFE_DELETE(m_authDlg);

	SAFE_DELETE(m_downloadDlg);

	SAFE_DELETE(m_base);
}

bool MainDlg::initInstance()
{
	bool result = false;
	do
	{
		ui.setupUi(this);

		setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);

		setAttribute(Qt::WA_DeleteOnClose);

		Misc::ThemeFactory::setTheme();

		JQCPUMonitor::initialize();

		connect(&m_usageRateTimer, &QTimer::timeout, this, &MainDlg::usageRateTimerSlot);
		m_usageRateTimer.start(1000);

		connect(ui.settingButton, &QPushButton::clicked, this, &MainDlg::settingButtonSlot);

		connect(ui.connectButton, &QPushButton::clicked, this, &MainDlg::connectButtonSlot);

		connect(ui.exitButton, &QPushButton::clicked, this, &MainDlg::exitButtonSlot);

		m_scanCodeDlg = NO_THROW_NEW ScanCodeDlg;

		RUN_BREAK(!m_scanCodeDlg, "扫码对话框分配内存失败");

		m_unlockDlg = NO_THROW_NEW UnlockDlg;
		RUN_BREAK(!m_unlockDlg, "解锁对话框分配内存失败");

		m_authDlg = NO_THROW_NEW AuthDlg;
		RUN_BREAK(!m_authDlg, "认证对话框分配内存失败");

		m_downloadDlg = NO_THROW_NEW DownloadDlg;
		RUN_BREAK(!m_downloadDlg, "下载对话框分配内存失败");

		RUN_BREAK(!m_base, "检测框架基类分配内存失败");

		connect(m_base, &Base::setScanCodeDlgSignal, this, &MainDlg::setScanCodeDlgSlot);

		connect(m_base, &Base::addListItemSignal, this, &MainDlg::addListItemSlot);

		connect(m_base, &Base::clearListItemSignal, this, &MainDlg::clearListItemSlot);

		connect(m_base, &Base::setCurrentStatusSignal, this, &MainDlg::setCurrentStatusSlot);

		connect(m_base, &Base::setMessageBoxSignal, this, &MainDlg::setMessageBoxSlot);

		connect(m_base, &Base::setMessageBoxExSignal, this, &MainDlg::setMessageBoxExSlot);

		connect(m_base, &Base::setQuestionBoxSignal, this, &MainDlg::setQuestionBoxSlot);

		connect(m_base, &Base::setQuestionBoxExSignal, this, &MainDlg::setQuestionBoxExSlot);

		connect(m_base, &Base::setTestResultSignal, this, &MainDlg::setTestResultSlot);

		connect(m_base, &Base::updateImageSignal, this, &MainDlg::updateImageSlot);

		connect(m_base, &Base::setUnlockDlgSignal, this, &MainDlg::setUnlockDlgSlot);

		connect(m_base, &Base::setDownloadDlgSignal, this, &MainDlg::setDownloadDlgSlot);

		if (m_base->getDetectionType() == BaseTypes::DT_DVR)
		{
			Dt::Dvr* dvr = nullptr;
			RUN_BREAK(!(dvr = dynamic_cast<Dt::Dvr*>(m_base)), "父类不为Dt::Dvr,设置VLC句柄失败");
			dvr->setVlcMediaHwnd((HWND)ui.imageLabel->winId());
			//connect(dvr->getUpdateSfr(), &Misc::UpdateSfr::updateSfrSignal, this, &MainDlg::updateSfrSlot);
		}

		RUN_BREAK(!m_base->initInstance(), m_base->getLastError());

		m_base->start();
		result = true;
	} while (false);
	Misc::renameAppByVersion(this);
	return result;
}

const QString& MainDlg::getLastError()
{
	return m_lastError;
}

void MainDlg::setScanCodeDlgSlot(bool show)
{
	show ? m_scanCodeDlg->show() : m_scanCodeDlg->hide();
}

void MainDlg::setUnlockDlgSlot(bool show)
{
	m_unlockDlg->exec();
	m_base->threadContinue();
}

void MainDlg::setAuthDlgSlot(bool* result)
{
	*result = !m_authDlg->isAuth() ? (m_authDlg->exec() == QDialog::Accepted) : true;
	return;
}

void MainDlg::setDownloadDlgSlot(BaseTypes::DownloadInfo* info)
{
	m_downloadDlg->download(info->title, info->url, info->path);
	m_downloadDlg->exec();
	info->result = m_downloadDlg->result();
	info->time = m_downloadDlg->elapsedTime();
	info->speed = m_downloadDlg->averageSpeed();
	info->error = m_downloadDlg->getLastError();
	m_base->threadContinue();
}

void MainDlg::settingButtonSlot()
{
	do
	{
		bool result = false;
		setAuthDlgSlot(&result);
		if (!result)
		{
			break;
		}

		if (m_isExistSettingDlg)
		{
			m_settingDlg->isMaximized() ? m_settingDlg->showMaximized() : m_settingDlg->showNormal();
			break;
		}

		m_settingDlg = NO_THROW_NEW SettingDlg;
		if (!m_settingDlg)
		{
			break;
		}

		//connect(m_settingDlg, &SettingDlg::setAuthDlgSignal, this, &MainDlg::setAuthDlgSlot);
		m_settingDlg->setConnected(m_connected);
		m_settingDlg->setIsExistDlg(&m_isExistSettingDlg);
		m_settingDlg->setBasePointer(m_base);
		m_settingDlg->setAppName(this->windowTitle().mid(0, this->windowTitle().indexOf(']') + 1));
		if (!m_settingDlg->initInstance())
		{
			QMessageBoxEx::warning(this, "错误", m_settingDlg->getLastError());
		}
		m_settingDlg->show();
	} while (false);
	return;
}

void MainDlg::connectButtonSlot()
{
	ui.connectButton->setEnabled(false);
	ui.connectButton->setIcon(!m_connected ? QIcon(":/images/Resources/images/disconnect.ico") :
		QIcon(":/images/Resources/images/connect.ico"));
	!m_connected ? m_base->openDevice() : m_base->closeDevice();
	ui.connectButton->setEnabled(true);
	ui.exitButton->setEnabled(m_connected);
	m_base->setTestSequence(!m_connected ? TS_SCAN_CODE : TS_NO);
	ui.connectButton->setText(!m_connected ? "断开" : "连接");
	m_connected = !m_connected;
}

void MainDlg::exitButtonSlot()
{
	this->close();
}

void MainDlg::setMessageBoxSlot(const QString& title, const QString& text)
{
	QMessageBox::warning(this, title, text);
	m_base->threadContinue();
}

void MainDlg::setMessageBoxExSlot(const QString& title, const QString& text, const QPoint& point)
{
	QMessageBox msgBox(QMessageBox::Warning, title, text, QMessageBox::Yes | QMessageBox::No);
	msgBox.move(point);
	msgBox.exec();
	m_base->threadContinue();
}

void MainDlg::setQuestionBoxSlot(const QString& title, const QString& text, bool* result)
{
	*result = QMessageBox::question(this, title, text) == QMessageBox::Yes;
	m_base->threadContinue();
}

void MainDlg::setQuestionBoxExSlot(const QString& title, const QString& text, bool* result, const QPoint& point)
{
	QMessageBox msgBox(QMessageBox::Question, title, text, QMessageBox::Yes | QMessageBox::No);
	msgBox.setParent(ui.recordList);
	msgBox.setStyleSheet("color:red");
	int width = ui.recordList->width() - msgBox.widthMM();
	msgBox.move(width - point.x(), point.y());
	*result = (msgBox.exec() == QMessageBox::Yes);
	m_base->threadContinue();
}

void MainDlg::setCurrentStatusSlot(const QString& status, bool systemStatus)
{
	systemStatus ? ui.systemLabel->setText(status) : ui.statusLabel->setText(status);
}

void MainDlg::setTestResultSlot(const BaseTypes::TestResult& testResult)
{
	QString result = "NO", color = "black";
	switch (testResult)
	{
	case BaseTypes::TR_TS:result = "TS";color = "yellow";break;
	case BaseTypes::TR_OK:result = "OK";color = "green";break;
	case BaseTypes::TR_NG:result = "NG";color = "red";break;
	case BaseTypes::TR_NO:result = "NO";color = "black";break;
	default:break;
	}
	ui.resultLabel->setText(result);
	ui.resultLabel->setStyleSheet(QString("background-color:%1;color:%2").arg(color).arg("rgb(0,0,0)"));
}

void MainDlg::addListItemSlot(const QString& item, bool logItem)
{
	QString icon = ":/images/Resources/images/";

	if (item.contains("OK") || item.contains("成功"))
	{
		icon.append("ok.ico");
	}
	else if (item.contains("NG") || item.contains("失败"))
	{
		icon.append("ng.ico");
	}
	else
	{
		icon.append("star.ico");
	}

	logItem ? ui.recordList->addItem(new QListWidgetItem(QIcon(icon), item))
		: ui.resultList->addItem(new QListWidgetItem(QIcon(icon), item));
	ui.recordList->setCurrentRow(ui.recordList->count() - 1);
	ui.resultList->setCurrentRow(ui.resultList->count() - 1);
}

void MainDlg::clearListItemSlot()
{
	ui.resultList->clear();
	ui.recordList->clear();
}

void MainDlg::updateImageSlot(const QImage& image)
{
	ui.imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainDlg::coordinateSlot(const QPoint& point)
{
	//qDebug() << point << endl;
}

void MainDlg::usageRateTimerSlot()
{
	static MEMORYSTATUSEX memoryStatus = { 0 };
	memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memoryStatus);

	qreal&& rate = JQCPUMonitor::cpuUsagePercentage() * 100;
	static QString cpuStyle = "color:rgb(0,0,0);";
	static QString memStyle = "color:rgb(0,0,0);";

	auto processFnc = [](const int& usageRate,QString& styleSheet)->void {
		if (usageRate <= 50)
		{
			styleSheet = "color:rgb(34,139,34);";
		}
		else if (usageRate > 50 && usageRate <= 80)
		{
			styleSheet = "color:rgb(218,165,32);";
		}
		else if (usageRate > 80)
		{
			styleSheet = "color:rgb(165,42,42);";
		} 
	};

	processFnc(rate, cpuStyle);
	processFnc(memoryStatus.dwMemoryLoad, memStyle);

	ui.cpuLabel->setText(QString().sprintf("%6.2f%%", rate));
	ui.cpuLabel->setStyleSheet(cpuStyle);

	ui.memLabel->setText(QString().sprintf("%02d%%", memoryStatus.dwMemoryLoad));
	ui.memLabel->setStyleSheet(memStyle);
}

void MainDlg::updateSfrSlot()
{
	dynamic_cast<Dt::Dvr*>(m_base)->getUpdateSfr()->setInterval(1000);

	HDC hDCMem = CreateCompatibleDC(NULL);
	HWND hWnd = (HWND)ui.imageLabel->winId();
	RECT rect = { 0 };
	GetWindowRect(hWnd, &rect);
	HDC hDc = GetDC(hWnd);
	ReleaseDC(hWnd, hDc);
	HBITMAP hBmp = CreateCompatibleBitmap(hDc, rect.right - rect.left, rect.bottom - rect.top);
	HGDIOBJ hOld = SelectObject(hDCMem, hBmp);
	SelectObject(hDCMem, hOld);
	DeleteObject(hDCMem);
	qDebug() << (Misc::saveBitmapToFile(hBmp, "d:\\temp.bmp") ? "成功" : "失败");
	//QFile file("d:\\temp.bmp");
	//file.open(QFile::WriteOnly);
	//QPixmap pix = ui.imageLabel->grab(ui.imageLabel->rect());
	//pix.save(&file, "BMP");
	//file.close();
}

