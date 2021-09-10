#pragma once
#pragma execution_character_set("utf-8")

#include <PortMgr/PortMgr.h>
#pragma comment(lib, "PortMgr.lib")

#include "CanTransfer.h"

class UartCan : public CanTransfer
{
public:
    UartCan();

	~UartCan();

    virtual bool open(int baudrate, int extframe, int device = 0, int port = 0);

    virtual bool close();

    virtual bool clearBuffer();

    virtual bool send(const MsgNode *msg);

	virtual bool multiSend(const MsgNode* msg, int count);

	virtual int receiveProtected(MsgNode* msg, int size, int ms = 200);

protected:
	void pack(const MsgNode* msg, unsigned char* data, int* length);

	bool unpack(MsgNode* msg, int* length);

	bool checkSumRigth(const unsigned char* data, int length);
private:
    CPortMgr m_portMgr;
};
