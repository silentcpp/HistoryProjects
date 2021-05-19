#include "UpdateDlg.h"
#include "Types.h"

UpdateDlg::UpdateDlg(QWidget* args, QWidget* parent)
	: QDialog(parent),
	m_parent(args)
{
	setWindowFlags(Qt::FramelessWindowHint);
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	QBitmap bmp(this->size());
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), 20, 20);
	this->setMask(bmp);
	
	QObject::connect(this, &UpdateDlg::setQuestionBoxSignal,
		this, &UpdateDlg::setQuestionBoxSlot);

	QObject::connect(this, &UpdateDlg::setProgressSignal,
		this, &UpdateDlg::setProgressSlot);

	QObject::connect(this, &UpdateDlg::setShowDlgSignal,
		this, &UpdateDlg::setShowDlgSlot);

	QObject::connect(this, &UpdateDlg::setTitleSignal,
		this, &UpdateDlg::setTitleSlot);

	QObject::connect(ui.abortButton, &QPushButton::clicked, this, [&]() {
		client_core::auto_update_stop_thread(m_client, 1000);
		});

	QString name = Misc::getCurrentFileName();
	int index = name.lastIndexOf("[");
	if (index != -1)
		name = name.mid(0, index);
	QByteArray bytes = name.toLocal8Bit();

	m_client = client_core::alloc_client();
	client_core::set_connect_times(m_client, 5);
	client_core::set_start_delay(m_client, 500);
	client_core::auto_update_start_thread(m_client, "www.invomes.com", 10086,
		bytes.data(),
		Q_TO_C_STR(Misc::getAppVersion()),
		notifyCallback,
		progressCallback,
		resultCallback,
		this);

}

UpdateDlg::~UpdateDlg()
{
	client_core::auto_update_stop_thread(m_client, 1000);
	client_core::free_client(&m_client);
}

bool UpdateDlg::notifyCallback(bool val, const char* name, void* args)
{
	UpdateDlg* dlg = static_cast<UpdateDlg*>(args);
	if (!val)
		return false;

	bool result = dlg->setQuestionBox("更新提示",
		Q_SPRINTF("发现新版本\"%s\",\n是否需要更新?", G_TO_C_STR(name)));

	if (result)
		dlg->setShowDlgSignal(true);
	return result;
}

void UpdateDlg::progressCallback(ulong current, ulong total, ulong status, void* args)
{
	static_cast<UpdateDlg*>(args)->setProgressSignal(current, total, status);
}

void UpdateDlg::resultCallback(bool result, const char* name, void* args)
{
	UpdateDlg* dlg = static_cast<UpdateDlg*>(args);
	Sleep(1000);
	dlg->setTitleSignal("更新完成,将自动重启");
	Sleep(1000);
	dlg->setShowDlgSignal(false);

	emit dlg->restartSignal(G_TO_Q_STR(name));
	//QProcess* process(new QProcess);
	//process->setWorkingDirectory(Misc::getCurrentDir());

	//const QString& cmd = QString("cmd.exe /c start %1").arg(QString::fromLocal8Bit(name));
	//process->start(cmd);
	//process->waitForStarted();
	//QApplication::exit(0);
}

bool UpdateDlg::setQuestionBox(const QString& title, const QString& text)
{
	bool result = false;
	emit setQuestionBoxSignal(title, text, &result);
	m_wait = true;
	while (m_wait)
		Sleep(100);
	return result;
}

void UpdateDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPress = true;
		m_point = event->globalPos();
	}
}

void UpdateDlg::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		m_isPress = false;
	}
}

void UpdateDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		int x = event->globalX() - m_point.x();
		int y = event->globalY() - m_point.y();
		m_point = event->globalPos();
		move(this->x() + x, this->y() + y);
	}
}

void UpdateDlg::setQuestionBoxSlot(const QString& title, const QString& text, bool* result)
{
	*result = (QMessageBoxEx::question(m_parent, title, text) == QMessageBoxEx::Yes);
	m_wait = false;
}

void UpdateDlg::setProgressSlot(ulong current, ulong total, ulong status)
{
	if (total)
		ui.progressBar->setValue(((float)current / total) * 100);
}


void UpdateDlg::setShowDlgSlot(bool show)
{
	show ? this->show() : this->close();
}

void UpdateDlg::setTitleSlot(const QString& title)
{
	ui.titleLabel->setText(title);
}
