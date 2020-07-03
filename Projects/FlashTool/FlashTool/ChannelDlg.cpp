#include "ChannelDlg.h"

ChannelDlg::ChannelDlg(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_burnTimer = new(std::nothrow) QTimer;
	if (m_burnTimer)
	{
		connect(m_burnTimer, &QTimer::timeout, this, &ChannelDlg::burnTimerTimeoutSlot);
	}
	//this->ui.groupBox->setStyleSheet("background-color:transparent;");
}

ChannelDlg::~ChannelDlg()
{
	if (m_burnTimer)
	{
		delete m_burnTimer;
		m_burnTimer = nullptr;
	}
}

void ChannelDlg::setGroupTitle(const int& id,const quint32& sn)
{
	m_channelId = id;
	m_channelSn = sn;

	ui.groupBox->setTitle(QString("通道:%1 序列号:%2").arg(m_channelId).arg(m_channelSn));
}

void ChannelDlg::setGroupTitle(const QString& title)
{
	ui.groupBox->setTitle(QString("通道%1 序列号:%2 异常:%3").arg(m_channelId).arg(m_channelSn).arg(title));
}

void ChannelDlg::restoreGroupTitle()
{
	ui.groupBox->setTitle(QString("通道:%1 序列号:%2").arg(m_channelId).arg(m_channelSn));
}

void ChannelDlg::updateCurrentStatusSlot(const QString& status)
{
	ui.currentStatus->setText(QString().sprintf("%-8s", status.toStdString().c_str()));
}

void ChannelDlg::updateBurnStatusSlot(const burnStatus_t& status, const QString& err)
{
	QString text = "",style = "";
	switch (status)
	{
	case BurnStatus::BS_WR:
		text = "WR";
		style = "background-color:rgb(255,255,0);";
		restoreGroupTitle();
		break;
	case BurnStatus::BS_RD:
		text = "RD";
		style = "background-color:rgb(255,255,0);";
		break;
	case BurnStatus::BS_OK:
		text = "OK";
		style = "background-color:rgb(0,255,0);";
		break;
	case BurnStatus::BS_NG:
		text = "NG";
		style = "background-color:rgb(255,0,0);";
		setGroupTitle(err);
		break;
	case BurnStatus::BS_NONE:
		style = "background-color:rgb(0,0,0);";
		break;
	default:
		style = "background-color:rgb(0,0,0);";
		break;
	}
	ui.burnStatus->setText(text);
	ui.burnStatus->setStyleSheet(style + "color:rgb(0,0,0);");
}

void ChannelDlg::updateGroupTitleSlot(const QString& title)
{
	setGroupTitle(title);
}

void ChannelDlg::setBurnTimerRunSlot(bool go)
{
	if (go)
	{
		m_burnTimerTime = 0;
		m_burnTimer->start(1000);
	}
	else
	{
		emit getBurnTimerTimeSignal(m_burnTimerTime);
		m_burnTimer->stop();
	}
}

void ChannelDlg::burnTimerTimeoutSlot()
{
	ui.burnTime->setText(QString().sprintf("%-4d 秒",++m_burnTimerTime));
}

void ChannelDlg::updateProgressSlot(const int& progress)
{
	ui.progressBar->setValue(progress);
}