#include "MainDlg.h"

/************************************************************************/
/* Public                                                               */
/************************************************************************/
MainDlg::MainDlg(QWidget* parent)
	: QWidget(parent)
{
	bool success = true;
	do 
	{
		initUi();

		if (!initInstance())
		{
			QMessageBox::warning(this, "错误", getLastError());
			success = false;
			break;
		}
		else
		{
			if (!m_choiceDlg->exec())
			{
				success = false;
				break;
			}
		}	
	} while (false);

	if (!success)
	{
		m_maskCloseEvent = true;
		this->close();
	}
}

MainDlg::~MainDlg()
{
	SAFE_DELETE(m_cpuUsageRateTimer);

	SAFE_DELETE(m_threadHandler);

	SAFE_DELETE_A(m_channelInterface);

	SAFE_DELETE(m_scanCodeDlg);

	SAFE_DELETE(m_choiceDlg);

	SAFE_DELETE(m_vBoxLayout);

	SAFE_DELETE(m_noDevice);

	SAFE_DELETE(m_authDlg);

	JsonTool::deleteInstance();
}

const QString& MainDlg::getLastError()
{
	return m_lastError;
}

bool MainDlg::initUi()
{
	this->ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->ui.scrollArea->setStyleSheet("QScrollArea {background-color:transparent;}");
	this->ui.scrollArea->viewport()->setStyleSheet("background-color:transparent;");

	qApp->setStyle(QStyleFactory::create("Fusion"));
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

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	m_screenSize = QSize(screenRect.width() / 2 + 100, screenRect.height() / 2 + 100);
	this->resize(m_screenSize);
	return true;
}

bool MainDlg::initInstance()
{
	bool result = false;
	do
	{
		m_jsonTool = JsonTool::getInstance();

		if (!m_jsonTool)
		{
			setLastError("m_jsonTool分配内存失败");
			break;
		}

		if (!m_jsonTool->initInstance())
		{
			setLastError(m_jsonTool->getLastError());
			break;
		}

		connect(ui.setting, &QPushButton::clicked, this, &MainDlg::settingButtonSlot);

		connect(ui.connect, &QPushButton::clicked, this, &MainDlg::connectButtonSlot);

		connect(ui.reload, &QPushButton::clicked, this, &MainDlg::reloadButtonSlot);

		connect(ui.exit, &QPushButton::clicked, this, &MainDlg::exitButtonSlot);

		ui.burnMode->setToolTip(JsonTool::getInstance()->getBurnModeTips());

		if (!initCpuMonitor())
		{
			break;
		}

		m_threadHandler = new(std::nothrow) ThreadHandler;
		if (!m_threadHandler)
		{
			setLastError(QString("%1 m_threadHandler分配内存失败").arg(__FUNCTION__));
			break;
		}

		connect(m_threadHandler, &ThreadHandler::setMessageBoxSignal, this, &MainDlg::setMessageBoxSlot);

		connect(m_threadHandler, &ThreadHandler::scanCodeDlgSignal, this, &MainDlg::scanCodeDlgSlot);

		if (!m_threadHandler->initInstance())
		{
			setLastError(QString("%1初始化失败,原因%2").arg(__FUNCTION__, m_threadHandler->getLastError()));
			break;
		}

		connect(ui.enableChannel, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged),
			[&](const QString&)->void {m_threadHandler->setChannelCount(ui.enableChannel->currentIndex() + 1); });
		
		m_scanCodeDlg = new(std::nothrow) ScanCodeDlg;
		if (!m_scanCodeDlg)
		{
			setLastError("m_scanCodeDlg分配内存失败");
			break;
		}

		m_choiceDlg = new(std::nothrow) ChoiceDlg;
		if (!m_choiceDlg)
		{
			setLastError("m_choiceDlg分配内存失败");
			break;
		}
		connect(m_choiceDlg, &ChoiceDlg::typeNameCorrectSignal, this, &MainDlg::typeNameCorrectSlot);

		m_authDlg = NO_THROW_NEW AuthDlg;
		if (!m_authDlg)
		{
			setLastError("m_authDlg分配内存失败");
			break;
		}

		m_vBoxLayout = new(std::nothrow) QVBoxLayout;
		if (!m_vBoxLayout)
		{
			setLastError(QString("%1 m_vBoxLayout分配内存失败").arg(__FUNCTION__));
			break;
		}

		m_aardvarkCount = m_threadHandler->getAardvarkCount();
		if (m_aardvarkCount > 0)
		{
			if (!createChannelInterface())
			{
				break;
			}
		}
		else
		{
			createNoDeviceInterface();
		}
		
		ui.scrollAreaWidgetContents->setLayout(m_vBoxLayout);
		result = true;
	} while (false);
	return result;
}

bool MainDlg::initCpuMonitor()
{
	bool result = false;
	do 
	{
		JQCPUMonitor::initialize();

		m_cpuUsageRateTimer = new(std::nothrow) QTimer;
		if (!m_cpuUsageRateTimer)
		{
			setLastError("m_cpuUsageRateTimer分配内存失败");
			break;
		}

		connect(m_cpuUsageRateTimer, &QTimer::timeout, this, &MainDlg::cpuUsageRateTimerSlot);
		m_cpuUsageRateTimer->start(1000);
		
		result = true;
	} while (false);
	return result;
}

bool MainDlg::createChannelInterface()
{
	bool result = false;
	do
	{
		if (m_aardvarkCount <= 0)
		{
			/*屏蔽无设备报错*/
			result = true;
			break;
		}

		m_channelInterface = new(std::nothrow) ChannelDlg[m_aardvarkCount];
		if (!m_channelInterface)
		{
			setLastError(QString("%1 m_channelInterface分配内存失败").arg(__FUNCTION__));
			break;
		}

		for (int i = 0; i < m_aardvarkCount; i++)
		{
			ui.enableChannel->addItem(QString("%1个通道").arg(i + 1));

			ui.enableChannel->setItemIcon(i, QIcon(":/Images/Resources/Images/firefox.ico"));

			m_channelInterface[i].setGroupTitle(i + 1, m_threadHandler->getAardvarkPortAndSn()[i]);
			
			connect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateProgressSignal, &m_channelInterface[i], &ChannelDlg::updateProgressSlot);

			connect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateCurrentStatusSiganl, &m_channelInterface[i], &ChannelDlg::updateCurrentStatusSlot);

			connect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateBurnStatusSiganl, &m_channelInterface[i], &ChannelDlg::updateBurnStatusSlot);

			connect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateGroupTitleSignal, &m_channelInterface[i], &ChannelDlg::updateGroupTitleSlot);

			connect(&m_threadHandler->getWorkThread()[i], &WorkThread::setBurnTimerRunSignal, &m_channelInterface[i], &ChannelDlg::setBurnTimerRunSlot);
			
			connect(&m_channelInterface[i], &ChannelDlg::getBurnTimerTimeSignal, &m_threadHandler->getWorkThread()[i], &WorkThread::getBurnTimerTimeSlot);
			
			m_vBoxLayout->addWidget(&m_channelInterface[i]);
		}

		ui.enableChannel->setCurrentIndex(ui.enableChannel->count() - 1);
		m_vBoxLayout->addStretch();
		result = true;
	} while (false);
	return result;
}

void MainDlg::deleteChannelInterface()
{
	do
	{
		if (m_aardvarkCount <= 0)
		{
			break;
		}

		ui.enableChannel->clear();
		for (int i = 0; i < m_aardvarkCount; i++)
		{
			disconnect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateProgressSignal, &m_channelInterface[i], &ChannelDlg::updateProgressSlot);
			
			disconnect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateCurrentStatusSiganl, &m_channelInterface[i], &ChannelDlg::updateCurrentStatusSlot);
			
			disconnect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateBurnStatusSiganl, &m_channelInterface[i], &ChannelDlg::updateBurnStatusSlot);

			disconnect(&m_threadHandler->getWorkThread()[i], &WorkThread::updateGroupTitleSignal, &m_channelInterface[i], &ChannelDlg::updateGroupTitleSlot);
			
			disconnect(&m_threadHandler->getWorkThread()[i], &WorkThread::setBurnTimerRunSignal, &m_channelInterface[i], &ChannelDlg::setBurnTimerRunSlot);
			
			disconnect(&m_channelInterface[i], &ChannelDlg::getBurnTimerTimeSignal, &m_threadHandler->getWorkThread()[i], &WorkThread::getBurnTimerTimeSlot);
			
			m_vBoxLayout->removeWidget(&m_channelInterface[i]);
		}
		deleteStretch();
		SAFE_DELETE_A(m_channelInterface);
	} while (false);
	return;
}

bool MainDlg::createNoDeviceInterface()
{
	bool result = false;
	do
	{
		m_noDevice = NO_THROW_NEW QLabel(this);
		if (!m_noDevice)
		{
			setLastError("m_noDevice分配内存失败");
			break;
		}
		QFont font;
		font.setPixelSize(30);
		font.setBold(true);
		m_noDevice->setFont(font);
		m_noDevice->setAlignment(Qt::AlignHCenter);
		m_noDevice->setText("请连接烧录器");
		m_noDevice->setStyleSheet("background-color:rgb(255,0,0);color:rgb(255,255,255)");
		m_vBoxLayout->addWidget(m_noDevice);
		m_vBoxLayout->addStretch();
	} while (false);
	return result;
}

void MainDlg::deleteNoDeviceInterface()
{
	do
	{
		if (m_aardvarkCount > 0)
		{
			break;
		}

		if (m_noDevice)
		{
			m_vBoxLayout->removeWidget(m_noDevice);
			deleteStretch();
			SAFE_DELETE(m_noDevice);
		}
	} while (false);
	return;
}

void MainDlg::enableControl(bool enable)
{
	//ui.setting->setEnabled(enable);
	ui.reload->setEnabled(enable);
	ui.exit->setEnabled(enable);
}

void MainDlg::updateBurnModeControl(const int& burnMode)
{
	QString text = "";
	switch (burnMode)
	{
	case BurnMode::BM_ATC_016_SET:text = "ATC_016_SET"; break;
	case BurnMode::BM_CTC_016_SET:text = "CTC_016_SET"; break;
	case BurnMode::BM_CTC_019_SET:text = "CTC_019_SET"; break;
	case BurnMode::BM_CTC_CHANGAN_IMS:text = "CTC_CHANGAN_IMS"; break;
	case BurnMode::BM_FLASH_AXS340:text = "FLASH_AXS340"; break;
	case BurnMode::BM_EEP_AXS340:text = "EEP_AXS340"; break;
	case BurnMode::BM_NET_AXS340:text = "NETWORK"; break;
	case BurnMode::BM_EEP_GEELY_BX11:text = "EEP_GEELY_BX11"; break;
	case BurnMode::BM_CTC_EP30TAP_DMS:text = "CTC_EP30TAP_DMS"; break;
	case BurnMode::BM_ATC_BYD_OV7958:text = "CTC_BYD_OV7958"; break;
	default:text = "模式错误"; break;
	}
	ui.burnMode->setText(QString("[%1,%2]").arg(burnMode).arg(text));
}

/************************************************************************/
/* Public Slot                                                          */
/************************************************************************/
void MainDlg::settingButtonSlot()
{
	do 
	{
		if (m_threadHandler->isWorkThreadRunning())
		{
			QMessageBoxEx::warning(this, "严重警告", "当前正在烧录中,切勿修改数据,\n否则将会导致程序崩溃!\n等待烧录完成方可修改数据.");
		}

		if (!m_authDlg->isAuth())
		{
			if (m_authDlg->exec() != QDialog::Accepted)
			{
				break;
			}
		}

		SettingDlg* settingDlg = NO_THROW_NEW SettingDlg;
		if (!settingDlg)
		{
			setLastError("m_settingInterface分配内存失败");
			break;
		}
		connect(settingDlg, &SettingDlg::updateTypeNameSignal, this, &MainDlg::updateTypeNameSlot);
		settingDlg->setTypeName(m_typeName);
		settingDlg->show();
	} while (false);
	return;
}

void MainDlg::connectButtonSlot()
{
	if (!m_jsonTool->getParsedFileConfig()->valid)
	{
		QMessageBoxEx::warning(this, "连接失败", QString("[%1]节点无效,\n请进行修正参数").arg(m_jsonTool->getParsedFileConfig()->nodeName));
		return;
	}

	static bool open = true;

	if (open)
	{
		if (!m_threadHandler->openDevice())
		{
			QMessageBox::warning(this, "错误", m_threadHandler->getLastError());
		}
		ui.connect->setText("断开");
	}
	else
	{
		if (QMessageBoxEx::question(this, "友情提示","你确定要断开连接吗?\n如果正在烧录切勿断开.") != QMessageBoxEx::Yes)
		{
			return;
		}

		if (!m_threadHandler->closeDevice())
		{
			QMessageBoxEx::warning(this, "错误", m_threadHandler->getLastError());
		}
		ui.connect->setText("连接");
		m_scanCodeDlg->hide();
	}
	
	if (m_typeName == SUPER_PASSWORD)
	{
		ui.enableName->setEnabled(!open);
	}

	m_threadHandler->setRunSwitch(open);
	open = !open;
	if (m_threadHandler->getDebugMode())
	{
		ui.enableName->setEnabled(open);
	}
	enableControl(open);
}

void MainDlg::exitButtonSlot()
{
	this->close();
}

void MainDlg::reloadButtonSlot()
{
	bool success = true;
	do
	{
		if (QMessageBox::question(this, "友情提示", "你确定要重新加载烧录器吗?\n如果正在烧录切勿重新加载.") != QMessageBox::Yes)
		{
			break;
		}
		
		deleteNoDeviceInterface();
		
		deleteChannelInterface();

		if (!m_threadHandler->loadAardvarkDevice())
		{
			success = false;
			break;
		}

		m_aardvarkCount = m_threadHandler->getAardvarkCount();
		if (!createChannelInterface())
		{
			success = false;
			break;
		}

		if (m_aardvarkCount <= 0)
		{
			if (!createNoDeviceInterface())
			{
				break;
			}
		}
	} while (false);

	if (!success)
	{
		QMessageBox::warning(this, "错误", QString("重新加载设备失败,原因%1").arg(m_threadHandler->getLastError()));
	}
	return;
}

void MainDlg::setMessageBoxSlot(const QString& title, const QString& text)
{
	QMessageBox::information(this, title, text);
}

void MainDlg::scanCodeDlgSlot(const int& number)
{
	m_scanCodeDlg->setChannel(number);
	m_scanCodeDlg->show();
}

void MainDlg::typeNameCorrectSlot(const QString& typeName)
{
	m_typeName = typeName;

	/*调试模式*/
	if (typeName == SUPER_PASSWORD)
	{
		ui.title->setText(ui.title->text() + "调试模式");
		ui.enableName->setEnabled(true);
		m_threadHandler->enableDebugMode(true);

		connect(ui.enableName, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged),
			[&](const QString& name)->void {
				if (m_delComboItem)
					return;
				if (!m_jsonTool->getParsedFileConfig(name))
					QMessageBoxEx::warning(this, "错误", m_jsonTool->getLastError());
				else
					updateBurnModeControl(m_jsonTool->getParsedFileConfig()->burnMode);
			});
		
		ui.enableName->addItems(m_jsonTool->getFileConfigObj().keys());
		for (int i = 0; i < ui.enableName->count(); i++)
		{
			ui.enableName->setItemIcon(i, QIcon(":/Images/Resources/Images/firefox.ico"));
		}
	}
	else
	{
		ui.enableName->addItem(typeName);
		ui.enableName->setItemIcon(0, QIcon(":/Images/Resources/Images/firefox.ico"));
		updateBurnModeControl(m_jsonTool->getParsedFileConfig()->burnMode);
	}
}

void MainDlg::cpuUsageRateTimerSlot()
{
	static MEMORYSTATUSEX memoryStatus;
	memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memoryStatus);

	qreal&& rate = JQCPUMonitor::cpuUsagePercentage() * 100;
	static QString cpuStyle = "color:rgb(0,0,0);";
	static QString memStyle = "color:rgb(0,0,0);";

	auto processFnc = [](const int& usageRate, QString& styleSheet)->void {
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

	ui.cpuUsageRate->setText(QString().sprintf("%6.2f%%", rate));
	ui.cpuUsageRate->setStyleSheet(cpuStyle);

	ui.memUsageRate->setText(QString().sprintf("%02d%%", memoryStatus.dwMemoryLoad));
	ui.memUsageRate->setStyleSheet(memStyle);
}

void MainDlg::updateTypeNameSlot()
{
	m_delComboItem = true;
	int count = ui.enableName->count();
	for (int i = 0; i < count; i++)
	{
		ui.enableName->removeItem(0);
	}
	m_delComboItem = false;
	ui.enableName->addItems(m_jsonTool->getFileConfigObj().keys());
	for (int i = 0; i < ui.enableName->count(); i++)
	{
		ui.enableName->setItemIcon(i, QIcon(":/Images/Resources/Images/firefox.ico"));
	}
}

/************************************************************************/
/* Protected                                                            */
/************************************************************************/
void MainDlg::closeEvent(QCloseEvent* event)
{
	do 
	{
		if (m_maskCloseEvent)
		{
			break;
		}

		switch (QMessageBox::question(this,"友情提示","你确定要退出吗?"))
		{
		case QMessageBox::Yes:event->accept();break;
		case QMessageBox::No:event->ignore();break;
		default:break;
		}
	} while (false);
	return;
}

void MainDlg::setLastError(const QString& err)
{
#ifdef QT_DEBUG
	qDebug() << __FUNCTION__ << err << endl;
#endif
	m_lastError = err;
}

void MainDlg::deleteStretch()
{
	for (int i = 0; i < m_vBoxLayout->count(); ++i)
	{
		QLayoutItem* layoutItem = m_vBoxLayout->itemAt(i);

		if (layoutItem->spacerItem())
		{
			m_vBoxLayout->removeItem(layoutItem);
			--i;
		}
	}
}
