#include "SettingDlg.h"
#include <QDesktopWidget>
SettingDlg::SettingDlg(QWidget *parent)
	: QWidget(parent)
{
	this->ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	QSize screenSize = QSize(screenRect.width() / 2 + 100, screenRect.height() / 2 + 100);
	this->resize(screenSize);
	qRegisterMetaType<bool*>("bool*");
	initInstance();
}

SettingDlg::~SettingDlg()
{

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
		m_jsonTool = JsonTool::getInstance();
		if (!m_jsonTool)
		{
			setLastError("初始化JsonTool失败");
			break;
		}

		ui.treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
		
		connect(ui.expandAll, &QPushButton::clicked, this, &SettingDlg::expandAllSlot);
		
		connect(ui.saveData, &QPushButton::clicked, this, &SettingDlg::saveDataSlot);
		
		connect(ui.exit, &QPushButton::clicked, this, &SettingDlg::closeSlot);

		connect(ui.addNode, &QPushButton::clicked, this, &SettingDlg::appendFileConfigNodeSlot);
		
		connect(ui.deleteNode, &QPushButton::clicked, this, &SettingDlg::deleteFileConfigNodeSlot);
		
		connect(ui.treeWidget, &QTreeWidget::itemPressed, this, &SettingDlg::itemPressedSlot);
		
		connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &SettingDlg::itemDoubleClickedSlot);
		
		connect(ui.treeWidget, &QTreeWidget::itemChanged, this, &SettingDlg::itemChangedSlot);

		result = true;
	} while (false);
	return result;
}

bool SettingDlg::initTreeWidget()
{
	bool result = false, success = true;
	do 
	{
		QTreeWidgetItem* rootDeviceConfig, *rootHardwareConfig,
			*rootThresholdConfig,*rootRelayConfig,
			*rootFileConfig,*rootUserConfig;

		QList<QTreeWidgetItem**>mainKeyList;
		mainKeyList.push_back(&rootDeviceConfig);
		mainKeyList.push_back(&rootHardwareConfig);
		mainKeyList.push_back(&rootRelayConfig);
		mainKeyList.push_back(&rootThresholdConfig);
		mainKeyList.push_back(&rootUserConfig);
		mainKeyList.push_back(&rootFileConfig);

		for (int i = 0; i < m_jsonTool->getAllMainKey().count(); i++)
		{
			*mainKeyList[i] = new QTreeWidgetItem({ m_jsonTool->getAllMainKey()[i] });
			(*mainKeyList[i])->setIcon(0, QIcon(":/Images/Resources/Images/store.ico"));
			if (!*mainKeyList[i])
			{
				success = false;
				setLastError(QString("%1,分配内存失败").arg(m_jsonTool->getAllMainKey()[i]));
				break;
			}
		}

		if (!success)
		{
			break;
		}
		
		QList<QTreeWidgetItem*> rootList;
		for (int i = 0; i < mainKeyList.size(); i++)
		{
			rootList.push_back(*mainKeyList[i]);
		}

		ui.treeWidget->addTopLevelItems(rootList);

		const int (JsonTool:: * getCountFnc[])() = {
			&JsonTool::getDeviceConfigCount,
			&JsonTool::getHardwareConfigCount,
			&JsonTool::getRelayConfigCount,
			&JsonTool::getThresholdConfigCount,
			&JsonTool::getUserConfigCount 
		};

		const QStringList& (JsonTool:: * getKeyFnc[])() = {
			&JsonTool::getDeviceConfigKeyList,
			&JsonTool::getHardwareConfigKeyList,
			&JsonTool::getRelayConfigKeyList,
			&JsonTool::getThresholdConfigKeyList,
			&JsonTool::getUserConfigKeyList
		};

		const QString(JsonTool:: * getValueFnc[])(const QString&) = {
			&JsonTool::getDeviceConfigValue,
			&JsonTool::getHardwareConfigValue,
			&JsonTool::getRelayConfigValue,
			&JsonTool::getThresholdConfigValue,
			&JsonTool::getUserConfigValue
		};

		const QStringList&(JsonTool:: * getExplainFnc[])() = {
			&JsonTool::getDeviceConfigExplain,
			&JsonTool::getHardwareConfigExplain,
			&JsonTool::getRelayConfigExplain,
			&JsonTool::getThresholdConfigExplain,
			&JsonTool::getUserConfigExplain
		};

		for (int i = 0; i < sizeof(getCountFnc) / sizeof(*getCountFnc); i++)
		{
			QList<QTreeWidgetItem*> childList;
			for (int j = 0; j < (m_jsonTool->*getCountFnc[i])(); j++)
			{
				childList.append(new QTreeWidgetItem({ (m_jsonTool->*getKeyFnc[i])().value(j) }));
				childList.at(j)->setIcon(0, QIcon(":/Images/Resources/Images/key.ico"));
				childList.at(j)->setIcon(1, QIcon(":/Images/Resources/Images/file.ico"));
				childList.at(j)->setIcon(2, QIcon(":/Images/Resources/Images/star.ico"));
				childList.at(j)->setText(1, (m_jsonTool->*getValueFnc[i])((m_jsonTool->*getKeyFnc[i])().value(j)));
				childList.at(j)->setText(2, (m_jsonTool->*getExplainFnc[i])().value(j));
			}
			rootList[i]->addChildren(childList);
		}

		QList<QTreeWidgetItem*>parentFileConfigList;
		for (int i = 0; i < m_jsonTool->getFileConfigCount(); i++)
		{
			QList<QTreeWidgetItem*> childFileConfigList;
			for (int j = 0; j < m_jsonTool->getFileConfigKeyList().count(); j++)
			{
				childFileConfigList.append(new QTreeWidgetItem({ m_jsonTool->getFileConfigKeyList()[j] }));
				childFileConfigList.at(j)->setIcon(0, QIcon(":/Images/Resources/Images/key.ico"));
				childFileConfigList.at(j)->setIcon(1, QIcon(":/Images/Resources/Images/file.ico"));
				childFileConfigList.at(j)->setIcon(2, QIcon(":/Images/Resources/Images/star.ico"));
				childFileConfigList.at(j)->setText(1, m_jsonTool->getFileConfigValue(m_jsonTool->getFileConfigObj().keys()[i],
					m_jsonTool->getFileConfigKeyList()[j]));
				childFileConfigList.at(j)->setText(2, m_jsonTool->getFileConfigExplain().value(j));
				if (m_jsonTool->getFileConfigKeyList()[j] == "烧录模式")
				{
					childFileConfigList.at(j)->setToolTip(2, m_jsonTool->getBurnModeTips());
				}
				if (m_jsonTool->getFileConfigKeyList()[j] == "文件路径")
				{
					childFileConfigList.at(j)->setToolTip(2, m_jsonTool->getFilePathTips());
				}
			}
			parentFileConfigList.append(new QTreeWidgetItem({ m_jsonTool->getFileConfigObj().keys()[i] }));
			parentFileConfigList.at(i)->addChildren(childFileConfigList);
			parentFileConfigList.at(i)->setIcon(0, QIcon(":/Images/Resources/Images/tree.ico"));
			if (!m_jsonTool->getParsedAllFileConfig()[i].valid)
			{
				parentFileConfigList.at(i)->setTextColor(0, Qt::red);
			}
		}
		rootFileConfig->addChildren(parentFileConfigList);

		result = true;
	} while (false);
	return result;
}

bool SettingDlg::appendFileConfigNode()
{
	bool result = false;
	do 
	{
		auto index = ui.treeWidget->findItems("文件配置", Qt::MatchRecursive);
		if (!index.size())
		{
			break;
		}

		QTreeWidgetItem* parent = index.at(0);
		QString nodeName = QString("[请编辑节点名称]:%1").arg(m_jsonTool->getFileConfigCount() + 1);

		QTreeWidgetItem* item = new(std::nothrow) QTreeWidgetItem(parent, { nodeName,"" });
		if (!item)
		{
			break;
		}
		item->setIcon(0, QIcon(":/Images/Resources/Images/tree.ico"));
		QList<QTreeWidgetItem*> itemList;
		QJsonObject object;
		for (int i = 0; i < m_jsonTool->getFileConfigKeyList().count(); i++)
		{
			itemList.append(new QTreeWidgetItem({ m_jsonTool->getFileConfigKeyList()[i],"[参数待编辑]" }));
			if (m_jsonTool->getFileConfigKeyList()[i] == "烧录模式")
			{
				itemList.at(i)->setToolTip(2, m_jsonTool->getBurnModeTips());
			}

			if (m_jsonTool->getFileConfigKeyList()[i] == "文件路径")
			{
				itemList.at(i)->setToolTip(2, m_jsonTool->getFilePathTips());
			}
			itemList.at(i)->setIcon(0, QIcon(":/Images/Resources/Images/key.ico"));
			itemList.at(i)->setIcon(1, QIcon(":/Images/Resources/Images/file.ico"));
			itemList.at(i)->setIcon(2, QIcon(":/Images/Resources/Images/star.ico"));
			itemList.at(i)->setText(2, m_jsonTool->getFileConfigExplain()[i]);
			object.insert(m_jsonTool->getFileConfigKeyList()[i], "[参数待编辑]");
		}
		item->addChildren(itemList);
		m_jsonTool->getFileConfigObj().insert(nodeName, object);
		result = true;
	} while (false);	
	return result;
}

bool SettingDlg::deleteFileConfigNode()
{
	bool result = false;
	do 
	{
		if (!m_currentItem)
		{
			QMessageBoxEx::information(this, "提示", "请选择要删除的文件配置父节点");
			break;
		}

		if (!m_currentItem->parent() ? false : ITEM_TO_STR(m_currentItem->parent(), 0) == "文件配置")
		{
			m_currentItem->parent()->takeChild(ui.treeWidget->currentIndex().row());
			m_jsonTool->getFileConfigObj().remove(ITEM_TO_STR(m_currentItem, 0));
			m_currentItem = ui.treeWidget->currentItem();
		}
		else
		{
			QMessageBoxEx::information(this, "提示", "该操作只能删除文件配置父节点");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool SettingDlg::setAuthDlg()
{
	bool result = false;
	emit setAuthDlgSignal(&result);
	return result;
}


void SettingDlg::itemPressedSlot(QTreeWidgetItem* item, int column)
{
	if (m_itemOpen)
	{
		ui.treeWidget->closePersistentEditor(m_currentItem, m_currentColumn);
		m_itemOpen = false;
	}
	m_currentItem = item;
}

void SettingDlg::itemDoubleClickedSlot(QTreeWidgetItem* item, int column)
{
	QString&& value = ITEM_TO_STR(item, column);

	if (!column && (!item->parent() ? true : ITEM_TO_STR(item->parent(), column) != "文件配置")  || value.isEmpty() || column == 2)
	{
		return;
	}
	ui.treeWidget->openPersistentEditor(item, column);
	m_currentItem = item;
	m_currentValue = value;
	m_currentColumn = column;
	m_itemOpen = true;
}

void SettingDlg::itemChangedSlot(QTreeWidgetItem* item, int column)
{
	QTreeWidgetItem* parent = item->parent();
	bool result = false, success = true;
	do 
	{
		QString&& mainNode = ITEM_TO_STR(parent, 0);
		bool (JsonTool:: * setValueFnc[])(const QString&, const QString&) = {
			&JsonTool::setDeviceConfigValue,
			&JsonTool::setHardwareConfigValue,
			&JsonTool::setRelayConfigValue,
			&JsonTool::setThresholdConfigValue,
			&JsonTool::setUserConfigValue
		};

		bool find = false;
		for (int i = 0; i < m_jsonTool->getAllMainKey().count() - 1; i++)
		{
			if (mainNode == m_jsonTool->getAllMainKey()[i])
			{
				find = true;
				if (!(m_jsonTool->*setValueFnc[i])(ITEM_TO_STR(item, 0), ITEM_TO_STR(item, 1)))
				{
					success = false;
					break;
				}
			}
		}

		if (!success)
		{
			break;
		}

		if (!find)
		{
			if (mainNode == "文件配置")
			{
				if (!m_jsonTool->setFileConfigKey(m_currentValue, ITEM_TO_STR(item, column)))
				{
					break;
				}
			}
			else
			{
				if (parent->parent() && ITEM_TO_STR(parent->parent(), 0) == "文件配置")
				{
					QString&& parentKey = ITEM_TO_STR(parent, 0);
					QString&& childKey = ITEM_TO_STR(item, 0);
					QString&& value = ITEM_TO_STR(item, 1);

					if (!m_jsonTool->setFileConfigValue(parentKey, childKey, value))
					{
						break;
					}
				}
			}
		}
		result = true;
	} while (false);

	/*修改失败还原参数*/
	if (!result)
	{
		QMessageBoxEx::warning(this, "警告", m_jsonTool->getLastError());
		item->setData(column, Qt::EditRole, m_currentValue);
	}
	ui.treeWidget->closePersistentEditor(item, column);
	m_itemOpen = false;
	m_currentItem = nullptr;
}

void SettingDlg::saveDataSlot()
{
	bool result = m_jsonTool->initInstance(true);
	QMessageBoxEx::information(this, "提示", result ? "保存数据成功" : "保存数据失败" + m_jsonTool->getLastError());
	result ? m_jsonTool->getParsedFileConfig(m_typeName) : false;
	m_typeName == SUPER_PASSWORD ? setUpdateTypeName() : false;
	return;
}

void SettingDlg::expandAllSlot()
{
	static bool pressed = true;
	pressed ? ui.treeWidget->expandAll() : ui.treeWidget->collapseAll();
	ui.expandAll->setText(pressed ? "全部收起" : "全部展开");
	pressed = !pressed;
}

void SettingDlg::closeSlot()
{
	this->close();
}

void SettingDlg::appendFileConfigNodeSlot()
{
	appendFileConfigNode();
}

void SettingDlg::deleteFileConfigNodeSlot()
{
	deleteFileConfigNode();
}

void SettingDlg::showEvent(QShowEvent* event)
{
	initTreeWidget();
}

void SettingDlg::setLastError(const QString& err)
{
#ifdef QT_DEBUG
	qDebug() << __FUNCTION__ << err << endl;
#endif
	m_lastError = err;
}

