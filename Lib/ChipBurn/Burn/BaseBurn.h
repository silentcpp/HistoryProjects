#pragma once
#pragma execution_character_set("utf-8")
/*
* @notice,这个库可能会给第三方调用,需要使用标准库进行开发
*/

#include <QObject>

#include <Windows.h>
#include <vector>
#include <deque>
#include <algorithm>

#include "../Device/Aardvark/AardvarkDevice.h"

#define C_SPRINTF(format, ...) QString().sprintf(format,##__VA_ARGS__)

#define LIB_RUN_BREAK(success,format,...)\
if (success)\
{\
	setLastError(C_SPRINTF(format,##__VA_ARGS__));\
	break;\
}

//#define SLAVE_ADDR_96706	(0x90 >> 1)

#define SLAVE_ADDR_96706    (0x9C >> 1)

#define SLAVE_ADDR_96701	(0x80 >> 1)

//长安IMS BX11
#define SLAVE_ADDR_934		(0x60 >> 1)

#define SLAVE_ADDR_914		(0xD0 >> 1)

//#define SLAVE_ADDR_914		(0xC0 >> 1)

/*
* @ChipType,芯片类型
* @notice,命名规则
* CT + 芯片名称 + 存储介质 + 项目名称
* CT 代表ChipType的缩写,
* UNIVERSAL_SET 代表为通用集合,很多
* 项目共用一个类库.
*/
enum ChipType
{
	CT_UNKNOWN,

	CT_ASX340_FLASH_UNIVERSAL_SET,

	CT_ASX340_EEPROM_UNIVERSAL_SET,

	CT_ASX340_EEPROM_GEELY_BX11,

	CT_SONY016_FLASH_UNIVERSAL_SET,

	CT_SONY016_EEPROM_UNIVERSAL_SET,

	CT_SONY019_FLASH_UNIVERSAL_SET,

	CT_SONY019_FLASH_CHANGAN_IMS,

	CT_SONY019_FLASH_EP30TAP_DMS,

	CT_OV7958_FLASH_UNIVERSAL_SET,

	CT_OVX1E_FLASH_UNIVERSAL_SET
};

class BaseBurn
{
public:
	BaseBurn();

	virtual ~BaseBurn();

	BaseBurn(const BaseBurn&) = delete;

	BaseBurn& operator=(const BaseBurn&) = delete;

	/*
	* @setDevice,设置设备
	* @param1,设备
	* @return,void
	*/
	void setDevice(BaseDevice* device);

	/*
	* @setChipType,设置芯片类型
	* @param1,芯片类型
	* @return,void
	*/
	void setChipType(ChipType type);

	/*
	* @getType,获取芯片类型
	* @return,CamerType
	*/
	ChipType getChipType() const;

	/*
	* @getLastError,获取最终错误
	* @retur,const std::string&
	*/
	const QString& getLastError();

	/*
	* @setSlave,设置从地址
	* @param1,从地址
	* @return,void
	*/
	void setSlave(ushort slave);

	/*
	* @getSlave,获取从地址
	* @return,ushort
	*/
	ushort getSlave() const;

	/*
	* @setReadWriteDelay,设置读写延时
	* @param1,读延时
	* @param2,写延时
	* @return,void
	*/
	void setReadWriteDelay(int readDelay, int writeDelay);

	/*
	* @setJump0xFF,设置跳过0xff
	* @param1,是否跳过
	* @return,void
	*/
	void setJump0xFF(int jump);

public:
	/*
	* @initialize,初始化
	* @param1,芯片类型
	* @return,bool
	*/
	virtual bool initialize() = 0;

	/*
	* @readFile,读文件
	* @param1,读取的数据缓存区
	* @param2,读取大小
	* @param3,读取进度
	* @return,bool
	*/
	virtual bool readFile(uchar* data, uint size, int* percent) = 0;

	/*
	* @writeFile,写文件
	* @param1,写入的数据缓存区
	* @param2,写入的大小
	* @param3,写入进度
	* @return,bool
	*/
	virtual bool writeFile(const uchar* data, uint size, int* percent) = 0;

	/*
	* @readFlash,读取闪存
	* @param1,起始地址
	* @param2,读取的数据缓存区
	* @param3,读取大小
	* @return,bool
	*/
	virtual bool readFlash(uint address, uchar* data, ushort size);

	/*
	* @writeFlash,写入闪存
	* @param1,起始地址
	* @param2,写入的数据缓存区
	* @param3,写入大小
	* @return,bool
	*/
	virtual bool writeFlash(uint address, const uchar* data, ushort size);

	/*
	* @readEeprom,读取电可擦除只读存储器
	* @param1,起始地址
	* @param2,读取的数据缓存区
	* @param3,读取大小
	* @return,bool
	*/
	virtual bool readEeprom(uint address, uchar* data, ushort size);

	/*
	* @writeEeprom,写入电可擦除只读存储器
	* @param1,起始地址
	* @param2,写入的数据缓存区
	* @param3,写入大小
	* @return,bool
	*/
	virtual bool writeEeprom(uint address, const uchar* data, ushort size);

	/*
	* @lock,上锁
	* @return,bool
	*/
	virtual bool lock();

	/*
	* @unlock,解锁
	* @return,bool
	*/
	virtual bool unlock();

public:
	/*
	* @i2cAddrRead,i2c地址读取
	* @param1,起始地址
	* @param2,地址长度
	* @param3,数据缓存区
	* @param4,读取数据大小
	* @param5,从地址
	* @return,bool
	*/
	bool i2cAddrRead(uint addr, uchar addrLen, uchar* data, ushort dataSize, ushort slave = 0);

	/*
	* @i2cAddrWrite,i2c地址写入
	* @param1,起始地址
	* @param2,地址长度
	* @param3,数据缓存区
	* @param4,写入数据大小
	* @param5,是否校验
	* @param6,从地址
	* @return,bool
	*/
	bool i2cAddrWrite(uint addr, uchar addrLen, const uchar* data, ushort dataSize, bool check = false, ushort slave = 0);

	/*
	* @i2cAddrWrite,i2c地址写入
	* @param1,起始地址
	* @param2,地址长度
	* @param3,初始化数据列表
	* @param4,从地址
	* @return,bool
	*/
	bool i2cAddrWrite(uint addr, uchar addrLen, const std::initializer_list<uchar>& data, ushort slave = 0);

protected:
	/*
	* @readData,读取数据
	* @param1,起始地址
	* @param2,读取的数据缓存区
	* @param3,读取大小
	* @return,bool
	*/
	virtual bool readData(uint address, uchar* data, ushort size) = 0;

	/*
	* @writeData,写入数据
	* @param1,起始地址
	* @param2,写入的数据缓存区
	* @param3,写入大小
	* @return,bool
	*/
	virtual bool writeData(uint address, const uchar* data, ushort size) = 0;

	/*
	* @setLastError,设置最终错误
	* @param1,错误信息
	* @return,void
	*/
	void setLastError(const QString& error);

	/*
	* @i2cRead,i2c读
	* @param1,读取的数据
	* @param2,读取的大小
	* @param3,slave地址
	* @return,实际读取的大小
	*/
	int i2cRead(uchar* data, ushort size, ushort slave = 0);

	/*
	* @i2cWrite,i2c写
	* @param1,写入的数据
	* @param2,写入的大小
	* @param3,slave地址
	* @return,实际写入的大小
	*/
	int i2cWrite(const uchar* data, ushort size, ushort slave = 0);

	/*
	* @i2cWrite,i2c写
	* @param1,写入的数据列表
	* @param2,从地址
	* @return,实际写入的大小
	*/
	int i2cWrite(const std::initializer_list<uchar>& data, ushort slave = 0);

	/*
	* @printLog,打印日志
	* @param1,日志类型[R,S]
	* @param2,日志数据
	* @param3,数据大小
	* @param4,从地址
	* @return,void
	*/
	void printLog(const QString& type, const uchar* data, int size, ushort slave);

	/*
	* @msleep,休眠
	* @param1,休眠多少毫秒
	* @return,void
	*/
	void msleep(uint ms);

	/*
	* @calculateSector,计算扇区
	* @parma1,数据缓存区
	* @param2,数据缓存区大小
	* @param3,倍数
	* @return,std::vector<uint>
	*/
	std::deque<uint> calculateSector(const uchar* buffer, uint size, uint multiple = 256, uchar value = 0xff);

	/*
	* @findNearNumber,寻找相邻地址
	* @param1,要寻找的地址
	* @param2,倍数
	* @param3,是否按降序排列
	* @return,成功返回找到的地址,失败(uint)-1未找到
	*/
	uint findNearAddress(uint address, uint multiple, bool lessThan = true);

	/*
	* @getPercent,获取百分比
	* @param1,当前
	* @param2,总数
	* @return,int
	*/
	int getPercent(uint current, uint total);

protected:

	ChipType m_chipType = CT_UNKNOWN;

	int m_readDelay = 0;

	int m_writeDelay = 0;
private:
	QString m_lastError = "No error";

	ushort m_slave = 0;

	bool m_jump0xff = false;

	BaseDevice* m_device = nullptr;
};