#include "MainDlg.h"

using namespace Dt;

void MainDlg::closeEvent(QCloseEvent* event)
{
	QMessageBox::question(this, "友情提示", "你确定要退出吗?") == QMessageBox::Yes
		? event->accept() : event->ignore();
}

void MainDlg::setLastError(const QString& err)
{
#ifdef QT_DEBUG
	qDebug() << err << endl;
#endif
	m_lastError = err;
}

MainDlg::MainDlg(Dt::Base* thread, QWidget* parent)
{
	m_base = thread;
	!initInstance() ? QMessageBox::warning(this, "初始化失败", getLastError()) : true;
}

MainDlg::~MainDlg()
{
	SAFE_DELETE(m_base);

	SAFE_DELETE(m_scanCodeDlg);

	SAFE_DELETE(m_unlockDlg);

	SAFE_DELETE(m_authDlg);
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

		if (!m_scanCodeDlg)
		{
			setLastError("m_scanCodeDlg分配内存失败");
			break;
		}

		m_unlockDlg = NO_THROW_NEW UnlockDlg;
		if (!m_unlockDlg)
		{
			setLastError("m_unlockDlg分配内存失败");
			break;
		}

		m_authDlg = NO_THROW_NEW AuthDlg;
		if (!m_authDlg)
		{
			setLastError("m_authDlg分配内存失败");
			break;
		}

		if (!m_base)
		{
			setLastError("m_base分配内存失败");
			break;
		}

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

		connect(m_base, &Base::setAuthDlgSignal, this, &MainDlg::setAuthDlgSlot);

		connect(ui.imageLabel, &QLabelEx::coordinateSignal, this, &MainDlg::coordinateSlot);

		if (m_base->getDetectionType() == BaseTypes::DT_DVR)
		{
			Dt::Dvr* dvr = nullptr;
			if (dvr = dynamic_cast<Dt::Dvr*>(m_base))
			{
				dvr->setVlcMediaHwnd((HWND)ui.imageLabel->winId());
			}
			else
			{
				setLastError("基类不为Dt::Dvr,dynamic_cast返回一个nullptr,请检查继承基类是否错误");
				break;
			}
		}

		if (!m_base->initInstance())
		{
			setLastError(m_base->getLastError());
			break;
		}

		Misc::renameAppByVersion(this);

		m_base->start();

		result = true;
	} while (false);
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

void MainDlg::setAuthDlgSlot(bool* result, const int& flag)
{
	/*避免多次认证导致,让人反感,故只需要认证一次*/
	*result = !m_authDlg->isAuth() ? (m_authDlg->exec() == QDialog::Accepted) : true;

	if (!flag && m_base->threadIsPause())
	{
		m_base->threadContinue();
	}
	return;
}

void MainDlg::settingButtonSlot()
{
	do
	{
		SettingDlg* settingDlg = NO_THROW_NEW SettingDlg;
		if (!settingDlg)
		{
			break;
		}

		connect(settingDlg, &SettingDlg::setAuthDlgSignal, this, &MainDlg::setAuthDlgSlot);
		settingDlg->setAppName(this->windowTitle());
		settingDlg->show();
	} while (false);
	return;
}

void MainDlg::connectButtonSlot()
{
	static bool press = true;
	ui.connectButton->setEnabled(false);
	ui.connectButton->setIcon(press ? QIcon(":/images/Resources/images/disconnect.ico") :
		QIcon(":/images/Resources/images/connect.ico"));
	press ? m_base->openDevice() : m_base->closeDevice();
	ui.connectButton->setEnabled(true);
	ui.exitButton->setEnabled(!press);
	m_base->setTestSequence(press ? TS_SCAN_CODE : TS_NO);
	ui.connectButton->setText(press ? "断开" : "连接");
	press = !press;
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

void MainDlg::setQuestionBoxSlot(const QString& title, const QString& text, bool* result, bool auth)
{
	if (auth)
	{
		const QString&& userName = JsonTool::getInstance()->getUserConfigValue("用户名").toUpper();
		if (userName == "ROOT" || userName == "INVO")
		{
			*result = QMessageBox::question(this, title, text) == QMessageBox::Yes;
		}
		else
		{
			*result = false;
		}
	}
	else
	{
		*result = QMessageBox::question(this, title, text) == QMessageBox::Yes;
	}

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
	static MEMORYSTATUSEX memoryStatus;
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

