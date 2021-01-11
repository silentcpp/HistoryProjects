#pragma once
#pragma execution_character_set("utf-8")
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QTimer>
#include <QUrl>
#include <QVector>

enum DownloadResult {
	DR_SUCCESS,
	DR_FAILURE,
	DR_ERROR,
	DR_TIMEOUT,
};

/*下载器类*/
class Downloader : public QObject
{
	Q_OBJECT
public:
	/*构造*/
	Downloader();

	/*析构*/
	~Downloader();

	/*获取最终错误*/
	const QString& getLastError();

	/*获取文件大小*/
	const qint64 getFileSize(const QUrl& url, const int& times = 0);

	/*下载*/
	void download(const QUrl& url);

	/*设置下载超时*/
	void setTimeout(const int& timeout);

	/*设置保存路径*/
	void setSavePath(const QString& savePath);

	/*获取应答*/
	QNetworkReply* getReply();

	/*所用时间*/
	const ulong elapsedTime();

	/*平均网速*/
	const float averageSpeed();
signals:
	/*结果信号*/
	void resultSignal(const DownloadResult& result, const QString& error);

	/*进度信号*/
	void progressSignal(const int& value, const float& speed);
public slots:
	/*完成槽*/
	void finishedSlot(QNetworkReply* reply);

	/*SSL错误槽*/
	void sslErrorsSlot(const QList<QSslError>& errors);

	/*进度槽*/
	void progressSlot(qint64 recvBytes, qint64 totalBytes);

	/*超时槽*/
	void timeoutSlot();
protected:
	/*设置最终错误*/
	void setLastError(const QString& error);

	/*保存文件名*/
	const QString saveFileName(const QUrl& url);

	/*保存到磁盘*/
	bool saveToDisk(const QString& filename, QIODevice* data);
private:
	QString m_lastError = "No Error";

	QNetworkAccessManager m_manager;

	QNetworkReply* m_reply = nullptr;

	QTimer m_timer;

	int m_timeout = 120000;

	ulong m_startTime = 0;

	ulong m_endTime = 0;

	quint64 m_recvBytes = 0;

	QVector<float> m_speedV;

	QString m_savePath = "Downloader";
};

/*应答超时类*/
class QReplyTimeout : public QObject
{
	Q_OBJECT
public:
	QReplyTimeout(QNetworkReply* reply, const int& timeout) : QObject(reply)
	{
		if (reply && reply->isRunning())
		{
			QTimer::singleShot(timeout, this, &QReplyTimeout::onTimeout);
		}
	}
private slots:
	void onTimeout()
	{
		QNetworkReply* reply = static_cast<QNetworkReply*>(parent());
		if (reply->isRunning() && reply->size() == 0)
		{
			reply->abort();
			reply->deleteLater();
			emit timeout();
		}
	}
signals:
	void timeout();
};