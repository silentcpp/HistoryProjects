#pragma once

#include "CanTransfer.h"

#define MAX_CAN_TRANSFER_COUNT 32

class CanFactory {
public:
	static CanTransfer* allocTransfer(const QString& cardName);

	static void freeTransfer(CanTransfer* transfer = nullptr);

	static int getTransferCount();

	static CanTransfer* getTransferValue(int index);

	static int getTransferIndex(const CanTransfer* transfer);

	static QStringList getSupportCan();
protected:
	CanFactory() = default;

	~CanFactory() = default;
private:
	static CanTransfer* m_transfer[MAX_CAN_TRANSFER_COUNT];

	static int m_count;
};
