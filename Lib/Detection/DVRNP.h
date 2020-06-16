#ifndef DVR_NETWORK_PROTOCOL
#define DVR_NETWORK_PROTOCOL
/*
byte	0		1		2		3		4		5		6		7		8		…		n - 1		n		n + 1		n + 2		n + 3
name	EE	    AA	    LEN								CMD		SUB		DATA						CRC32
		数据头			数据长度 = CMD + SUB + DATA		命令	子命令	数据						校验 = CRC32(LEN + CMD + SUB + DATA)



APP与SoC端使用相同的传输层协议，其中包括：

HDR	数据头	固定为EE、AA
LEN	数据长度	指“命令” + “子命令” + “数据”的长度
CMD	命令	详见[3 - 服务层协议]
SUB	子命令	详见[3 - 服务层协议]
DATA	数据	详见[3 - 服务层协议]，可以为空
CRC32	校验码	“长度” + “命令” + “子命令” + “数据”的CRC32值

SOCKET通讯端口号		2000
*/
#include <iostream>

struct Connecting {
	enum {
		CMD,
	};
	enum {
		HANDSHAKE,
		PAIRING_REQS,
		PAIRING_CHECK,
		HEARTBEAT = 0x10,
		AP_CONNECT_REQS = 0x20,
	};
}connecting_t;

struct UiControl {
	unsigned char cmd;
	enum {
		UI_REQ_PREVIEW,
		UI_REQ_FILES,
		UI_REQ_CONFIG,
		UI_REQ_PLAYBACK,
	};
}uiControl_t;

struct FastControl {
	unsigned char cmd;
	enum {
		FAST_CYCLE_RECORD,
		FAST_EMERGE = 0x10,
		FAST_PHOTOGRAPHY = 0x11,
	};
}fastControl_t;
class DvrNetworkProtocol
{
private:

protected:

public:
	DvrNetworkProtocol();
	~DvrNetworkProtocol();
	void pack();
};
#endif //!DVR_NETWORK_PROTOCOL
