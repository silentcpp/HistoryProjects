#include "UpdateDlg.h"

#include <Windows.h>

#include <ClientCore/DLLExport.h>
#pragma comment(lib,"ClientCore.lib")

using namespace Utility;

UpdateDlg::UpdateDlg(QWidget* parent, const QString& updateLog)
	: QDialog(nullptr),
	m_parent(parent),
	m_updateLog(updateLog)
{
	ui.setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint);

	Utility::Window::setBorderRadius(this);

	QObject::connect(this, &UpdateDlg::setQuestionBoxSignal, this, &UpdateDlg::setQuestionBoxSlot);

	QObject::connect(this, &UpdateDlg::setProgressSignal, this, &UpdateDlg::setProgressSlot);

	QObject::connect(this, &UpdateDlg::setShowDlgSignal, this, &UpdateDlg::setShowDlgSlot);

	QObject::connect(this, &UpdateDlg::setTitleSignal, this, &UpdateDlg::setTitleSlot);

	QObject::connect(ui.abortButton, &QPushButton::clicked, this, [&]() {
		client_core::auto_update_stop_thread(m_client, 1000);
		});

	QString name = getCurrentFileName();
	int index = name.lastIndexOf("[");
	if (index != -1)
		name = name.mid(0, index);
	QByteArray bytes = name.toLocal8Bit();

	m_client = client_core::alloc_client();
	client_core::set_connect_times(m_client, 5);
	client_core::set_start_delay(m_client, 500);
	client_core::auto_update_start_thread(m_client, "www.invomes.com", 10086,
		bytes.data(),
		getAppVersion().toStdString().c_str(),
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

void Utility::UpdateDlg::autoRelease()
{
	setAttribute(Qt::WA_DeleteOnClose);
}

bool UpdateDlg::notifyCallback(bool val, const char* name, void* args)
{
	UpdateDlg* dlg = static_cast<UpdateDlg*>(args);
	if (!val)
	{
		return false;
	}

	QString text;
	if (dlg->m_updateLog.isEmpty())
	{
		text = QString().sprintf("发现新版本\"%s\",\n是否需要更新?",
			QString::fromLocal8Bit(name).toStdString().c_str());
	}
	else
	{
		text = QString("发现新版本\"%1\",是否需要更新?\n本次更新内容:\n%2")
			.arg(QString::fromLocal8Bit(name))
			.arg(dlg->m_updateLog);
	}
	bool result = dlg->setQuestionBox("更新提示", text);

	if (result)
	{
		dlg->setShowDlgSignal(true);
	}
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

	QProcess* process(new QProcess);
	process->setWorkingDirectory(getCurrentDir());

	const QString& cmd = QString("cmd.exe /c start %1").arg(QString::fromLocal8Bit(name));
	process->start(cmd);
	process->waitForStarted();
	QApplication::exit(0);
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
