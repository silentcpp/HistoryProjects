#include "SerialPort.h"

SerialPort::SerialPort(QObject* parent) : QObject(parent)
{
	m_serialPort = new QSerialPort;
}

SerialPort::~SerialPort()
{
	if (m_serialPort->isOpen())
	{
		m_serialPort->close();
	}

	if (m_serialPort)
	{
		delete m_serialPort;
		m_serialPort = nullptr;
	}
}

QList<QSerialPortInfo> SerialPort::getSerialPortList()
{
	QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
	return availablePorts;
}

bool SerialPort::open(const SerialPortConfig& config)
{
	bool result = false;
	do {

		QString portName = QString::number(config.port);
		portName.insert(0, "COM");

		m_serialPort->setPort(QSerialPortInfo(portName));
		if (!m_serialPort->open(QIODevice::ReadWrite))
		{
			setLastError();
			break;
		}

		if (!setBaud(config.baud))
		{
			setLastError("设置波特率失败");
			break;
		}

		if (!setDataBit(config.dataBit))
		{
			setLastError("设置数据位失败");
			break;
		}

		if (!setVerify(config.verify))
		{
			setLastError("设置校验失败");
			break;
		}

		if (!setStopBit(config.stopBit))
		{
			setLastError("设置停止位失败");
			break;
		}

		if (!setFlowControl(config.flow))
		{
			setLastError("设置流控制失败");
			break;
		}
		connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPort::readData);
		result = true;
	} while (false);
	return result;
}

void SerialPort::close()
{
	if (m_serialPort->isOpen())
	{
		m_serialPort->close();
	}
}

const QStringList& SerialPort::getBaudEnum()
{
	return m_baudEnum;
}

const QStringList& SerialPort::getVerityEnum()
{
	return m_verityEnum;
}

const QStringList& SerialPort::getDataBitEnum()
{
	return m_dataBitEnum;
}

bool SerialPort::setBaud(const int& baud)
{
	bool result = false;
	switch (baud)
	{
	case 1200:result = m_serialPort->setBaudRate(QSerialPort::Baud1200);break;
	case 2400:result = m_serialPort->setBaudRate(QSerialPort::Baud2400);break;
	case 4800:result = m_serialPort->setBaudRate(QSerialPort::Baud4800);break;
	case 9600:result = m_serialPort->setBaudRate(QSerialPort::Baud9600);break;
	case 19200:result = m_serialPort->setBaudRate(QSerialPort::Baud19200);break;
	case 38400:result = m_serialPort->setBaudRate(QSerialPort::Baud38400);break;
	case 57600:result = m_serialPort->setBaudRate(QSerialPort::Baud57600);break;
	case 115200:result = m_serialPort->setBaudRate(QSerialPort::Baud115200);break;
	default:result = false;break;
	}
	return result;
}

bool SerialPort::setDataBit(const int& dataBit)
{
	bool result = false;
	switch (dataBit)
	{
	case 5:result = m_serialPort->setDataBits(QSerialPort::Data5);break;
	case 6:result = m_serialPort->setDataBits(QSerialPort::Data6);break;
	case 7:result = m_serialPort->setDataBits(QSerialPort::Data7);break;
	case 8:result = m_serialPort->setDataBits(QSerialPort::Data8);break;
	default:result = false;break;
	}
	return result;
}

const QStringList& SerialPort::getStopBitEnum()
{
	return m_stopBitEnum;
}

bool SerialPort::setVerify(const int& verify)
{
	bool result = false;
	switch (verify)
	{
	case 0:result = m_serialPort->setParity(QSerialPort::NoParity);break;
	case 2:result = m_serialPort->setParity(QSerialPort::EvenParity);break;
	case 3:result = m_serialPort->setParity(QSerialPort::OddParity);break;
	case 4:result = m_serialPort->setParity(QSerialPort::SpaceParity);break;
	case 5:result = m_serialPort->setParity(QSerialPort::MarkParity);break;
	default:result = false;break;
	}
	return result;
}

bool SerialPort::setStopBit(const int& stopBit)
{
	bool result = false;
	switch (stopBit)
	{
	case 1:result = m_serialPort->setStopBits(QSerialPort::OneStop);break;
	case 2:result = m_serialPort->setStopBits(QSerialPort::TwoStop);break;
	case 3:result = m_serialPort->setStopBits(QSerialPort::OneAndHalfStop);break;
	default:result = false;break;
	}
	return result;
}

bool SerialPort::setFlowControl(const int& flowControl)
{
	bool result = false;
	switch (flowControl)
	{
	case 0:result = m_serialPort->setFlowControl(QSerialPort::NoFlowControl);break;
	case 1:result = m_serialPort->setFlowControl(QSerialPort::HardwareControl);break;
	case 2:result = m_serialPort->setFlowControl(QSerialPort::SoftwareControl);break;
	default:result = false;break;
	}
	return result;
}

QSerialPort* SerialPort::getSerialPort()
{
	return m_serialPort;
}

void SerialPort::setLastError(const QString& e)
{
	if (e.isEmpty())
	{
		m_lastError = QMetaEnum::fromType<QSerialPort::SerialPortError>()
			.valueToKey(m_serialPort->error());
	}
	else
	{
		m_lastError = e;
	}
}

const QString& SerialPort::getLastError()
{
	return m_lastError;
}

qint64 SerialPort::writeData(const QString& data)
{
	QByteArray byte = QByteArray::fromHex(data.toLatin1());
	return m_serialPort->write(byte);
}

void SerialPort::readData()
{
	emit readyReadSignal(m_serialPort->portName(),m_serialPort->readAll());
}
