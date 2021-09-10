#pragma once
#pragma execution_character_set("utf-8")

#include "CanTransfer.h"

class ZlgCan : public CanTransfer
{
public:
    ZlgCan();

    ~ZlgCan();

    virtual bool open(int baudrate, int extframe, int device = 0, int port = 0);

    virtual bool close();

    virtual bool clearBuffer();

	virtual bool send(const MsgNode* msg);

	virtual bool multiSend(const MsgNode* msg, int count);

	virtual int receiveProtected(MsgNode* msg, int size, int ms = 200);

private:
    bool initDevice(void *config);

    CRITICAL_SECTION m_cs;
};
