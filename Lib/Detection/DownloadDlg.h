#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QDialog>
#include <QMouseEvent>
#include "GeneratedFiles/ui_DownloadDlg.h"
#include "Downloader.h"

class DownloadDlg : public QDialog
{
	Q_OBJECT
public:
	DownloadDlg(QWidget *parent = Q_NULLPTR);

	~DownloadDlg();

	void download(const QString& title, const QString& url, const QString& path);

	bool result();

	const ulong elapsedTime();

	const float averageSpeed();

	const QString& getLastError();
protected:
	void setLastError(const QString& error);

	virtual void mousePressEvent(QMouseEvent* event);

	virtual void mouseReleaseEvent(QMouseEvent* event);

	virtual void mouseMoveEvent(QMouseEvent* event);

	virtual bool eventFilter(QObject* obj, QEvent* event);
private slots:
	void resultSlot(const DownloadResult& result, const QString& error);

	void progressSlot(const int& value, const float& speed);
private:
	Ui::DownloadDlg ui;

	QString m_lastError = "No Error";

	Downloader m_manager;

	DownloadResult m_result = DR_ERROR;

	bool m_isPress = false;

	QPoint m_point;
};
