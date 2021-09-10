#pragma once

#define MAX_SAVE_MSG_COUNT 4096

/************************************************************************/
/* Macro define                                                         */
/************************************************************************/
#define ER_SUCCESS                         0x00000000

// 0x00000001 - 0x0000000f -> CAN error code define
#define ER_CAN_OPEN_DEVICE_ERROR           0x00000001
#define ER_CAN_UNSUPPORTED_BAUDRATE_ERROR  0x00000002
#define ER_CAN_NEED_CONNECT_ERROR          0x00000003
#define ER_CAN_SEND_FAIL_ERROR             0x00000004
#define ER_CAN_RECEIVE_FAIL_ERROR          0x00000005
#define ER_CAN_RECEIVE_NONE_ERROR          0x00000006
#define ER_CAN_RECEIVE_BUFFER_FULL_ERROR   0x00000007
#define ER_CAN_START_RECEIVE_THREAD_ERROR  0x00000008

// 0x00000010 - 0x000000f0 -> CCP error code define
#define ER_CCP_CONNECT_SEND_ERROR          0x00000010
#define ER_CCP_CONNECT_RECEIVE_ERROR       0x00000020
#define ER_CCP_UNLOCK_ERROR                0x00000030
#define ER_CCP_CHECK_SUM_ERROR             0x00000040
#define ER_CCP_NEED_CAN_CONNECT_ERROR      0x00000050
#define ER_CCP_INVALIDATE_ADDRESS_ERROR    0x00000060
#define ER_CCP_CLEAR_FLASH_ERROR           0x00000070

// 0x00000100 - 0x00000f00 -> Image transfer error code define
#define ER_IMAGE_TRANS_INVALIDATE_SIZE_ERROR  0x00000100
#define ER_IMAGE_TRANS_REPEATED_INDEX_ERROR   0x00000200
#define ER_IMAGE_TRANS_MISSING_INDEX_ERROR    0x00000300
#define ER_IMAGE_TRANS_DELAY_ERROR            0x00000400
#define ER_IMAGE_TRANS_UNSUPPORTED_ERROR      0x00000500

struct MsgNode
{
	/*CANID*/
	int id;

	/*数据长度*/
	int dlc;

	/*数据*/
	unsigned char data[64];

	/*拓展帧*/
	bool extFrame;

	/*远程帧*/
	bool remFrame;

	/*时间戳*/
	float timeStamp;
};

class CanMessage
{
public:
    CanMessage();

    ~CanMessage();

	void save(const MsgNode* msg, int size);

	int get(MsgNode* msg, int size);

    void clear();

private:
    bool empty();

    bool full();

    int m_writeIndex = 0;

    int m_readIndex = 0;

    void* m_cs = nullptr;

	MsgNode m_msg[MAX_SAVE_MSG_COUNT] = { 0 };
};

