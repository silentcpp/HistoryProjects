#include "DownloadDlg.h"

DownloadDlg::DownloadDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	installEventFilter(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	connect(&m_manager, &Downloader::progressSignal, this, &DownloadDlg::progressSlot);
	connect(&m_manager, &Downloader::resultSignal, this, &DownloadDlg::resultSlot);
	connect(ui.abortBtn, &QPushButton::clicked, this, [&]() {m_manager.getReply()->abort(); });
}

DownloadDlg::~DownloadDlg()
{
}

void DownloadDlg::download(const QString& title, const QString& url, const QString& path)
{
	ui.progressBar->setValue(0);
	ui.titleLabel->setText(title);
	ui.urlLabel->setText(url);
	m_manager.setSavePath(path);
	m_manager.download(url);
}

bool DownloadDlg::result()
{
	return m_result == DR_SUCCESS;
}

const ulong DownloadDlg::elapsedTime()
{
	return m_manager.elapsedTime();
}

const float DownloadDlg::averageSpeed()
{
	return m_manager.averageSpeed();
}

const QString& DownloadDlg::getLastError()
{
	return m_lastError;
}

void DownloadDlg::setLastError(const QString& error)
{
	m_lastError = error;
}

void DownloadDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPress = true;
		m_point = event->globalPos();
	}
}

void DownloadDlg::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		m_isPress = false;
	}
}

void DownloadDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		int x = event->globalX() - m_point.x();
		int y = event->globalY() - m_point.y();
		m_point = event->globalPos();
		move(this->x() + x, this->y() + y);
	}
}

bool DownloadDlg::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		if (reinterpret_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
		{
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

void DownloadDlg::resultSlot(const DownloadResult& result, const QString& error)
{
	setLastError(error);
	m_result = result;
	this->close();
}

void DownloadDlg::progressSlot(const int& value, const float& speed)
{
	ui.speedLabel->setText(QString().sprintf("%4.2fKb/s", speed));
	ui.progressBar->setValue(value);
}
