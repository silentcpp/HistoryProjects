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

	bool getResult();

	const ulong getElapsedTime();

	const float getAverageSpeed();

	const float getFileSize();

	const QString& getLastError();

	bool resetNetwork();
protected:
	void setLastError(const QString& error);

	virtual void mousePressEvent(QMouseEvent* event);

	virtual void mouseReleaseEvent(QMouseEvent* event);

	virtual void mouseMoveEvent(QMouseEvent* event);

	virtual bool eventFilter(QObject* obj, QEvent* event);
private slots:
	void resultSlot(const DownloadResult& result, const QString& error);

	void progressSlot(const qint64& receive, const qint64& total, const float& speed);
private:
	Ui::DownloadDlg ui;

	QString m_lastError = "No Error";

	Downloader* m_manager = nullptr;

	DownloadResult m_result = DR_ERROR;

	bool m_isPress = false;

	QPoint m_point;
};
