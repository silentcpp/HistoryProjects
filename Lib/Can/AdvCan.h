#pragma once

#pragma execution_character_set("utf-8")

#include "CanTransfer.h"

class AdvCan : public CanTransfer
{
public:
    AdvCan();

    ~AdvCan();

    virtual bool open(int baudrate, int extFrame, int device = 0, int port = 0);

	virtual bool close();

    virtual bool clearBuffer();

	virtual bool send(const MsgNode* msg);

	virtual bool multiSend(const MsgNode* msg, int count);

	virtual int receiveProtected(MsgNode* msg, int size, int ms = 200);

private:
    HANDLE m_handle;
};
