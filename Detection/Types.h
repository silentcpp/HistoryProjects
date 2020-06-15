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
/* 此C++代码为苏州智华汽车电子有限科技公司,硬件 功能[AVM DVR TAP]检测框架		*/
/* 界面框架		  :Qt													*/
/* VS_QT插件		  :V2.3.3(此版本不要去更新,如果选择模块,没有确定按钮勾选回车即可)*/
/* 部门			  :工程部												*/
/* 所使用静态库开发者:卢东亚												*/
/* 框架开发者		  :王浩													*/
/************************************************************************/

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

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <imgproc\imgproc_c.h>

#pragma comment(lib, "opencv_core231.lib")
#pragma comment(lib, "opencv_highgui231.lib")
#pragma comment(lib, "opencv_imgproc231.lib")
using namespace cv;

#include <StaticCurrentMgr/StaticCurrentMgr.h>
#pragma comment(lib,"StaticCurrentMgr.lib")

#include <Mil.h>
#pragma comment(lib, "mil.lib")
#include <MV800Mgr/MV800Mgr.h>
#pragma comment(lib, "MV800Mgr.lib")

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

#include <vlc/vlc.h>
#pragma comment(lib, "libvlc.lib")
#pragma comment(lib, "libvlccore.lib")
#pragma comment(lib, "urlmon.lib")

/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define S_TO_Q_STR(X) QString::fromStdString(X)

#define WS_TO_Q_STR(X) QString::fromStdWString(X)

#define Q_TO_C_STR(X) X.toStdString().c_str()

#define Q_TO_WC_STR(X) X.toStdWString().c_str()

#define G_TO_Q_STR(X) QString::fromLocal8Bit(X)

#define G_TO_C_STR(X) Q_TO_C_STR(G_TO_Q_STR(X))

#define OK_NG(X) X ? "OK" : "NG"

#define Q_SPRINTF(format,...) QString().sprintf(format,__VA_ARGS__)

#define OUTPUT_DEBUG_INFO(format,...) \
static ulong count = 0;\
if (Dt::Base::getOutputRunLog())\
qDebug() << QString("%1 %2 %3 %4 %5").arg(QString::number(++count),4,'0').arg(Misc::getCurrentTime(),\
__FUNCTION__,QString::number(__LINE__),Q_SPRINTF(format,__VA_ARGS__))

#define WRITE_LOG(format,...)\
Dt::Base::m_logList.push_back(Q_SPRINTF(format,__VA_ARGS__).replace(" ",","))

#define RUN_BREAK(success,error) \
if ((success))\
{\
	Dt::Base::m_lastError = error;\
	break;\
}

#define CYCLE_OUTPUT(DELAY,FNC)\
QTimer* timer = new QTimer;\
QObject::connect(timer,&QTimer::timeout,FNC);\
timer->start(DELAY);

#define FUNC_NAME(X) #X

#define BUFF_SIZE 0x1000

#define NO_THROW_NEW new(std::nothrow)

#define GET_DETECTION_DIR(NAME) NAME == "功能" ?"FcLog":"HwLog"

#define AUTO_RESIZE(X) X->resize(QApplication::desktop()->screenGeometry().width() / 2 + 100,\
QApplication::desktop()->screenGeometry().height() / 2 + 100)

typedef const std::function<bool(const int&, const MsgNode&)>& MsgProc;

typedef std::initializer_list<MsgNode>&& MsgList;

typedef const std::initializer_list<int>& ReqList;

/*启动处理回调函数*/
typedef bool (*LaunchProc)(void*);

typedef bool (*LaunchProcEx)(void*, const int&, MsgProc);

/*请求处理回调函数*/
typedef bool (*RequestProc)(void*, const int&);

typedef bool (*RequestProcEx)(void*, const int&, MsgProc);

#define TS_SCAN_CODE 0x1024
#define TS_NO 0x2048

namespace BaseTypes {
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
	enum RectType { RT_FRONT_BIG, RT_REAR_BIG, RT_SMALL, RT_NO };
}

namespace AvmTypes {

}

namespace DvrTypes {
	/*DVR系统状态*/
	enum SystemStatus { SS_INITIALIZING, SS_GENERAL_RECORD, SS_PAUSE_RECORD, SS_HARDWARE_KEY, SS_CRASH_KEY, SS_UPDATE_MODE, SS_ERROR, };

	/*DVR WIFI状态*/
	enum WifiStatus { WS_CLOSE, WS_INIT, WS_NORMAL, WS_CONNECT, WS_ERROR, };

	/*DVR以太网状态*/
	enum EthernetStatus { ES_CONNECT, ES_ERROR, };

	/*DVR SD卡状态*/
	enum SdCardStatus { SCS_NORMAL, SCS_NO_SD, SCS_ERROR, SCS_NOT_FORMAT, SCS_INSUFFICIENT, SCS_RESERVED, };

	/*DVR文件类型*/
	enum FilePath { FP_NOR, FP_EVT, FP_PHO, FP_D1, FP_ALL, };

	/*格式化sd卡*/
	enum FormatSdCard { FSC_BY_NETWORK, FSC_BY_CAN, FSC_BY_UDS, };

	enum NetCmd { NC_CONNECT = 0x00, NC_FAST_CONTROL = 0x02,NC_FILE_CTRL = 0x10, NC_CONFIG_SET = 0x12 };

	enum NetSub { NS_HEART = 0x10, NS_FAST_CYCLE_RECORD = 0x00, NS_GET_FILE_LIST = 0x02, NS_FORMAT_SD_CARD = 0x20 };

	/*加密算法密钥*/
	static const size_t crc32Table[256] = { 
		0x00000000,0x77073096,0xEE0E612C,0x990951BA,0x076DC419,0x706AF48F,0xE963A535,
		0x9E6495A3,0x0EDB8832,0x79DCB8A4,0xE0D5E91E,0x97D2D988,0x09B64C2B,0x7EB17CBD,
		0xE7B82D07,0x90BF1D91,0x1DB71064,0x6AB020F2,0xF3B97148,0x84BE41DE,0x1ADAD47D,
		0x6DDDE4EB,0xF4D4B551,0x83D385C7,0x136C9856,0x646BA8C0,0xFD62F97A,0x8A65C9EC,
		0x14015C4F,0x63066CD9,0xFA0F3D63,0x8D080DF5,0x3B6E20C8,0x4C69105E,0xD56041E4,
		0xA2677172,0x3C03E4D1,0x4B04D447,0xD20D85FD,0xA50AB56B,0x35B5A8FA,0x42B2986C,
		0xDBBBC9D6,0xACBCF940,0x32D86CE3,0x45DF5C75,0xDCD60DCF,0xABD13D59,0x26D930AC,
		0x51DE003A,0xC8D75180,0xBFD06116,0x21B4F4B5,0x56B3C423,0xCFBA9599,0xB8BDA50F,
		0x2802B89E,0x5F058808,0xC60CD9B2,0xB10BE924,0x2F6F7C87,0x58684C11,0xC1611DAB,
		0xB6662D3D,0x76DC4190,0x01DB7106,0x98D220BC,0xEFD5102A,0x71B18589,0x06B6B51F,
		0x9FBFE4A5,0xE8B8D433,0x7807C9A2,0x0F00F934,0x9609A88E,0xE10E9818,0x7F6A0DBB,
		0x086D3D2D,0x91646C97,0xE6635C01,0x6B6B51F4,0x1C6C6162,0x856530D8,0xF262004E,
		0x6C0695ED,0x1B01A57B,0x8208F4C1,0xF50FC457,0x65B0D9C6,0x12B7E950,0x8BBEB8EA,
		0xFCB9887C,0x62DD1DDF,0x15DA2D49,0x8CD37CF3,0xFBD44C65,0x4DB26158,0x3AB551CE,
		0xA3BC0074,0xD4BB30E2,0x4ADFA541,0x3DD895D7,0xA4D1C46D,0xD3D6F4FB,0x4369E96A,
		0x346ED9FC,0xAD678846,0xDA60B8D0,0x44042D73,0x33031DE5,0xAA0A4C5F,0xDD0D7CC9,
		0x5005713C,0x270241AA,0xBE0B1010,0xC90C2086,0x5768B525,0x206F85B3,0xB966D409,
		0xCE61E49F,0x5EDEF90E,0x29D9C998,0xB0D09822,0xC7D7A8B4,0x59B33D17,0x2EB40D81,
		0xB7BD5C3B,0xC0BA6CAD,0xEDB88320,0x9ABFB3B6,0x03B6E20C,0x74B1D29A,0xEAD54739,
		0x9DD277AF,0x04DB2615,0x73DC1683,0xE3630B12,0x94643B84,0x0D6D6A3E,0x7A6A5AA8,
		0xE40ECF0B,0x9309FF9D,0x0A00AE27,0x7D079EB1,0xF00F9344,0x8708A3D2,0x1E01F268,
		0x6906C2FE,0xF762575D,0x806567CB,0x196C3671,0x6E6B06E7,0xFED41B76,0x89D32BE0,
		0x10DA7A5A,0x67DD4ACC,0xF9B9DF6F,0x8EBEEFF9,0x17B7BE43,0x60B08ED5,0xD6D6A3E8,
		0xA1D1937E,0x38D8C2C4,0x4FDFF252,0xD1BB67F1,0xA6BC5767,0x3FB506DD,0x48B2364B,
		0xD80D2BDA,0xAF0A1B4C,0x36034AF6,0x41047A60,0xDF60EFC3,0xA867DF55,0x316E8EEF,
		0x4669BE79,0xCB61B38C,0xBC66831A,0x256FD2A0,0x5268E236,0xCC0C7795,0xBB0B4703,
		0x220216B9,0x5505262F,0xC5BA3BBE,0xB2BD0B28,0x2BB45A92,0x5CB36A04,0xC2D7FFA7,
		0xB5D0CF31,0x2CD99E8B,0x5BDEAE1D,0x9B64C2B0,0xEC63F226,0x756AA39C,0x026D930A,
		0x9C0906A9,0xEB0E363F,0x72076785,0x05005713,0x95BF4A82,0xE2B87A14,0x7BB12BAE,
		0x0CB61B38,0x92D28E9B,0xE5D5BE0D,0x7CDCEFB7,0x0BDBDF21,0x86D3D2D4,0xF1D4E242,
		0x68DDB3F8,0x1FDA836E,0x81BE16CD,0xF6B9265B,0x6FB077E1,0x18B74777,0x88085AE6,
		0xFF0F6A70,0x66063BCA,0x11010B5C,0x8F659EFF,0xF862AE69,0x616BFFD3,0x166CCF45,
		0xA00AE278,0xD70DD2EE,0x4E048354,0x3903B3C2,0xA7672661,0xD06016F7,0x4969474D,
		0x3E6E77DB,0xAED16A4A,0xD9D65ADC,0x40DF0B66,0x37D83BF0,0xA9BCAE53,0xDEBB9EC5,
		0x47B2CF7F,0x30B5FFE9,0xBDBDF21C,0xCABAC28A,0x53B39330,0x24B4A3A6,0xBAD03605,
		0xCDD70693,0x54DE5729,0x23D967BF,0xB3667A2E,0xC4614AB8,0x5D681B02,0x2A6F2B94,
		0xB40BBE37,0xC30C8EA1,0x5A05DF1B,0x2D02EF8D
	};
}

