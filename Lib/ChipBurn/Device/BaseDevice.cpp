#include "BaseDevice.h"

BaseDevice::BaseDevice()
{
}

BaseDevice::~BaseDevice()
{

}

bool BaseDevice::isOpened() const
{
	return m_open;
}

int BaseDevice::getPort() const
{
	return m_port;
}

const QString& BaseDevice::getLastError()
{
	return m_lastError;
}

void BaseDevice::setLastError(const QString& error)
{
	m_lastError = error;
}
