#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QDebug>
#include <QMetaEnum>
#include <QSerialPort>
#include <QSerialPortInfo>

struct SerialPortConfig {
	int port;

	int baud;

	int verify;

	int dataBit;

	int stopBit;

	int flow;
};

class SerialPort : public QObject
{
	Q_OBJECT
public:
	explicit SerialPort(QObject* parent = nullptr);

	~SerialPort();

	QList<QSerialPortInfo> getSerialPortList();

	bool open(const SerialPortConfig& config);

	void close();

	const QStringList& getBaudEnum();

	const QStringList& getVerityEnum();

	const QStringList& getDataBitEnum();

	const QStringList& getStopBitEnum();

	QSerialPort* getSerialPort();

	const QString& getLastError();

	qint64 writeData(const QString& data);
protected:
	bool setBaud(const int& baud);

	bool setDataBit(const int& dataBit);

	bool setVerify(const int& verify);

	bool setStopBit(const int& stopBit);

	bool setFlowControl(const int& flowControl);
private:
	QSerialPort* m_serialPort = nullptr;

	QString m_lastError = "No Error";

	void setLastError(const QString& e = "");

	const QStringList m_baudEnum = { "1200","2400","4800","9600","19200","38400","57600","115200" };

	const QStringList m_verityEnum = { "NoParity","EvenParity","OddParity","SpaceParity","MarkParity" };

	const QStringList m_dataBitEnum = { "5","6","7","8" };

	const QStringList m_stopBitEnum = { "1","1.5","2" };
signals:
	void readyReadSignal(const QString& portName, const QByteArray& data);
private slots:
	void readData();
};
