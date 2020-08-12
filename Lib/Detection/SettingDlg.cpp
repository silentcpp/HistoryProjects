#include "SettingDlg.h"
#include "Detection.h"

SettingDlg::SettingDlg(QWidget* parent)
	: QWidget(parent)
{
	this->ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
}

SettingDlg::~SettingDlg()
{
	Dt::Base::getCanConnect()->SetDynamicDisplay();
	Dt::Base::getCanConnect()->EndReceiveThread();
}

bool SettingDlg::setAuthDlg(const int& flag)
{
	bool result = false;
	emit setAuthDlgSignal(&result, flag);
	return result;
}

const QString& SettingDlg::getLastError()
{
	return m_lastError;
}

bool SettingDlg::initInstance()
{
	bool result = false;
	do
	{
		//AUTO_RESIZE(this);

		ui.configAdd->setEnabled(false);
		ui.configDel->setEnabled(false);

		connect(ui.configExpand, &QPushButton::clicked, this, &SettingDlg::configExpand);
		connect(ui.configAdd, &QPushButton::clicked, this, &SettingDlg::configAddNode);
		connect(ui.configDel, &QPushButton::clicked, this, &SettingDlg::configDelNode);
		connect(ui.configSave, &QPushButton::clicked, this, &SettingDlg::configSaveData);
		connect(ui.configExit, &QPushButton::clicked, this, &SettingDlg::configExitDlg);
		connect(ui.canStartup, &QPushButton::clicked, this, &SettingDlg::canStartupSlot);
		connect(ui.startCapture, &QPushButton::clicked, this, &SettingDlg::startCaptureSlot);
		connect(ui.stopCapture, &QPushButton::clicked, this, &SettingDlg::stopCaptureSlot);
		connect(ui.saveCoord, &QPushButton::clicked, this, &SettingDlg::saveCoordSlot);

		m_jsonTool = JsonTool::getInstance();
		if (!m_jsonTool)
		{
			setLastError("JSON工具初始化失败");
			break;
		}

		auto& device = m_jsonTool->getParsedDefConfig()->device;
		QString&& newTitle = QString("%1%2%3设置[%4]").arg(device.modelName,
			Misc::getAppAppendName(),
			device.detectionName,
			Misc::getAppVersion());

		setWindowTitle(newTitle);
		if (!initConfigTreeWidget())
		{
			break;
		}

		initCanTableWidget();

		initAboutWidget();
		result = true;
	} while (false);
	return result;
}

void SettingDlg::setAppName(const QString& name)
{
	m_name = name;
}


void SettingDlg::configExpand()
{
	static bool pressed = true;
	pressed ? ui.configTree->expandAll() : ui.configTree->collapseAll();
	ui.configExpand->setIcon(QIcon(QString(":/images/Resources/images/%1").arg(pressed ? "collapse.ico" : "expand.ico")));
	ui.configExpand->setText(pressed ? "全部收起" : "全部展开");
	pressed = !pressed;
}

void SettingDlg::configAddNode()
{
	do
	{
		QTreeWidgetItem* oldCurrentConfigItem = m_currentConfigItem;
		QString&& currentKey = ITEM_TO_STR(m_currentConfigItem, 0);
		const QStringList keyList = { "电压配置","电流配置","电阻配置","版本配置","诊断故障码配置" };
		if (!keyList.contains(currentKey))
		{
			QMessageBoxEx::warning(this, "警告", currentKey + "不允许添加子节点");
			break;
		}

		const QStringList newKeyList = {
			QString("0.0V元件电压[%1]").arg(m_jsonTool->getVoltageConfigCount()),
			QString("0.0V工作电流[%1]").arg(m_jsonTool->getCurrentConfigCount()),
			QString("0.0V对地电阻[%1]").arg(m_jsonTool->getResConfigCount()),
			QString("XXXX版本配置[%1]").arg(m_jsonTool->getVerConfigCount()),
			QString("XXXX诊断配置[%1]").arg(m_jsonTool->getDtcConfigCount())
		};

		const QStringList&(JsonTool:: * childKeyListFnc[])() = {
			&JsonTool::getChildVoltageConfigKeyList,
			&JsonTool::getChildCurrentConfigKeyList,
			&JsonTool::getChildResConfigKeyList,
			&JsonTool::getChildVerConfigKeyList,
			&JsonTool::getChildDtcConfigKeyList
		};

		const QStringList&(JsonTool:: * childValueListFnc[])() = {
			&JsonTool::getChildVoltageConfigValueList,
			&JsonTool::getChildCurrentConfigValueList,
			&JsonTool::getChildResConfigValueList,
			&JsonTool::getChildVerConfigValueList,
			&JsonTool::getChildDtcConfigValueList
		};

		const QStringList&(JsonTool:: * explainListFnc[])() = {
			&JsonTool::getVoltageConfigExplain,
			&JsonTool::getCurrentConfigExplain,
			&JsonTool::getResConfigExplain,
			&JsonTool::getVerConfigExplain,
			&JsonTool::getDtcConfigExplain
		};

		QJsonObject& (JsonTool:: * getObjectFnc[])() = {
			&JsonTool::getVoltageConfigObj,
			&JsonTool::getCurrentConfigObj,
			&JsonTool::getResConfigObj,
			&JsonTool::getVerConfigObj,
			&JsonTool::getDtcConfigObj
		};

		for (int i = 0; i < keyList.count(); i++)
		{
			if (currentKey == keyList[i])
			{
				QList<QTreeWidgetItem*> childList = {};
				const QString& newKey = newKeyList[i];
				QJsonObject newObj;
				auto newItem = new QTreeWidgetItem(m_currentConfigItem, { newKey });
				newItem->setIcon(0, QIcon(":/images/Resources/images/tree.ico"));
				for (int j = 0; j < (m_jsonTool->*childKeyListFnc[i])().count(); j++)
				{
					childList.append(new QTreeWidgetItem({
						(m_jsonTool->*childKeyListFnc[i])()[j],
						(m_jsonTool->*childValueListFnc[i])()[j],
						(m_jsonTool->*explainListFnc[i])()[j]
						}));
					childList.at(j)->setIcon(0, QIcon(":/images/Resources/images/key.ico"));
					childList.at(j)->setIcon(1, QIcon(":/images/Resources/images/file.ico"));
					childList.at(j)->setIcon(2, QIcon(":/images/Resources/images/msg.ico"));
					newObj.insert((m_jsonTool->*childKeyListFnc[i])()[j],
						(m_jsonTool->*childValueListFnc[i])()[j]);
				}
				newItem->addChildren(childList);
				(m_jsonTool->*getObjectFnc[i])().insert(newKey, newObj);
				break;
			}
		}
		m_currentConfigItem = oldCurrentConfigItem;
	} while (false);
	return;
}

void SettingDlg::configDelNode()
{
	do
	{
		if (!m_currentConfigItem->parent())
		{
			break;
		}

		QJsonObject& (JsonTool:: * getObjectFnc[])() = {
		&JsonTool::getVoltageConfigObj,
		&JsonTool::getCurrentConfigObj,
		&JsonTool::getResConfigObj,
		&JsonTool::getVerConfigObj,
		&JsonTool::getDtcConfigObj
		};

		QString&& parentKey = ITEM_TO_STR(m_currentConfigItem->parent(), 0);
		QString&& currentKey = ITEM_TO_STR(m_currentConfigItem, 0);

		const QStringList keyList = { "电压配置","电流配置","电阻配置","版本配置","诊断故障码配置" };
		int find = -1;
		for (int i = 0; i < keyList.count(); i++)
		{
			if (parentKey == keyList[i])
			{
				find = i;
				break;
			}
		}

		if (find == -1)
		{
			QMessageBoxEx::warning(this, "警告", parentKey + "不允许删除子节点");
			break;
		}

		m_currentConfigItem->parent()->takeChild(ui.configTree->currentIndex().row());
		(m_jsonTool->*getObjectFnc[find])().remove(currentKey);
		m_currentConfigItem = ui.configTree->currentItem();
	} while (false);
	return;
}

void SettingDlg::configSaveData()
{
	do
	{
		if (!setAuthDlg())
		{
			QMessageBoxEx::warning(this, "提示", "认证失败,无法进行保存");
			break;
		}

		QStringList warn = { "配置已生效,无需重启应用程序","配置已生效,需重启应用重新,是否重启?","配置已生效,需重新连接应用程序","保存成功" };
		const QString& title = m_jsonTool->initInstance(true) ? warn.value(m_updateWarn) : QString("保存失败,%1").arg(m_jsonTool->getLastError());

		if (m_updateWarn == UW_NO || m_updateWarn == UW_EMPTY)
		{
			QMessageBoxEx::information(this, "提示", title);
		}
		else if (m_updateWarn == UW_RESTART)
		{
			if (QMessageBoxEx::question(this, "警告", title) == QMessageBoxEx::Yes)
			{
				QProcess* process(new QProcess);
				process->setWorkingDirectory(Misc::getCurrentDir());

				/*因启动程序会导致运行中更改名称,此处使用getModuleFileName来获取会导致获取到的为旧的名称*/
				const QString& cmd = QString("cmd.exe /c start %1.exe").arg(m_name);
				process->start(cmd);
				process->waitForStarted();
				QApplication::exit(0);
			}
		}
		else
		{
			QMessageBoxEx::warning(this, "警告", title);
		}
	} while (false);
	return;
}

void SettingDlg::configExitDlg()
{
	close();
}

void SettingDlg::setBasePointer(void* pointer)
{
	m_basePointer = pointer;
}

void SettingDlg::configTreeItemPressedSlot(QTreeWidgetItem* item, int column)
{
	do
	{
		QString&& currentKey = ITEM_TO_STR(item, 0);
		const QStringList keyList = { "电压配置","电流配置","电阻配置","版本配置","诊断故障码配置" };
		ui.configAdd->setEnabled(keyList.contains(currentKey));

		if (item->parent())
		{
			QString&& parentKey = ITEM_TO_STR(item->parent(), 0);
			ui.configDel->setEnabled(keyList.contains(parentKey));
		}
		else
		{
			ui.configDel->setEnabled(false);
		}

		if (m_configItemOpen)
		{
			ui.configTree->closePersistentEditor(m_currentConfigItem, m_currentConfigColumn);
			m_configItemOpen = false;
		}
		m_currentConfigItem = item;
	} while (false);
	return;
}

void SettingDlg::configTreeItemDoubleClickedSlot(QTreeWidgetItem* item, int column)
{
	/*电压配置,电流配置,电阻配置,版本配置,诊断故障码配置可以更改*/
	/*第0列和第2列不可以编辑*/
	QString parentKey;
	QString&& currentValue = ITEM_TO_STR(item, column);
	if (item->parent())
	{
		parentKey = ITEM_TO_STR(item->parent(), 0);
	}

	if ((!column || (column == 2)) && (!item->parent() ? true :
		(parentKey != "电压配置" && parentKey != "电流配置"
			&& parentKey != "电阻配置" && parentKey != "版本配置"
			&& parentKey != "诊断故障码配置")))
	{
		return;
	}

	m_currentConfigValue = ITEM_TO_STR(item, column);
	ui.configTree->openPersistentEditor(item, column);
	m_currentConfigItem = item;
	m_currentConfigColumn = column;
	m_configItemOpen = true;
}

void SettingDlg::configTreeItemChangedSlot(QTreeWidgetItem* item, int column)
{
	QTreeWidgetItem* parentItem = item->parent();

	QString&& parentKey = ITEM_TO_STR(parentItem, 0);
	QString&& parentValue = ITEM_TO_STR(parentItem, 1);
	QString&& currentKey = ITEM_TO_STR(item, 0);
	QString&& currentVal = ITEM_TO_STR(item, 1);

	QStringList oneKeyList = { "设备配置","硬件配置","继电器配置","范围配置","阈值配置","按键电压配置","静态电流配置","启用配置" };

	QStringList twoKeyList = { "图像配置","电压配置","电流配置","电阻配置","版本配置","诊断故障码配置" };

	bool (JsonTool:: * setValue1Fnc[])(const QString&, const QString&) = {
		&JsonTool::setDeviceConfigValue,&JsonTool::setHardwareConfigValue,
		&JsonTool::setRelayConfigValue,&JsonTool::setRangeConfigValue,
		&JsonTool::setThresholdConfigValue,&JsonTool::setKeyVolConfigValue,
		&JsonTool::setStaticConfigValue,&JsonTool::setEnableConfigValue
	};

	bool (JsonTool:: * setValue2Fnc[])(const QString&, const QString&, const QString&) = {
		&JsonTool::setImageConfigValue,&JsonTool::setVoltageConfigValue,
		&JsonTool::setCurrentConfigValue,&JsonTool::setResConfigValue,
		&JsonTool::setVerConfigValue,&JsonTool::setDtcConfigValue
	};

	void (JsonTool:: * setKeyFnc[])(const QString&, const QString&) = {
		&JsonTool::setImageConfigKey,&JsonTool::setVoltageConfigKey,
		&JsonTool::setCurrentConfigKey,&JsonTool::setResConfigKey,
		&JsonTool::setVerConfigKey,&JsonTool::setDtcConfigKey
	};

	bool success = true;
	if (!parentItem->parent())
	{
		bool setKey = false;
		for (int i = 0; i < twoKeyList.size(); i++)
		{
			if (parentKey == twoKeyList[i])
			{
				setKey = true;
				(m_jsonTool->*setKeyFnc[i])(m_currentConfigValue, currentKey);
				break;
			}
		}

		if (!setKey)
		{
			for (int i = 0; i < oneKeyList.size(); i++)
			{
				if (parentKey == oneKeyList[i])
				{
					/*更新提醒,RESTART优先级2,RECONNECT优先级1,NO优先级0*/
					if (parentKey == oneKeyList[0])
					{
						m_updateWarn = UpdateWarn::UW_RESTART;
					}
					else if (parentKey == oneKeyList[1])
					{
						if (m_updateWarn != UW_RESTART)
							m_updateWarn = UpdateWarn::UW_RECONNECT;
					}
					else
					{
						if (m_updateWarn != UW_RESTART || m_updateWarn != UW_RECONNECT)
							m_updateWarn = UpdateWarn::UW_NO;
					}

					if (!(m_jsonTool->*setValue1Fnc[i])(currentKey, currentVal))
					{
						success = false;
					}
					break;;
				}
			}
		}
	}
	else
	{
		QString&& grandpaKey = ITEM_TO_STR(parentItem->parent(), 0);
		for (int i = 0; i < twoKeyList.size(); i++)
		{
			if (grandpaKey == twoKeyList[i])
			{
				if (!(m_jsonTool->*setValue2Fnc[i])(parentKey, currentKey, currentVal))
				{
					success = false;
				}
				if (m_updateWarn != UW_RESTART || m_updateWarn != UW_RECONNECT)
					m_updateWarn = UpdateWarn::UW_NO;
				break;
			}
		}
	}

	if (!success)
	{
		QMessageBoxEx::warning(this, "错误", m_jsonTool->getLastError());
		item->setData(column, Qt::EditRole, m_currentConfigValue);
	}
	ui.configTree->closePersistentEditor(item, column);
	m_configItemOpen = false;
	m_currentConfigItem = nullptr;
}

void SettingDlg::addCanTableItemSlot(const char* type, const MsgNode& msg)
{
	static ulong number = 0;
	int rowCount = ui.canTable->rowCount();
	ui.canTable->insertRow(rowCount);
	ui.canTable->setItem(rowCount, 0, new QTableWidgetItem({ QString::number(++number) }));
	ui.canTable->setItem(rowCount, 1, new QTableWidgetItem({ type }));
	ui.canTable->setItem(rowCount, 2, new QTableWidgetItem({ Misc::getCurrentTime() }));
	ui.canTable->setItem(rowCount, 3, new QTableWidgetItem({ QString::number(msg.id,16) }));
	ui.canTable->setItem(rowCount, 4, new QTableWidgetItem({ "数据帧" }));
	ui.canTable->setItem(rowCount, 5, new QTableWidgetItem({ msg.bExtFrame ? "拓展帧" : "标准帧" }));
	ui.canTable->setItem(rowCount, 6, new QTableWidgetItem({ QString::number(msg.iDLC) }));
	ui.canTable->setItem(rowCount, 7, new QTableWidgetItem({Q_SPRINTF("%02x %02x %02x %02x %02x %02x %02x %02x",
	msg.ucData[0],msg.ucData[1],msg.ucData[2],msg.ucData[3],msg.ucData[4],msg.ucData[5],msg.ucData[6],msg.ucData[7])}));
	ui.canTable->scrollToBottom();
}

void SettingDlg::canBaseSendSlot()
{
	do 
	{
		memset(&m_msg, 0x00, sizeof(MsgNode));
		bool convert = false;
		m_msg.iDLC = 8;
		m_msg.bExtFrame = ui.canFrameType->currentText() == "拓展帧";
		m_msg.bRemFrame = ui.canFrameFormat->currentText() == "远程帧";
		m_msg.id = ui.canFrameId->text().toInt(&convert, 16);
		if (!convert)
		{
			QMessageBoxEx::warning(this, "错误", "帧ID不为16进制");
			break;
		}

		QStringList datas = ui.canDataEdit->text().split(" ", QString::SkipEmptyParts);
		if (datas.size() != 8)
		{
			QMessageBoxEx::warning(this, "错误", "数据格式错误");
			break;
		}

		int i = 0;
		for (; i < datas.size(); i++)
		{
			m_msg.ucData[i] = datas[i].toInt(&convert, 16);
			if (!convert)
			{
				break;
			}
		}

		if (!convert)
		{
			QMessageBoxEx::warning(this, "错误", QString("数据%1不为16进制").arg(i + 1));
			break;
		}

		int sendCount = ui.canSendCount->text().toInt(&convert);
		if (!convert)
		{
			QMessageBoxEx::warning(this, "错误", "发送次数不为整数");
			break;
		}

		int delay = ui.canSendDelay->text().toInt(&convert);
		if (!convert)
		{
			QMessageBoxEx::warning(this, "错误", "时间间隔不为整数");
			break;
		}
		ui.canBaseSend->setEnabled(false);
		Dt::Base::getCanSender()->AddMsg(m_msg, delay, ST_Event, sendCount);
		Dt::Base::getCanSender()->Start();

		m_canBaseSendTimer.start(delay * sendCount);
	} while (false);
}

void SettingDlg::canBaseStopSlot()
{
	if (m_canBaseSendTimer.isActive())
	{
		Dt::Base::getCanSender()->DeleteOneMsg(m_msg.id);
		m_canBaseSendTimer.stop();
		ui.canBaseSend->setEnabled(true);
	}
}

void SettingDlg::updateImageSlot(const QImage& image)
{
	ui.label->setPixmap(QPixmap::fromImage(image));
}

void SettingDlg::canStartupSlot()
{
	if (!m_canThreadStart)
	{
		ui.canStartup->setText("停止");
		Dt::Base::getCanConnect()->StartReceiveThread();
	}
	else
	{
		ui.canStartup->setText("开始");
		Dt::Base::getCanConnect()->EndReceiveThread();
	}
	m_canThreadStart = !m_canThreadStart;
}

void SettingDlg::startCaptureSlot()
{
	if (m_startCapture) return;
	m_startCapture = true;
	connect(static_cast<Dt::Base*>(m_basePointer), &Dt::Base::updateImageSignal, this, &SettingDlg::updateImageSlot);
}

void SettingDlg::stopCaptureSlot()
{
	if (!m_startCapture) return;
	m_startCapture = false;
	disconnect(static_cast<Dt::Base*>(m_basePointer), &Dt::Base::updateImageSignal, this, &SettingDlg::updateImageSlot);
}

void SettingDlg::saveCoordSlot()
{
	QVector<QPoint> start, end;
	ui.label->getCoordinate(&start, &end);
	if (start.size() != 4 || end.size() != 4)
	{
		QMessageBoxEx::warning(this, "提示", "坐标数量必须为4个坐标");
		return;
	}

	QStringList smallRectList = { "前小图矩形框","后小图矩形框","左小图矩形框","右小图矩形框" };
	for (int i = 0; i < SMALL_RECT_; i++)
	{
		m_jsonTool->setImageConfigValue(smallRectList[i], "X坐标", QString::number(start[i].x()));
		m_jsonTool->setImageConfigValue(smallRectList[i], "Y坐标", QString::number(start[i].y()));
		m_jsonTool->setImageConfigValue(smallRectList[i], "宽", QString::number(end[i].x() - start[i].x()));
		m_jsonTool->setImageConfigValue(smallRectList[i], "高", QString::number(end[i].y() - start[i].y()));
	}
	QMessageBoxEx::information(this, "提示", QString("保存%1").arg(m_jsonTool->initInstance(true) ? "成功" : "失败"));
}

void SettingDlg::setLastError(const QString& error)
{
	m_lastError = error;
}

bool SettingDlg::initConfigTreeWidget()
{
	bool result = false;
	do
	{
		ui.configTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
		ui.configTree->setHeaderLabels(QStringList{ "键","值" ,"说明" });
		ui.configTree->setColumnCount(3);

		connect(ui.configTree, &QTreeWidget::itemPressed, this, &SettingDlg::configTreeItemPressedSlot);
		connect(ui.configTree, &QTreeWidget::itemDoubleClicked, this, &SettingDlg::configTreeItemDoubleClickedSlot);
		connect(ui.configTree, &QTreeWidget::itemChanged, this, &SettingDlg::configTreeItemChangedSlot);

		QList<QTreeWidgetItem**>treeRootList;

		QTreeWidgetItem* parentDeviceConfig,
			* parentHardwareConfig, 
			* parentRelayConfig, 
			* parentRangeConfig,
			* parentThresholdConfig, 
			* parentImageConfig, 
			* parentKeyVolConfig, 
			* parentVoltageConfig,
			* parentCurrentConfig,
			* parentResConfig,
			* parentStaticConfig, 
			* parentVersionConfig,
			* parentDtcConfig,
			* parentEnableConfig;

		treeRootList.append(&parentDeviceConfig);
		treeRootList.append(&parentHardwareConfig);
		treeRootList.append(&parentRelayConfig);
		treeRootList.append(&parentRangeConfig);
		treeRootList.append(&parentThresholdConfig);
		treeRootList.append(&parentImageConfig);
		treeRootList.append(&parentKeyVolConfig);
		treeRootList.append(&parentVoltageConfig);
		treeRootList.append(&parentCurrentConfig);
		treeRootList.append(&parentResConfig);
		treeRootList.append(&parentStaticConfig);
		treeRootList.append(&parentVersionConfig);
		treeRootList.append(&parentDtcConfig);
		treeRootList.append(&parentEnableConfig);

		QList<QTreeWidgetItem*> rootList;
		for (int i = 0; i < treeRootList.size(); i++)
		{
			*treeRootList[i] = new(std::nothrow) QTreeWidgetItem({ m_jsonTool->getAllMainKey()[i] });
			if (!*treeRootList[i])
			{
				setLastError(QString("%1,分配内存失败").arg(m_jsonTool->getAllMainKey()[i]));
				break;
			}
			(*treeRootList[i])->setIcon(0, QIcon(":/images/Resources/images/store.ico"));
			rootList.append(*treeRootList[i]);
		}

		/*父级目录*/
		ui.configTree->addTopLevelItems(rootList);

		/************************************************************************/
		/* Function1                                                            */
		/************************************************************************/
		/*返回临时变量*/
		const int(JsonTool:: * getCount1Fnc[])() = {
			&JsonTool::getDeviceConfigCount,
			&JsonTool::getHardwareConfigCount,
			&JsonTool::getRelayConfigCount,
			&JsonTool::getRangeConfigCount,
			&JsonTool::getThresholdConfigCount,
			&JsonTool::getKeyVolConfigCount,
			&JsonTool::getStaticConfigCount,
			&JsonTool::getEnableConfigCount
		};

		const QStringList&(JsonTool:: * getKey1Fnc[])() = {
			&JsonTool::getDeviceConfigKeyList,
			&JsonTool::getHardwareConfigKeyList,
			&JsonTool::getRelayConfigKeyList,
			&JsonTool::getRangeConfigKeyList,
			&JsonTool::getThresholdConfigKeyList,
			&JsonTool::getKeyVolConfigKeyList,
			&JsonTool::getStaticConfigKeyList,
			&JsonTool::getEnableConfigKeyList
		};

		/*返回临时变量*/
		const QString(JsonTool:: * getValue1Fnc[])(const QString & key) = {
			&JsonTool::getDeviceConfigValue,
			&JsonTool::getHardwareConfigValue,
			&JsonTool::getRelayConfigValue,
			&JsonTool::getRangeConfigValue,
			&JsonTool::getThresholdConfigValue,
			&JsonTool::getKeyVolConfigValue,
			&JsonTool::getStaticConfigValue,
			&JsonTool::getEnableConfigValue
		};

		const QStringList&(JsonTool:: * getExplain1Fnc[])() = {
			&JsonTool::getDeviceConfigExplain,
			&JsonTool::getHardwareConfigExplain,
			&JsonTool::getRelayConfigExplain,
			&JsonTool::getRangeConfigExplain,
			&JsonTool::getThresholdConfigExplain,
			&JsonTool::getKeyVolConfigExplain,
			&JsonTool::getStaticConfigExplain,
			&JsonTool::getEnableConfigExplain
		};

		QList<QTreeWidgetItem*> getParent1List = {
			parentDeviceConfig,
			parentHardwareConfig,
			parentRelayConfig,
			parentRangeConfig,
			parentThresholdConfig,
			parentKeyVolConfig,
			parentStaticConfig,
			parentEnableConfig
		};

		for (int i = 0; i < getParent1List.size(); i++)
		{
			QList<QTreeWidgetItem*> childList;
			for (int j = 0; j < (m_jsonTool->*getCount1Fnc[i])(); j++)
			{
				childList.append(new QTreeWidgetItem({ (m_jsonTool->*getKey1Fnc[i])().value(j) }));
				childList[j]->setIcon(0, QIcon(":/images/Resources/images/key.ico"));
				childList[j]->setIcon(1, QIcon(":/images/Resources/images/file.ico"));
				childList[j]->setIcon(2, QIcon(":/images/Resources/images/msg.ico"));
				childList[j]->setText(1, (m_jsonTool->*getValue1Fnc[i])((m_jsonTool->*getKey1Fnc[i])().value(j)));
				childList[j]->setText(2, (m_jsonTool->*getExplain1Fnc[i])().value(j));
			}
			getParent1List[i]->addChildren(childList);
		}

		/************************************************************************/
		/* Function2                                                            */
		/************************************************************************/
		QList<QTreeWidgetItem*>getParent2List = {
			parentImageConfig,
			parentVoltageConfig,
			parentCurrentConfig,
			parentResConfig,
			parentVersionConfig,
			parentDtcConfig
		};

		const int (JsonTool:: * getCount2Fnc[])() = {
			&JsonTool::getImageConfigCount,
			&JsonTool::getVoltageConfigCount,
			&JsonTool::getCurrentConfigCount,
			&JsonTool::getResConfigCount,
			&JsonTool::getVerConfigCount,
			&JsonTool::getDtcConfigCount
		};

		/*返回临时遍历主键*/
		const QStringList(JsonTool:: * getParentKey2Fnc[])() = {
			&JsonTool::getParentImageKeyList,
			&JsonTool::getParentVoltageConfigKeyList,
			&JsonTool::getParentCurrentConfigKeyList,
			&JsonTool::getParentResConfigKeyList,
			&JsonTool::getParentVerConfigKeyList,
			&JsonTool::getParentDtcConfigKeyList
		};

		const QStringList&(JsonTool:: * getChildKey2Fnc[])() = {
			&JsonTool::getChildImageKeyList,
			&JsonTool::getChildVoltageConfigKeyList,
			&JsonTool::getChildCurrentConfigKeyList,
			&JsonTool::getChildResConfigKeyList,
			&JsonTool::getChildVerConfigKeyList,
			&JsonTool::getChildDtcConfigKeyList
		};

		/*返回临时变量*/
		const QString(JsonTool:: * getValue2Fnc[])(const QString & key, const QString & value) = {
			&JsonTool::getImageConfigValue,
			&JsonTool::getVoltageConfigValue,
			&JsonTool::getCurrentConfigValue,
			&JsonTool::getResConfigValue,
			&JsonTool::getVerConfigValue,
			&JsonTool::getDtcConfigValue
		};

		const QStringList&(JsonTool:: * getExplain2Fnc[])() = {
			&JsonTool::getImageConfigExplain,
			&JsonTool::getVoltageConfigExplain,
			&JsonTool::getCurrentConfigExplain,
			&JsonTool::getResConfigExplain,
			&JsonTool::getVerConfigExplain,
			&JsonTool::getDtcConfigExplain
		};

		for (int i = 0; i < getParent2List.size(); i++)
		{
			QList<QTreeWidgetItem*> parentList;
			for (int j = 0; j < (m_jsonTool->*getCount2Fnc[i])(); j++)
			{
				m_jsonTool->setChildImageKeyListSubscript(j);
				parentList.append(new QTreeWidgetItem({ (m_jsonTool->*getParentKey2Fnc[i])()[j] }));
				QList<QTreeWidgetItem*> childList;
				for (int k = 0; k < (m_jsonTool->*getChildKey2Fnc[i])().count(); k++)
				{
					childList.append(new QTreeWidgetItem({ (m_jsonTool->*getChildKey2Fnc[i])()[k] }));
					childList.at(k)->setText(1, (m_jsonTool->*getValue2Fnc[i])((m_jsonTool->*getParentKey2Fnc[i])()[j],
						(m_jsonTool->*getChildKey2Fnc[i])()[k]));
					childList.at(k)->setText(2, (m_jsonTool->*getExplain2Fnc[i])()[k]);
					childList.at(k)->setIcon(0, QIcon(":/images/Resources/images/key.ico"));
					childList.at(k)->setIcon(1, QIcon(":/images/Resources/images/file.ico"));
					childList.at(k)->setIcon(2, QIcon(":/images/Resources/images/msg.ico"));
				}
				parentList.at(j)->addChildren(childList);
				parentList.at(j)->setIcon(0, QIcon(":/images/Resources/images/tree.ico"));
			}
			getParent2List[i]->addChildren(parentList);
		}
		result = true;
	} while (false);
	return result;
}

bool SettingDlg::initCanTableWidget()
{
	/*CAN表格初始化*/
	ui.canTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	ui.canTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	ui.canTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.canTable->setSelectionMode(QAbstractItemView::SingleSelection);

	ui.canTable->setColumnWidth(0, 80);
	ui.canTable->setColumnWidth(1, 60);
	ui.canTable->setColumnWidth(3, 60);
	ui.canTable->setColumnWidth(4, 60);
	ui.canTable->setColumnWidth(5, 60);
	ui.canTable->setColumnWidth(6, 60);
	ui.canTable->setColumnWidth(7, 150);

	qRegisterMetaType<MsgNode>("MsgNode");
	connect(this, &SettingDlg::addCanTableItemSignal, this, &SettingDlg::addCanTableItemSlot);
	ui.canTable->verticalHeader()->setHidden(true);

	Dt::Base::getCanConnect()->SetDynamicDisplay([&](const char* type, const MsgNode& msg)->void {emit addCanTableItemSignal(type, msg); Sleep(10); });

	connect(ui.canBaseSend, &QPushButton::clicked, this, &SettingDlg::canBaseSendSlot);

	connect(ui.canBaseStop, &QPushButton::clicked, this, &SettingDlg::canBaseStopSlot);

	connect(&m_canBaseSendTimer, &QTimer::timeout, this, [&]()->void {ui.canBaseSend->setEnabled(true); m_canBaseSendTimer.stop(); });

	return true;
}

bool SettingDlg::initAboutWidget()
{
	ui.frameVersion->setText(m_jsonTool->getLibrayVersion());
	ui.fileVersion->setText(m_jsonTool->getJsonFileVersion());
	ui.appVersion->setText(Misc::getAppVersion());
	return true;
}
