#pragma once

#include <QtWidgets/QWidget>
#include <QDebug>
#include "GeneratedFiles/ui_MainDlg.h"
#include "SettingDlg.h"
#include "ScanCodeDlg.h"
#include "UnlockDlg.h"
#include "AuthDlg.h"
#include "DownloadDlg.h"
#include "Detection.h"
#include "jqcpumonitor.h"

#define NEW_MAIN_DLG(THREAD)\
(NO_THROW_NEW MainDlg(NO_THROW_NEW THREAD))->show()

#define RUN_MAIN_FNC(THREAD)\
int main(int argc,char* argv[])\
{\
QApplication a(argc,argv);\
NEW_MAIN_DLG(THREAD);\
return a.exec();\
}

class MainDlg : public QWidget
{
	Q_OBJECT
public:
	/*构造*/
	MainDlg(Dt::Base* thread, QWidget* parent = nullptr);

	/*析构*/
	~MainDlg();

	/*初始化实例*/
	bool initInstance();

	/*获取错误*/
	const QString& getLastError();
public slots:
	/*扫码对话框槽*/
	void setScanCodeDlgSlot(bool show);

	/*解锁对话框槽*/
	void setUnlockDlgSlot(bool show);

	/*认证对话框槽*/
	void setAuthDlgSlot(bool* result);

	/*设置下载对话框槽*/
	void setDownloadDlgSlot(BaseTypes::DownloadInfo* info);

	/*设置按钮槽*/
	void settingButtonSlot();

	/*连接按钮槽*/
	void connectButtonSlot();

	/*退出按钮槽*/
	void exitButtonSlot();

	/*普通消息对话框槽*/
	void setMessageBoxSlot(const QString& title, const QString& text);

	void setMessageBoxExSlot(const QString& title, const QString& text, const QPoint& point);

	/*询问对话框槽*/
	void setQuestionBoxSlot(const QString& title, const QString& text, bool* result);

	void setQuestionBoxExSlot(const QString& title, const QString& text, bool* result, const QPoint& point);

	/*设置当前状态槽*/
	void setCurrentStatusSlot(const QString& status, bool systemStatus);

	/*设置结果槽*/
	void setTestResultSlot(const BaseTypes::TestResult& result);

	/*添加列表元素槽*/
	void addListItemSlot(const QString& item, bool logItem);

	/*清除列表元素槽*/
	void clearListItemSlot();

	/*更新图像槽*/
	void updateImageSlot(const QImage& image);

	void coordinateSlot(const QPoint& point);

	void usageRateTimerSlot();

	void updateSfrSlot();
protected:
	/*重写关闭事件*/
	virtual void closeEvent(QCloseEvent* event);

	/*设置错误*/
	void setLastError(const QString& error);
private:
	Ui::MainDlgClass ui;

	Dt::Base* m_base = nullptr;

	/*扫码对话框*/
	ScanCodeDlg* m_scanCodeDlg = nullptr;

	/*解锁对话框*/
	UnlockDlg* m_unlockDlg = nullptr;

	/*认证对话框*/
	AuthDlg* m_authDlg = nullptr;

	/*设置对话框*/
	SettingDlg* m_settingDlg = nullptr;

	/*下载对话框*/
	DownloadDlg* m_downloadDlg = nullptr;

	/*保存错误*/
	QString m_lastError = "No Error";

	/*使用率定时器*/
	QTimer m_usageRateTimer;

	/*是否存在设置对话框*/
	bool m_isExistSettingDlg = false;

	/*是否已连接*/
	bool m_connected = false;
};
