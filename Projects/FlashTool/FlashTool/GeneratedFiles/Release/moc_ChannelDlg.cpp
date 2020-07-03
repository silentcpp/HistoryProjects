/****************************************************************************
** Meta object code from reading C++ file 'ChannelDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ChannelDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChannelDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChannelDlg_t {
    QByteArrayData data[16];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChannelDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChannelDlg_t qt_meta_stringdata_ChannelDlg = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChannelDlg"
QT_MOC_LITERAL(1, 11, 22), // "getBurnTimerTimeSignal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "data"
QT_MOC_LITERAL(4, 40, 18), // "updateProgressSlot"
QT_MOC_LITERAL(5, 59, 8), // "progress"
QT_MOC_LITERAL(6, 68, 23), // "updateCurrentStatusSlot"
QT_MOC_LITERAL(7, 92, 6), // "status"
QT_MOC_LITERAL(8, 99, 20), // "updateBurnStatusSlot"
QT_MOC_LITERAL(9, 120, 12), // "burnStatus_t"
QT_MOC_LITERAL(10, 133, 3), // "err"
QT_MOC_LITERAL(11, 137, 20), // "updateGroupTitleSlot"
QT_MOC_LITERAL(12, 158, 5), // "title"
QT_MOC_LITERAL(13, 164, 19), // "setBurnTimerRunSlot"
QT_MOC_LITERAL(14, 184, 2), // "go"
QT_MOC_LITERAL(15, 187, 20) // "burnTimerTimeoutSlot"

    },
    "ChannelDlg\0getBurnTimerTimeSignal\0\0"
    "data\0updateProgressSlot\0progress\0"
    "updateCurrentStatusSlot\0status\0"
    "updateBurnStatusSlot\0burnStatus_t\0err\0"
    "updateGroupTitleSlot\0title\0"
    "setBurnTimerRunSlot\0go\0burnTimerTimeoutSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChannelDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       8,    2,   58,    2, 0x0a /* Public */,
      11,    1,   63,    2, 0x0a /* Public */,
      13,    1,   66,    2, 0x0a /* Public */,
      15,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,    7,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,

       0        // eod
};

void ChannelDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChannelDlg *_t = static_cast<ChannelDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getBurnTimerTimeSignal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->updateProgressSlot((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->updateCurrentStatusSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateBurnStatusSlot((*reinterpret_cast< const burnStatus_t(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->updateGroupTitleSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setBurnTimerRunSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->burnTimerTimeoutSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChannelDlg::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChannelDlg::getBurnTimerTimeSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ChannelDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChannelDlg.data,
      qt_meta_data_ChannelDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ChannelDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChannelDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ChannelDlg.stringdata0))
        return static_cast<void*>(const_cast< ChannelDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int ChannelDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ChannelDlg::getBurnTimerTimeSignal(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
