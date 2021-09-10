
//接口卡类型定义
#define VCI_PCI5121		1
#define VCI_PCI9810		2
#define VCI_USBCAN1		3
#define VCI_USBCAN2		4
#define VCI_PCI9820		5
#define VCI_CAN232		6

//函数调用返回状态值
#define	STATUS_OK 1
#define STATUS_ERR 0

//CAN错误码
#define	ERR_CAN_OVERFLOW			0x0001	//CAN控制器内部FIFO溢出
#define	ERR_CAN_ERRALARM			0x0002	//CAN控制器错误报警
#define	ERR_CAN_PASSIVE				0x0004	//CAN控制器消极错误
#define	ERR_CAN_LOSE				0x0008	//CAN控制器仲裁丢失
#define	ERR_CAN_BUSERR				0x0010	//CAN控制器总线错误

//通用错误码
#define	ERR_DEVICEOPENED			0x0100	//设备已经打开
#define	ERR_DEVICEOPEN				0x0200	//打开设备错误
#define	ERR_DEVICENOTOPEN			0x0400	//设备没有打开
#define	ERR_BUFFEROVERFLOW			0x0800	//缓冲区溢出
#define	ERR_DEVICENOTEXIST			0x1000	//此设备不存在
#define	ERR_LOADKERNELDLL			0x2000	//装载动态库失败
#define ERR_CMDFAILED				0x4000	//执行命令失败错误码
#define	ERR_BUFFERCREATE			0x8000	//内存不足


//1.ZLGCAN系列接口卡信息的数据类型。
typedef  struct  _VCI_BOARD_INFO{
		unsigned short	hw_Version;
		unsigned short	fw_Version;
		unsigned short	dr_Version;
		unsigned short	in_Version;
		unsigned short	irq_Num;
		unsigned char	can_Num;
		char	str_Serial_Num[20];
		char	str_hw_Type[40];
		unsigned short	Reserved[4];
} VCI_BOARD_INFO,*PVCI_BOARD_INFO; 

//2.定义CAN信息帧的数据类型。
typedef  struct  _VCI_CAN_OBJ{
	unsigned int	ID;
	unsigned int	TimeStamp;
	unsigned char	TimeFlag;
	unsigned char	SendType;
	unsigned char	RemoteFlag;//是否是远程帧
	unsigned char	ExternFlag;//是否是扩展帧
	unsigned char	DataLen;
	unsigned char	Data[8];
	unsigned char	Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

//3.定义CAN控制器状态的数据类型。
typedef struct _VCI_CAN_STATUS{
	unsigned char	ErrInterrupt;
	unsigned char	regMode;
	unsigned char	regStatus;
	unsigned char	regALCapture;
	unsigned char	regECCapture; 
	unsigned char	regEWLimit;
	unsigned char	regRECounter; 
	unsigned char	regTECounter;
	unsigned long	Reserved;
}VCI_CAN_STATUS,*PVCI_CAN_STATUS;

//4.定义错误信息的数据类型。
typedef struct _ERR_INFO{
		unsigned int	ErrCode;
		unsigned char	Passive_ErrData[3];
		unsigned char	ArLost_ErrData;
} VCI_ERR_INFO,*PVCI_ERR_INFO;

//5.定义初始化CAN的数据类型
typedef struct _INIT_CONFIG{
	unsigned long	AccCode;
	unsigned long	AccMask;
	unsigned long	Reserved;
	unsigned char	Filter;
	unsigned char	Timing0;	
	unsigned char	Timing1;	
	unsigned char	Mode;
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

unsigned long __stdcall VCI_OpenDevice(unsigned long DeviceType,unsigned long DeviceInd,unsigned long Reserved);
unsigned long __stdcall VCI_CloseDevice(unsigned long DeviceType,unsigned long DeviceInd);
unsigned long __stdcall VCI_InitCAN(unsigned long DeviceType, unsigned long DeviceInd, unsigned long CANInd, PVCI_INIT_CONFIG pInitConfig);

unsigned long __stdcall VCI_ReadBoardInfo(unsigned long DeviceType,unsigned long DeviceInd,PVCI_BOARD_INFO pInfo);
unsigned long __stdcall VCI_ReadErrInfo(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_ERR_INFO pErrInfo);
unsigned long __stdcall VCI_ReadCANStatus(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_CAN_STATUS pCANStatus);

unsigned long __stdcall VCI_GetReference(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,unsigned long RefType,void* pData);
unsigned long __stdcall VCI_SetReference(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,unsigned long RefType,void* pData);

unsigned long __stdcall VCI_GetReceiveNum(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);
unsigned long __stdcall VCI_ClearBuffer(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);

unsigned long __stdcall VCI_StartCAN(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);
unsigned long __stdcall VCI_ResetCAN(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd);

unsigned long __stdcall VCI_Transmit(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_CAN_OBJ pSend,unsigned long Len);
unsigned long __stdcall VCI_Receive(unsigned long DeviceType,unsigned long DeviceInd,unsigned long CANInd,PVCI_CAN_OBJ pReceive,unsigned long Len,int WaitTime=-1);

