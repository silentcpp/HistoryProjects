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
/* 此C++代码为硬件 功能[AVM DVR TAP]检测框架		*/
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
	};
}

