/****************************************************************************
** Meta object code from reading C++ file 'MainDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MainDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainDlg_t {
    QByteArrayData data[15];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainDlg_t qt_meta_stringdata_MainDlg = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MainDlg"
QT_MOC_LITERAL(1, 8, 17), // "settingButtonSlot"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "connectButtonSlot"
QT_MOC_LITERAL(4, 45, 14), // "exitButtonSlot"
QT_MOC_LITERAL(5, 60, 16), // "reloadButtonSlot"
QT_MOC_LITERAL(6, 77, 17), // "setMessageBoxSlot"
QT_MOC_LITERAL(7, 95, 5), // "title"
QT_MOC_LITERAL(8, 101, 4), // "text"
QT_MOC_LITERAL(9, 106, 15), // "scanCodeDlgSlot"
QT_MOC_LITERAL(10, 122, 6), // "number"
QT_MOC_LITERAL(11, 129, 19), // "typeNameCorrectSlot"
QT_MOC_LITERAL(12, 149, 8), // "typeName"
QT_MOC_LITERAL(13, 158, 21), // "cpuUsageRateTimerSlot"
QT_MOC_LITERAL(14, 180, 18) // "updateTypeNameSlot"

    },
    "MainDlg\0settingButtonSlot\0\0connectButtonSlot\0"
    "exitButtonSlot\0reloadButtonSlot\0"
    "setMessageBoxSlot\0title\0text\0"
    "scanCodeDlgSlot\0number\0typeNameCorrectSlot\0"
    "typeName\0cpuUsageRateTimerSlot\0"
    "updateTypeNameSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    2,   63,    2, 0x0a /* Public */,
       9,    1,   68,    2, 0x0a /* Public */,
      11,    1,   71,    2, 0x0a /* Public */,
      13,    0,   74,    2, 0x0a /* Public */,
      14,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainDlg *_t = static_cast<MainDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingButtonSlot(); break;
        case 1: _t->connectButtonSlot(); break;
        case 2: _t->exitButtonSlot(); break;
        case 3: _t->reloadButtonSlot(); break;
        case 4: _t->setMessageBoxSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->scanCodeDlgSlot((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->typeNameCorrectSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->cpuUsageRateTimerSlot(); break;
        case 8: _t->updateTypeNameSlot(); break;
        default: ;
        }
    }
}

const QMetaObject MainDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainDlg.data,
      qt_meta_data_MainDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainDlg.stringdata0))
        return static_cast<void*>(const_cast< MainDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
