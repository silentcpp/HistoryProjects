#ifndef ISP_H_INCLUDED
#define ISP_H_INCLUDED

/*A12网络烧录摄像头很坑,烧录一次失败就直接报废,如要使用此类,请一定要认认真真验证!!!切记,重要的事情所三遍!!!认认真真验证 认认真真验证 认认真真验证*/
/*如果要改里面的地址数据,改完之后一定要给改回原来的值,中途千万不要去断电,一断电就报废,巨坑货,改的时候一定要小心.*/

#define USE_WIN_OS
#include <string>
#include <vector>
#include <QDebug>

typedef signed char                 int8;
typedef unsigned char               uint8;
typedef signed short int            int16;
typedef unsigned short int          uint16;
typedef signed long int             int32;
typedef unsigned long int           uint32;
typedef signed long long            int64;
typedef unsigned long long          uint64;
typedef signed int                  fint;
typedef unsigned int                fuint;

typedef enum NetworkCmdId
{
    NET_SET_REG_16  = 0xC402,
    NET_GET_REG_16  = 0xC403,
    NET_SET_VAR_8   = 0xC500,
    NET_GET_VAR_8   = 0xC501,
    NET_SET_VAR_16  = 0xC502,
    NET_GET_VAR_16  = 0xC503,
    NET_SET_VAR_32  = 0xC504,
    NET_GET_VAR_32  = 0xC505,
    NET_SET_OVL0_8  = 0xC640,
    NET_GET_OVL0_8  = 0xC641,
    NET_SET_OVL0_16 = 0xC642,
    NET_GET_OVL0_16 = 0xC643,
    NET_SET_OVL0_32 = 0xC644,
    NET_GET_OVL0_32 = 0xC645,
    NET_SET_OVL1_8  = 0xC650,
    NET_GET_OVL1_8  = 0xC651,
    NET_SET_OVL1_16 = 0xC652,
    NET_GET_OVL1_16 = 0xC653,
    NET_SET_OVL1_32 = 0xC654,
    NET_GET_OVL1_32 = 0xC655,
    NET_SET_OVL2_8  = 0xC660,
    NET_GET_OVL2_8  = 0xC661,
    NET_SET_OVL2_16 = 0xC662,
    NET_GET_OVL2_16 = 0xC663,
    NET_SET_OVL2_32 = 0xC664,
    NET_GET_OVL2_32 = 0xC665,
    NET_SET_OVL3_8  = 0xC670,
    NET_GET_OVL3_8  = 0xC671,
    NET_SET_OVL3_16 = 0xC672,
    NET_GET_OVL3_16 = 0xC673,
    NET_SET_OVL3_32 = 0xC674,
    NET_GET_OVL3_32 = 0xC675,
    NET_SET_RAW_8   = 0xC700,
    NET_GET_RAW_8   = 0xC701,
    NET_SET_RAW_16  = 0xC702,
    NET_GET_RAW_16  = 0xC703,
    NET_SET_RAW_32  = 0xC704,
    NET_GET_RAW_32  = 0xC705,
}networkCmdId_t;

typedef enum HostCmdId
{
    SYSMGR_SET_STATE = 0x8100,
    SYSMGR_GET_STATE = 0x8101,
    FLASHMGR_GET_LOCK = 0x8500,
    FLASHMGR_LOCK_STATUS = 0x8501,
    FLASHMGR_RELEASE_LOCK = 0x8502,
    FLASHMGR_READ = 0x8504,
    FLASHMGR_WRITE = 0x8505,
    FLASHMGR_ERASE_DEVICE = 0x8507,
    FLASHMGR_STATUS = 0x8509,
    FLASHMGR_CONFIG_DEVICE = 0x850A,
}hostCmdId_t;

typedef enum SystemState
{
    SYS_STATE_ENTER_CONFIG_CHANGE = 0x28,
    SYS_STATE_ENTER_STREAMING = 0x34,
    SYS_STATE_ENTER_SUSPEND = 0x40,
    SYS_STATE_ENTER_SOFT_STANDBY = 0x50,
    SYS_STATE_LEAVE_SOFT_STANDBY  = 0x55
}systemState_t;

typedef enum RegisterAddress
{
	/*寄存器芯片版本*/
    CHIP_VERSION_REG = 0x0000,
	/*复位和杂项控制*/
    RESET_AND_MISC_CONTROL =  0x001A,
    /*命令寄存器*/
	COMMAND_REGISTER = 0x0040,
    /*寄存器最大地址*/
	REG_ADDRESS_MAX = 0x7FFF,
	/*网络配置和IPV4地址配置*/
    NET_CFG_IFC0_IPV4_ADDRESS = 0x8C28,
	NET_CFG_VID_SOURCE_IP_0 = 0x8CA4,
    CMD_HANDLER_PARAMS_POOL_0 = 0xFC00,
}registerAddress_t;

typedef enum DeviceErrorCode
{
    ERROR_ENOERR = 0,           // no error
    ERROR_ENOENT = 1,           // no such entity
    ERROR_EINTR  = 2,           // operation interrupted
    ERROR_EIO    = 3,           // I/O failure
    ERROR_E2BIG  = 4,           // too big
    ERROR_EBADF  = 5,           // bad file/handle
    ERROR_EAGAIN = 6,           // would-block, try again
    ERROR_ENOMEM = 7,           // not enough memory/resource
    ERROR_EACCES = 8,           // permission denied
    ERROR_EBUSY  = 9,           // entity busy, cannot support operation
    ERROR_EEXIST = 10,          // entity exists
    ERROR_ENODEV = 11,          // device not found
    ERROR_EINVAL = 12,          // invalid argument
    ERROR_ENOSPC = 13,          // no space/resource to complete
    ERROR_ERANGE = 14,          // parameter out-of-range
    ERROR_ENOSYS = 15,          // operation not supported
    ERROR_EALREADY = 16,        // already requested/exists
}deviceErrorCode_t;

typedef enum DeviceDriver
{
    SPI_READONLY = 0,   //mounted by default
    SPI_FLASH_RW = 1,
    SPI_EEPROM_RW = 2,
}deviceDeriver_t;



#define PARAM_LENGTH 4 //读取命令行参数长度
#define MAX_READ_SIZE 0xFF //每次读取最大字节
#define MAX_WRITE_SIZE 0x10 //每次写入最大字节



/************************************************************************/
/* IspTool Class                                                        */
/************************************************************************/

class IspTool {
private:
	IspTool();
	~IspTool();
	std::string m_lastError = "No Error";
    std::string m_ipaddr = "127.0.0.1";
	bool m_init = false;
	int m_delay = 1;
    static IspTool* m_self;
protected:
    /*设置错误*/
	void setLastError(const std::string& err);
	
    /*寄存器是否忙碌*/
    int16 registerIsBusy();
    
    /*寄存器空闲*/
	int16 waitRegisterLeisure(unsigned int timeout = 10, unsigned int timeoutDelay = 10);
	
    /*创建一个序列号,用于握手*/
    uint32 createSn();
    
    /*发送接收数据*/
	int16 sendRecvMsg(uint8* buffer, const uint16& bufferLen, uint16& paramLen);
	
    /*发送接收数据加强,在原有的基础上增加循环*/
    int16 sendRecvMsgEx(uint8* buffer, const uint16& bufferLen, uint16& paramLen, uint16 loop = 100);
	
    /*校验和*/
    uint16 checkSum(uint8* buffer, uint32 count);
public:
    /*此处封装成单例,拷贝构造删除*/
    IspTool(const IspTool&) = delete;
    
    /*此处封装成单例,操作符重载赋值删除*/
    IspTool& operator=(const IspTool&) = delete;

    /*获取单例*/
    static IspTool* getInstance();

    /*删除单例*/
    static void deleteInstance();

    /*初始化网络*/
	bool initNetwork(const std::string& ipaddr, const uint16& port, const std::string& protocol = "UDP");
	
    /*清理网络*/
    bool deinitNetwork();
	
    /*启用调试输出*/
    void enableDebugOutput(bool result);

    /*获取错误*/
	const std::string& getLastError();

    /*读寄存器*/
	int16 readRegister(const uint16& address, const uint16& totalBytes, std::vector<uint8>& regDatas);
	
    /*读寄存器1个字节*/
    int16 readRegister1Bytes(const uint16& address, uint8& value);
	
    /*读寄存器2个字节*/
    int16 readRegister2Bytes(const uint16& address, uint16& value);

    /*写寄存器*/
	int16 writeRegister(const uint16& address, std::vector<uint8>& regDatas);
	
    /*写寄存器1个字节*/
    int16 writeRegister1Bytes(const uint16& address, const uint8& value);
	
    /*写寄存器2个字节*/
    int16 writeRegister2Bytes(const uint16& address, const uint16& value);

    /*改变配置*/
	int16 changeConfiguration();
	
    /*设置系统状态*/
    int16 setSystemStatus(const uint16& status);

    /*是否可以交流*/
	int16 canBeCommunication();

    /*重置自身*/
	int16 resetSelf();

    /*加锁*/
	int16 lock();

    /*解锁*/
	int16 unlock();

    /*获得锁状态*/
	int16 getLockStatus();

    /*读Flash*/
	int16 readFlash(const uint32& address, const uint8& length, uint8** dataArray);
	
    /*写Flash*/
    int16 writeFlash(const uint32& address, const uint8& length, uint8* dataArray);

    /*获得Flash状态*/
	int16 getFlashStatus(uint8** dataArray);

    /*获得Flash状态*/
	int16 getFlashStatus();

    /*配置Flash设备*/
	int16 configFlashDevice(uint8 driverId, uint8 addressWidth, uint32 sizeOfDevice);

    /*擦除Flash设备*/
	int16 eraseFlashDevice();
	int16 configFlashDeviceNvm(uint8 byteWidth = 3, uint32 sizeOfDevice = 16 * 1024, uint8 driverId = SPI_READONLY);
	int16 readFlashDeviceNvm(uint8** dataArray, int32 numOfBytes, uint32 address = 0, int* progress = nullptr);
	int16 writeFlashDeviceNvm(const uint8* data, int32 numOfBytes, uint32 byteWidth = 3, uint32 address = 0, int* progress = nullptr);
};
#endif // ISP_H_INCLUDED
