#pragma once

/*
* MainDlg.h这个文件是整个程序的入口
*/

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
#include "UpdateDlg.h"

/*
* @NEW_MAIN_DLG,分配一个对话框
* @param1,继承Dt::Base的线程
*/
#define NEW_MAIN_DLG(THREAD)\
(NO_THROW_NEW MainDlg(NO_THROW_NEW THREAD))->show()


/*
* @RUN_MAIN_FNC,运行主函数
* @param1,继承Dt::Base的线程
*/
#define RUN_MAIN_FNC(THREAD)\
int main(int argc,char* argv[])\
{\
QApplication a(argc,argv);\
NEW_MAIN_DLG(THREAD);\
return a.exec();\
}

/*
* @MainDlg,主界面对话框
*/
class MainDlg : public QWidget
{
	Q_OBJECT
public:
	/*
	* @MainDlg,主对话框构造
	* @param1,检测基类指针
	* @param2,控件父类
	*/
	MainDlg(Dt::Base* thread, QWidget* parent = nullptr);

	/*
	* @~MainDlg,主对话框析构
	*/
	~MainDlg();

	/*
	* @initInstance,初始化实例
	* @return,bool
	*/
	bool initInstance();

	/*
	* @getLastError,获取最终错误
	* @return,QString
	*/
	const QString& getLastError();

public slots:
	/*
	* @setScanCodeDlgSlot,设置扫码对话框槽
	* @param1,是否显示
	* @return,vid
	*/
	void setScanCodeDlgSlot(bool show);

	/*
	* @setUnlockDlgSlot,设置解锁对话框槽
	* @param1,是否显示
	* @return,void
	*/
	void setUnlockDlgSlot(bool show);

	/*
	* @setAuthDlgSlot,设置认证对话框槽
	* @param1,结果指针
	* @return,void
	*/
	void setAuthDlgSlot(bool* result);

	/*
	* @setDownloadDlgSlot,设置下载对话框槽
	* @param1,下载信息结构体指针
	* @return,void
	*/
	void setDownloadDlgSlot(BaseTypes::DownloadInfo* info);

	/*
	* @settingButtonSlot,设置按钮槽
	* @return,void
	*/
	void settingButtonSlot();

	/*
	* @connectButtonSlot,连接按钮槽
	* @return,void
	*/
	void connectButtonSlot();

	/*
	* @exitButtonSlot,退出按钮槽
	* @return,void
	*/
	void exitButtonSlot();

	/*
	* @setMessageBoxSlot,设置消息对话框
	* @notice,子线程发射信号到主线程所使用
	* @param1,标题
	* @param2,文本
	* @return,void
	*/
	void setMessageBoxSlot(const QString& title, const QString& text);

	/*
	* @setMessageBoxSlot,设置消息对话框
	* @notice,子线程发射信号到主线程所使用
	* @param1,标题
	* @param2,文本
	* @param3,坐标
	* @return,void
	*/
	void setMessageBoxExSlot(const QString& title, const QString& text, const QPoint& point);

	/*
	* @setQuestionBoxSlot,设置询问对话框
	* @notice,子线程发射信号到主线程所使用
	* @param1,标题
	* @param2,文本
	* @param3,结果
	* @return,void
	*/
	void setQuestionBoxSlot(const QString& title, const QString& text, bool* result);

	/*
	* @setQuestionBoxSlot,设置询问对话框
	* @notice,子线程发射信号到主线程所使用
	* @param1,标题
	* @param2,文本
	* @param3,结果
	* @param4,在recordList中的坐标
	* @return,void
	*/
	void setQuestionBoxExSlot(const QString& title, const QString& text, bool* result, const QPoint& point);


	/*
	* @setPlayQuestionBoxSlot,设置播放询问对话框
	* @notice,子线程发射信号到主线程所使用
	* @param1,标题
	* @param2,文本
	* @param3,结果
	* @param4,在recordList中的坐标
	* @return,void
	*/
	void setPlayQuestionBoxSlot(const QString& title, const QString& text, int* result, const QPoint& point);

	/*
	* @setCurrentStatusSlot,设置当前状态槽
	* @param1,当前状态内容
	* @param2,是否为系统状态
	* @return,void
	*/
	void setCurrentStatusSlot(const QString& status, bool systemStatus);

	/*
	* @setTestResultSlot,设置测试结果槽
	* @param1,测试结果枚举
	* @return,void
	*/
	void setTestResultSlot(const BaseTypes::TestResult& result);

	/*
	* @addListItemSlot,添加列表项目槽
	* @param1,项目内容
	* @param2,是否为日志项目
	* @return,void
	*/
	void addListItemSlot(const QString& item, bool logItem);

	/*
	* @clearListItemSlot,清除列表项目槽
	* @return,void
	*/
	void clearListItemSlot();

	/*
	* @updateImageSlot,更新图像槽
	* @param1,图像
	* @return,void
	*/
	void updateImageSlot(const QImage& image);

	/*
	* @coordinateSlot,坐标槽
	* @param1,videoLabel中的坐标
	* @return,void
	*/
	void coordinateSlot(const QPoint& point);

	/*
	* @usageRateTimerSlot,使用率定时器槽
	* @return,void
	*/
	void usageRateTimerSlot();

	/*
	* @updateSfrSlot,更新解像度槽
	* @return,void
	*/
	void updateSfrSlot();

	/*
	* @restartSlot,重启槽
	* @param1,程序名
	* @return,void
	*/
	void restartSlot(const QString& name);
protected:
	/*
	* @closeEvent,重写关闭事件
	* @param1,关闭事件
	* @return,void
	*/
	virtual void closeEvent(QCloseEvent* event);

	/*
	* @setLastError,设置错误
	* @param1,错误内容
	* @return,void
	*/
	void setLastError(const QString& error);
private:
	//主对话框控件类
	Ui::MainDlgClass ui;

	//检测基类
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

	/*更新对话框*/
	UpdateDlg* m_updateDlg = nullptr;

	/*保存错误*/
	QString m_lastError = "No Error";

	/*使用率定时器*/
	QTimer m_usageRateTimer;

	/*是否存在设置对话框*/
	bool m_isExistSettingDlg = false;

	/*是否已连接*/
	bool m_connected = false;
};
