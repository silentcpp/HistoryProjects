#pragma once

#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include "JsonTool.h"
#include "GeneratedFiles/ui_SettingDlg.h"

#define ITEM_TO_STR(I,N) I->data(N, Qt::EditRole).toString()

class SettingDlg : public QWidget
{
	Q_OBJECT
public:
	SettingDlg(QWidget *parent = Q_NULLPTR);

	~SettingDlg();

	const QString& getLastError();

	bool setAuthDlg(const int& flag = 1);

	bool initInstance();

	void setAppName(const QString& name);

	/************************************************************************/
	/* ≈‰÷√“≥                                                               */
	/************************************************************************/
	void configExpand();

	void configAddNode();

	void configDelNode();

	void configSaveData();

	void configExitDlg();

	void setBasePointer(void* pointer);
public slots:
	/*≈‰÷√“≥øÿº˛*/
	void configTreeItemPressedSlot(QTreeWidgetItem* item, int column);

	void configTreeItemDoubleClickedSlot(QTreeWidgetItem* item, int column);

	void configTreeItemChangedSlot(QTreeWidgetItem* item, int column);

	/*CAN“≥øÿº˛*/
	void addCanTableItemSlot(const char* type, const MsgNode& msg);

	void canBaseSendSlot();

	void canBaseStopSlot();

	void updateImageSlot(const QImage& image);

	void canStartupSlot();

	void startCaptureSlot();

	void stopCaptureSlot();

	void saveCoordSlot();
protected:
	void setLastError(const QString& error);

	bool initConfigTreeWidget();

	bool initCanTableWidget();

	bool initAboutWidget();
signals:
	void setAuthDlgSignal(bool* result, const int& flag);

	void addCanTableItemSignal(const char* type, const MsgNode& msg);
private:
	Ui::SettingDlg ui;

	JsonTool* m_jsonTool = nullptr;

	QString m_lastError = "No Error";

	QString m_name = "Name";

	bool m_configItemOpen = false;

	QTreeWidgetItem* m_currentConfigItem = nullptr;

	QString m_currentConfigValue = "";

	int m_currentConfigColumn = 0;

	enum UpdateWarn {
		UW_NO,
		UW_RESTART,
		UW_RECONNECT,
		UW_EMPTY,
	}m_updateWarn = UW_NO;

	MsgNode m_msg;

	QTimer m_canBaseSendTimer;

	bool m_startCapture = false;

	void* m_basePointer = nullptr;

	bool m_canThreadStart = false;
};
