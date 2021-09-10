#pragma once
#pragma execution_character_set("utf-8")

#include "CanTransfer.h"

class Kvaser : public CanTransfer
{
public:
    Kvaser();

    ~Kvaser();

    virtual bool open(int baudrate, int extframe, int device = 0, int port = 0);

    virtual bool close();

    virtual bool clearBuffer();

    virtual bool send(const MsgNode *msg);

	virtual bool multiSend(const MsgNode* msg, int count);

	virtual int receiveProtected(MsgNode* pMsg, int size, int ms = 200);

private:
    int m_handle = -1;
};
