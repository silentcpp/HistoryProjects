#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QTimer>
#include "ui_ChannelDlg.h"
#include "ThreadHandler.h"

/************************************************************************/
/* 通道界面类,内部动态增加到滑动窗口控件上                              */
/* 烧录计时控件内部更新,线程中计时器无法使用必须用exec时间循环		    */	
/************************************************************************/

class ChannelDlg : public QWidget
{
	Q_OBJECT
private:
	Ui::ChannelDlg ui;

	/*通道ID*/
	int m_channelId = 0;

	/*烧录器序列号*/
	quint32 m_channelSn = 0;

	/*烧录计时器*/
	QTimer* m_burnTimer = nullptr;

	/*烧录计时器时间*/
	quint32 m_burnTimerTime = 0;
public:
	/*构造*/
	ChannelDlg(QWidget* parent = Q_NULLPTR);

	/*析构*/
	~ChannelDlg();

	/*设置组控件标题*/
	void setGroupTitle(const int& id, const quint32& sn);
	void setGroupTitle(const QString& title);
	void restoreGroupTitle();
signals:
	/*获取烧录计时器时间信号*/
	void getBurnTimerTimeSignal(const int& data);
public slots:
	/*更新进度条槽*/
	void updateProgressSlot(const int& progress);

	/*更新当前状态槽*/
	void updateCurrentStatusSlot(const QString& status);

	/*更新烧录状态槽*/
	void updateBurnStatusSlot(const burnStatus_t& status, const QString& err);

	/*更新组标题*/
	void updateGroupTitleSlot(const QString& title);

	/*设置烧录计时器运行槽*/
	void setBurnTimerRunSlot(bool go);

	/*烧录计时器超时槽*/
	void burnTimerTimeoutSlot();
};