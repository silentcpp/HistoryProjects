#pragma once
/*
													《琵琶行》

															白居易

											浔阳江头夜送客，枫叶荻花秋瑟瑟。
											主人下马客在船，举酒欲饮无管弦。
											醉不成欢惨将别，别时茫茫江浸月。

											忽闻水上琵琶声，主人忘归客不发。
											寻声暗问弹者谁，琵琶声停欲语迟。
											移船相近邀相见，添酒回灯重开宴。
											千呼万唤始出来，犹抱琵琶半遮面。
											转轴拨弦三两声，未成曲调先有情。
											弦弦掩抑声声思，似诉平生不得志。
											低眉信手续续弹，说尽心中无限事。
											轻拢慢捻抹复挑，初为霓裳后六幺。
											大弦嘈嘈如急雨，小弦切切如私语。
											嘈嘈切切错杂弹，大珠小珠落玉盘。
											间关莺语花底滑，幽咽泉流冰下难。
											冰泉冷涩弦凝绝，凝绝不通声暂歇。
											别有幽愁暗恨生，此时无声胜有声。
											银瓶乍破水浆迸，铁骑突出刀枪鸣。
											曲终收拨当心画，四弦一声如裂帛。
											东船西舫悄无言，唯见江心秋月白。

											沉吟放拨插弦中，整顿衣裳起敛容。
											自言本是京城女，家在虾蟆陵下住。
											十三学得琵琶成，名属教坊第一部。
											曲罢曾教善才服，妆成每被秋娘妒。
											五陵年少争缠头，一曲红绡不知数。
											钿头银篦击节碎，血色罗裙翻酒污。
											今年欢笑复明年，秋月春风等闲度。
											弟走从军阿姨死，暮去朝来颜色故。
											门前冷落鞍马稀，老大嫁作商人妇。
											商人重利轻别离，前月浮梁买茶去。
											去来江口守空船，绕船月明江水寒。
											夜深忽梦少年事，梦啼妆泪红阑干。

											我闻琵琶已叹息，又闻此语重唧唧。
											同是天涯沦落人，相逢何必曾相识！
											我从去年辞帝京，谪居卧病浔阳城。
											浔阳地僻无音乐，终岁不闻丝竹声。
											住近湓江地低湿，黄芦苦竹绕宅生。
											其间旦暮闻何物？杜鹃啼血猿哀鸣。
											春江花朝秋月夜，往往取酒还独倾。
											岂无山歌与村笛，呕哑嘲哳难为听。
											今夜闻君琵琶语，如听仙乐耳暂明。
											莫辞更坐弹一曲，为君翻作琵琶行。

											感我此言良久立，却坐促弦弦转急。
											凄凄不似向前声，满座重闻皆掩泣。
											座中泣下谁最多？江州司马青衫湿。
*/

/************************************************************************/
/* Include                                                              */
/************************************************************************/
#include <QStyleFactory>

#include <QApplication>

#include <QBitmap>

#include <QPainter>

#include <QThread>

#include <QDesktopWidget>

#include <QThread>

#include <QDateTime>

#include <QImage>

#include <QDebug>

#include <QProcess>

#include <QTimer>

//#include <QtNetwork/QNetworkAccessManager>
//
//#include <QtNetwork/QNetworkRequest>
//
//#include <QtNetwork/QNetworkReply>

//#include <io.h>

#include <VoltageTestMgr/VoltageTestMgr.h>
#pragma comment(lib, "VoltageTestMgr.lib")

#include <MR-DO16-KNMgr/MR-DO16-KNMgr.h>
#pragma comment(lib, "MR-DO16-KNMgr.lib")

#include <UdsProtocolMgr/UdsFactory.h>
#pragma comment(lib, "UdsProtocolMgr.lib")

#include <ItechSCPIMgr/ItechSCPIMgr.h>
#pragma comment(lib, "ItechSCPIMgr.lib")

#include <CanMgr/ConnFactory.h>
#pragma comment(lib, "CanMgr.lib")

#include <StaticCurrentMgr/StaticCurrentMgr.h>
#pragma comment(lib, "StaticCurrentMgr.lib")

#include <MV800Mgr/MV800Mgr.h>
#pragma comment(lib, "MV800Mgr.lib")

#include <WifiMgr/WifiMgr.h>
#pragma comment(lib, "WifiMgr.lib")

#include "QMessageBoxEx.h"

#include "QLabelEx.h"

#include "CanMatrix.h"

#include "JsonTool.h"

#include "RayAxis.h"

#include "CanSender.h"

#include "SerialPortTool.h"

#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "urlmon.lib")

#include "../DetectionExt/Lib/OpenCv2.3.1/include/opencv/cv.h"
#include "../DetectionExt/Lib/OpenCv2.3.1/include/opencv/cxcore.h"
#include "../DetectionExt/Lib/OpenCv2.3.1/include/opencv/highgui.h"
#include "../DetectionExt/Lib/OpenCv2.3.1/include/opencv2/imgproc/imgproc_c.h"
#include "../DetectionExt/Lib/MIL/include/Mil.h"

#pragma comment(lib, "../DetectionExt/Lib/OpenCv2.3.1/lib/opencv_core231.lib")
#pragma comment(lib, "../DetectionExt/Lib/OpenCv2.3.1/lib/opencv_highgui231.lib")
#pragma comment(lib, "../DetectionExt/Lib/OpenCv2.3.1/lib/opencv_imgproc231.lib")
#pragma comment(lib, "../DetectionExt/Lib/MIL/lib/mil.lib")

using namespace cv;

#include "../DetectionExt/Lib/vlc-2.2.4/include/vlc.h"
#pragma comment(lib, "../DetectionExt/Lib/vlc-2.2.4/lib/libvlc.lib")
#pragma comment(lib, "../DetectionExt/Lib/vlc-2.2.4/lib/libvlccore.lib")

#include <process.h>
#include <wincon.h>
#include <WinInet.h>
#pragma comment(lib,"wininet.lib")


#define CALL_PYTHON_LIB 0

#if CALL_PYTHON_LIB
#include "../DetectionExt/Lib/Python34/include/Python.h"
#endif

/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define S_TO_Q_STR(X) QString::fromStdString(X)

#define WS_TO_Q_STR(X) QString::fromStdWString(X)

#define WC_TO_Q_STR QString::fromWCharArray

#define Q_TO_C_STR(X) X.toStdString().c_str()

#define Q_TO_WC_STR(X) X.toStdWString().c_str()

#define G_TO_Q_STR(X) QString::fromLocal8Bit(X)

#define G_TO_C_STR(X) Q_TO_C_STR(G_TO_Q_STR(X))

#define N_TO_Q_STR QString::number

#define SU_FA(X) X ? "成功":"失败"

#define OK_NG(X) X ? "OK" : "NG"

#define Q_SPRINTF(format,...) QString().sprintf(format,##__VA_ARGS__)

extern int* g_debugInfo;

static ulong __logCount = 0;

#define DEBUG_INFO()\
if (g_debugInfo && *g_debugInfo)\
	qDebug().noquote() << QString("%1 %2 %3 %4").arg(QString::number(++__logCount), 4, '0').arg(Misc::getCurrentTime(), \
	__FUNCTION__, QString::number(__LINE__))

#define DEBUG_INFO_EX(format,...) \
if (g_debugInfo && *g_debugInfo)\
	qDebug().noquote() << QString("%1 %2 %3 %4 %5").arg(QString::number(++__logCount), 4, '0').arg(Misc::getCurrentTime(), \
	__FUNCTION__, QString::number(__LINE__), Q_SPRINTF(format, ##__VA_ARGS__))

#define WRITE_LOG(format,...)\
m_logList.push_back(Q_SPRINTF(format,##__VA_ARGS__).replace(" ",","))

#define RUN_BREAK(success,error) \
if ((success))\
{\
	setLastError(error);\
	break;\
}

#define CYCLE_PROC_FNC(FNC,DELAY)\
{\
QTimer* timer = NO_THROW_NEW QTimer;\
if (timer)\
{\
QObject::connect(timer,&QTimer::timeout,FNC);\
timer->start(DELAY);\
}\
}

#define GET_FNC_NAME(X) #X

#define BUFF_SIZE 0x1000

#define NO_THROW_NEW new(std::nothrow)

#define GET_DT_DIR() ((Dt::Base::getDetectionType() == BaseTypes::DT_HARDWARE) ? "HwLog" : "FcLog")

#define GET_DT_TYPE() ((Dt::Base::getDetectionType() == BaseTypes::DT_HARDWARE) ? "硬件" : "功能")

#define AUTO_RESIZE(X) X->resize(QApplication::desktop()->screenGeometry().width() / 2 + 100,\
QApplication::desktop()->screenGeometry().height() / 2 + 100)

#define FREQ req

#define FMSG msg

#define FSIZE size

#define FDATA data

#define MSG_PROC_FNC(...) [__VA_ARGS__](const int& FREQ,const MsgNode& FMSG)mutable->bool

#define CAN_PROC_FNC(...) [__VA_ARGS__](const int& FREQ,const MsgNode& FMSG)mutable->bool

#define UDS_PROC_FNC(...) [__VA_ARGS__](const int& FREQ,const int& FSIZE,const uchar* FDATA)mutable->bool

#define TEST_PASS []()->bool{ return true; }

typedef const std::function<bool(const int&, const MsgNode&)>& MsgProc;

typedef const std::function<bool(const int&, const int&, const uchar* data)>& UdsProc;

typedef const std::initializer_list<int>& IdList;

typedef const std::initializer_list<int>& ReqList;

typedef const std::initializer_list<CanMsg>& CanList;

typedef const std::initializer_list<MsgNode>& MsgList;

typedef const std::initializer_list<uchar>& DidList;

typedef MsgProc CanProc;

struct MsgProcInfo {
	int id;
	int req;
	MsgProc proc;
};

struct CanProcInfo {
	int id;
	int req;
	CanProc proc;
};

struct MsgProcInfoEx {
	IdList idList;
	ReqList reqList;
	MsgProc proc;
};

struct CanProcInfoEx {
	IdList idList;
	ReqList reqList;
	CanProc proc;
};

enum TestSequence {
	TS_SCAN_CODE = 0x1000,
	TS_PREP_TEST,
	TS_CHECK_STATIC,
	TS_CHECK_ROUSE,
	TS_CHECK_VOLTAGE,
	TS_CHECK_CURRENT,
	TS_CHECK_VERSION,
	TS_WRITE_SN,
	TS_CHECK_SN,
	TS_WRITE_DATE,
	TS_SAVE_LOG,
	TS_CHECK_VIDEO,
	TS_CHECK_AVM,
	TS_SET_AVM,
	TS_CHECK_DVR,
	TS_CHECK_FRVIEW,
	TS_CHECK_LRVIEW,
	TS_CHECK_ALLVIEW,
	TS_CLEAR_DTC,
	TS_CHECK_DTC,
	TS_FORMAT_CARD,
	TS_UMOUNT_CARD,
	TS_CHECK_CARD,
	TS_POPUP_CARD,
	TS_CHECK_RECORD,
	TS_CHECK_RAYAXIS_SFR,
	TS_CHECK_RAYAXIS,
	TS_CHECK_SFR,
	TS_CHECK_PLAYBACK,
	TS_CHECK_UART,
	TS_CHECK_KEYVOL,
	TS_CHECK_LDW,
	TS_CHANGE_PWD,
	TS_CHECK_MINCUR,
	TS_CHECK_MAXCUR,
	TS_CAN_PROC0,
	TS_CAN_PROC1,
	TS_CAN_PROC2,
	TS_CAN_PROC3,
	TS_CAN_PROC4,
	TS_CAN_PROC5,
	TS_CAN_PROC6,
	TS_CAN_PROC7,
	TS_CAN_PROC8,
	TS_CAN_PROC9,
	TS_UDS_PROC0,
	TS_UDS_PROC1,
	TS_UDS_PROC2,
	TS_UDS_PROC3,
	TS_UDS_PROC4,
	TS_UDS_PROC5,
	TS_UDS_PROC6,
	TS_UDS_PROC7,
	TS_UDS_PROC8,
	TS_UDS_PROC9,
	TS_NO
};

#define TS_SUCCESS success

#define GO_SAVE_LOG()\
success = false;\
m_testSequence = TS_SAVE_LOG;\
break

#define GO_NEXT_TEST(NEXT)\
success = true;\
m_testSequence = NEXT;\
break

template<class T> static void _assertProcCall(const T& arg)
{
	(static_cast<const std::function<void()>&>(arg))();
}

template<class T, class ...args> static void _assertProcCall(const T& fnc, args... arg)
{ 
	_assertProcCall(arg...);
}

#define ASSERT_PROC_FNC(...) [__VA_ARGS__]()mutable->void

/*
* @ASSERT_TEST
* @param1,当前测试内容
* @param2,当前测试函数
* @param3,下个测试内容
* @param4,附加函数,ASSERT_PROC_FNC(){},可选
*/
#define ASSERT_TEST(CURR,FNC,NEXT,...)\
case CURR:\
{\
	if (!FNC)\
	{\
		if (CURR == TS_SAVE_LOG)\
		{\
			setMessageBox("保存日志失败",getLastError());\
		}\
		else\
		{\
			GO_SAVE_LOG();\
		}\
	}\
	_assertProcCall(ASSERT_PROC_FNC(){},__VA_ARGS__);\
	GO_NEXT_TEST(NEXT);\
}

#define TEST_THREAD(FNC)\
bool success = true;\
while(!m_quit)\
{\
	if (m_connect)\
	{\
		switch(m_testSequence)\
		{\
			FNC\
			default:break;\
		}\
	}\
	msleep(100);\
}

#define TEST_THREAD_EX(FNC)\
bool success = true;\
while(!m_quit)\
{\
	if (m_connect)\
	{\
		switch(m_testSequence)\
		{\
			ASSERT_TEST(TS_SCAN_CODE, setScanCodeDlg(), TS_PREP_TEST);\
			FNC\
			ASSERT_TEST(TS_SAVE_LOG, saveLog(TS_SUCCESS), TS_SCAN_CODE);\
			default:break;\
		}\
	}\
	msleep(100);\
}

namespace BaseTypes {
	/*
	* 下载信息
	* @param1,对话框标题
	* @param2,URL链接
	* @param3,保存路径
	* @param4,文件大小
	* @param5,所用时间
	* @param6,平均速度
	* @param7,错误内容
	* @param8,结果
	*/
	struct DownloadInfo {
		QString title;
		QString url;
		QString path;
		float size;
		ulong time;
		float speed;
		QString error;
		bool result;
	};

	/*检测类型*/
	enum DetectionType { DT_AVM, DT_DVR, DT_HARDWARE, DT_TAP };

	/*测试结果*/
	enum TestResult { TR_NO, TR_OK, TR_NG, TR_TS };

	/*检测日志*/
	enum DetectionLog { DL_CUR, DL_RES, DL_VOL, DL_VER, DL_DTC, DL_ALL };
}

namespace HwTypes {

}

namespace FcTypes {
	/*矩形类型*/
	enum RectType { RT_FRONT_BIG, RT_REAR_BIG, RT_LEFT_BIG, RT_RIGHT_BIG, RT_SMALL, RT_NO };

	/*采集卡结构体*/
	struct CardConfig {
		/*采集卡名称*/
		QString name;

		/*采集卡通道数*/
		int channelCount;

		/*采集卡通道号*/
		int channelId;

		/*图像宽度*/
		int width;

		/*图像高度*/
		int height;

		/*图像总大小*/
		int size;
	};
}

namespace AvmTypes {

}

namespace DvrTypes {
	/*系统状态报文*/
	enum SysStatusMsg {
		SSM_BAIC = 0x5A0,
		SSM_CHJ = 0x514,
	};

	enum PlayResult {
		PR_OK,
		PR_NG,
		PR_REPLAY
	};

	/*网络类型*/
	enum NetworkTypes { NT_WIFI, NT_ETHERNET };

	/*DVR系统状态*/
	enum SystemStatus { SS_INITIALIZING, SS_GENERAL_RECORD, SS_PAUSE_RECORD, SS_HARDWARE_KEY, SS_CRASH_KEY, SS_UPDATE_MODE, SS_ERROR, };

	/*WIFI状态*/
	enum WifiStatus { WS_CLOSE, WS_INIT, WS_NORMAL, WS_CONNECT, WS_ERROR, WS_CONNECTED };

	/*以太网状态*/
	enum EthernetStatus { ES_CONNECT, ES_ERROR, };

	/*SD卡状态*/
	enum SdCardStatus { SCS_NORMAL, SCS_NO_SD, SCS_ERROR, SCS_NOT_FORMAT, SCS_INSUFFICIENT, SCS_SPEED_LOW, SCS_USING, SCS_RESERVED, };

	/*文件路径*/
	enum FilePath { FP_NOR, FP_EVT, FP_PHO, FP_D1, FP_ALL, };

	/*文件类型*/
	enum FileType { FT_PHOTO, FT_VIDEO };

	/*格式化SD卡*/
	enum FormatSdCard { FSC_BY_NETWORK, FSC_BY_CAN, FSC_BY_UDS, };

	/*网络命令1*/
	enum NetCmd { NC_CONNECT = 0x00, NC_FAST_CONTROL = 0x02,NC_FILE_CTRL = 0x10, NC_CONFIG_SET = 0x12 };

	/*网络命令2*/
	enum NetSub { NS_HEART = 0x10, NS_FAST_CYCLE_RECORD = 0x00, NS_GET_FILE_LIST = 0x02, NS_FORMAT_SD_CARD = 0x20 };

	/*网络错误*/
	enum NetErr {
		NE_OK = 0x00000000U,
		NE_PARA_CONST,
		NE_PARA_RANGE,
		NE_PARA_VALUE = 0x00000004U,
		NE_OVERTIME = 0x00000008U,
		NE_BUSY = 0x00000010U,
		NE_NOT_INIT = 0x00000020U,
		NE_NOT_SUPPORT = 0x00000040U,
		NE_BUFF_EMPTY = 0x00000080U,
		NE_BUFF_FULL = 0x00000100U,
		NE_HW_PER = 0x00000200U,
		NE_HW_IC = 0x00000400U,
		NE_ACCESS = 0x00000800U,
		NE_CHECK = 0x00001000U,
		NE_BUS_OFF = 0x00002000U,
		NE_ABORT = 0x00004000U,
		NE_OVERFLOW = 0x00008000U,
		NE_UNKNOW = 0x80000000U,
	};

	/*加密算法密钥*/
	static const size_t crc32Table[256] = { 
		
	};
}

