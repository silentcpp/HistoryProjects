#pragma once
#include "../BaseBurn.h"

#define SONY_CMD_MAX_CNT 16

#define SONY_CMD_FRAME_MAX_LEN 137

struct SonyCmdFrame
{
	uchar total_byte;
	uchar cmd_cnt;
	struct {
		uchar total_cmd_byte;
		uchar cmd_and_status_code;
		uchar data[128];
	} cmd[SONY_CMD_MAX_CNT];
	uchar check_sum;
};

enum SonyCmdList
{
	CMD_LOCK_UNLOCK = 0x00,

	CMD_READ_REG = 0x01,

	CMD_WRITE_REG = 0x02,

	CMD_READ_EEP = 0x03,

	CMD_WRITE_EEP = 0x04,

	CMD_ALL_SAVE_REG_TO_EEP_019 = 0x05,

	CMD_WRITE_CHECK_SUM_016 = 0x08,

	CMD_ERASE_EEP_019 = 0x08,
};

enum SonyStatusCode
{
	SC016_SUCCESS = 0x01,

	SC016_ERR_EFFI_NUM = 0xF0,

	SC016_ERR_CMD_NUM_NOT_EXIST = 0xF1,

	SC016_ERR_CAT_NUM = 0xF2,

	SC016_ERR_ADDR_OFFSET = 0xF3,

	SC016_ERR_ACCESS = 0xF4,

	SC016_ERR_CMD_NUM_NOT_MATCH = 0xF5,

	SC016_ERR_CHECK_SUM = 0xF6,

	SC016_ERR_TOTAL_BYTE_NUM = 0xF7,

	SC016_ERR_EEP_ACCESS = 0xFA,

	SC016_ERR_COMMUNICATION = 0xFC,
};

class Sony016 : public BaseBurn
{
public:
	Sony016();

	~Sony016();

	bool initialize();

	bool lock();

	bool unlock();

	bool readFile(uchar* data, uint size, int* percent);

	bool writeFile(const uchar* data, uint size, int* percent);

	bool readEeprom(uint address, uchar* data, ushort size);

	bool writeEeprom(uint address, const uchar* data, ushort size);
protected:
	bool readData(uint address, uchar* data, ushort size);

	bool writeData(uint address, const uchar* data, ushort size);

	/*
	* @packFrame,打包帧
	* @param1,帧结构体
	* @param2,数据缓存区
	* @return,bool
	*/
	bool packFrame(SonyCmdFrame frame, uchar* data);

	/*
	* @unpackFrame,解包帧
	* @param1,帧结构体
	* @param2,数据缓存区
	* @param3,数据缓存区大小
	* @return,bool
	*/
	bool unpackFrame(SonyCmdFrame* frame, const uchar* data, uchar size);

	/*
	* @readFrame,读取帧
	* @param1,命令帧
	* @param2,读取大小
	* @param3,从地址
	* @return,bool
	*/
	bool readFrame(SonyCmdFrame* frame, uchar size);

	/*
	* @writeFrame,写入帧
	* @param1,命令帧
	* @param2,从地址
	* @return,bool
	*/
	bool writeFrame(SonyCmdFrame frame);

	/*
	* @readRegister,读寄存器
	* @param1,寄存器种类
	* @param2,偏移地址
	* @param3,读取的缓存区
	* @param4,读取的缓存区大小
	* @return,bool
	*/
	bool readRegister(uchar category, ushort addrOffset, uchar* data, uchar dataSize);

	/*
	* @writeRegister,写寄存器
	* @param1,寄存器种类
	* @param2,偏移地址
	* @param3,写入的缓存区
	* @param4,写入的缓存区大小
	* @return,bool
	*/
	bool writeRegister(uchar category, ushort addrOffset, const uchar* data, uchar dataSize);

	/*
	* @tempInit,临时初始化
	* @notice,这个函数用途未知
	* @return,bool
	*/
	bool tempInit();

	/*
	* @tempUnint,临时未初始化
	* @notice,这个函数用途未知
	* @return,bool
	*/
	bool tempUnint();

	/*
	* @setErrorInfo,设置错误信息
	* @param1,错误码
	* @return,void
	*/
	void setErrorInfo(uchar code);

	int m_cmdAddrLen = 2;
private:
	bool protect();

	bool unprotect();

	bool convertToAddress();

	bool changeFlashStatus();
};

