#include "Can.h"

const char* Can::getVersion()
{
	return "1.0.0.1";
}

QStringList Can::getSupportCan()
{
	return CanFactory::getSupportCan();
}

CanTransfer* Can::allocCanTransfer(const QString& transfer)
{
	return CanFactory::allocTransfer(transfer);
}

void Can::freeCanTransfer(CanTransfer* transfer)
{
	CanFactory::freeTransfer(transfer);
}

int Can::getSupportMaxCanTransferCount()
{
	return MAX_CAN_TRANSFER_COUNT;
}

int Can::getCurrentUsedCanTransferCount()
{
	return CanFactory::getTransferCount();
}

CanTransfer* Can::getCanTransferValue(int index)
{
	return CanFactory::getTransferValue(index);
}

int Can::getCanTransferIndex(const CanTransfer* transfer)
{
	return CanFactory::getTransferIndex(transfer);
}

CanSender* Can::allocCanSender(CanTransfer* transfer)
{
	return new(std::nothrow) CanSender(transfer);
}

void Can::freeCanSender(CanSender*& sender)
{
	if (sender)
	{
		delete sender;
		sender = nullptr;
	}
}
