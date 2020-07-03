#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QStyleFactory>

#include "JsonTool.h"
#include "ScanCodeDlg.h"
#include "ui_MainDlg.h"
#include "ThreadHandler.h"
#include "ChannelDlg.h"
#include "SettingDlg.h"
#include "ChoiceDlg.h"
#include "JQCPUMonitor"
#include "AuthDlg.h"
/************************************************************************/
/* 主界面类                                                             */
/************************************************************************/

class MainDlg : public QWidget
{
	Q_OBJECT
public:
	/*构造*/
	explicit MainDlg(QWidget* parent = nullptr);

	/*析构*/
	~MainDlg();

	/*获取错误信息*/
	const QString& getLastError();

	/*初始化Ui*/
	bool initUi();

	/*初始化*/
	bool initInstance();

	/*初始化CPU监控*/
	bool initCpuMonitor();

	/*创建通道界面*/
	bool createChannelInterface();

	/*删除通道界面*/
	void deleteChannelInterface();

	/*创建没有设备界面*/
	bool createNoDeviceInterface();

	/*删除没有设备界面*/
	void deleteNoDeviceInterface();

	/*禁用启用控件*/
	void enableControl(bool enable);

	/*更新烧录模式控件*/
	void updateBurnModeControl(const int& burnMode);

	/*槽函数*/
public slots:
	/*设置按钮槽*/
	void settingButtonSlot();

	/*连接按钮槽*/
	void connectButtonSlot();

	/*退出按钮槽*/
	void exitButtonSlot();

	/*重新加载设备槽*/
	void reloadButtonSlot();

	/*对话框槽*/
	void setMessageBoxSlot(const QString& title, const QString& text);

	/*扫码对话框槽*/
	void scanCodeDlgSlot(const int& number);

	/*机种名正确槽*/
	void typeNameCorrectSlot(const QString& typeName);

	/*CPU使用率定时器槽函数*/
	void cpuUsageRateTimerSlot();

	void updateTypeNameSlot();
protected:
	/*重写关闭事件*/
	virtual void closeEvent(QCloseEvent* event);

	/*设置错误信息*/
	void setLastError(const QString& err);

	/*删除弹簧控件*/
	void deleteStretch();
private:
	Ui::MainDlg ui;

	JsonTool* m_jsonTool = nullptr;

	/*错误信息*/
	QString m_lastError = "None Error";

	/*线程管理者*/
	ThreadHandler* m_threadHandler = nullptr;

	/*通道界面*/
	ChannelDlg* m_channelInterface = nullptr;

	/*扫码对话框*/
	ScanCodeDlg* m_scanCodeDlg = nullptr;

	/*认证对话框*/
	AuthDlg* m_authDlg = nullptr;

	/*垂直布局用于滑动控件*/
	QVBoxLayout* m_vBoxLayout = nullptr;

	/*用于没有连接设备显示信息*/
	QLabel* m_noDevice = nullptr;

	/*Aardvark 是烧录器的名称,所以此处用它来描述烧录器数量*/
	int m_aardvarkCount = 0;

	/*选择对话框*/
	ChoiceDlg* m_choiceDlg = nullptr;

	/*屏蔽关闭事件*/
	bool m_maskCloseEvent = false;

	/*CPU使用率检测定时器*/
	QTimer* m_cpuUsageRateTimer = nullptr;

	/*屏幕大小*/
	QSize m_screenSize;

	/*机种名*/
	QString m_typeName;

	/**是否正在删除combobox项目*/
	bool m_delComboItem = false;
};