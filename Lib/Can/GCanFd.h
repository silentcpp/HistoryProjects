#pragma once
#pragma execution_character_set("utf-8")

#include "CanTransfer.h"

class GCanFd : public CanTransfer
{
public:
	GCanFd();

	~GCanFd();

	virtual bool open(int baudrate, int extFrame, int device = 0, int port = 0);
	
	virtual bool close();

	virtual bool clearBuffer();

	virtual bool send(const MsgNode* msg);
	
	virtual bool multiSend(const MsgNode* msg, int count);
	
	virtual int receiveProtected(MsgNode* msg, int size, int ms = 200);

private:
	CRITICAL_SECTION m_cs;
};

