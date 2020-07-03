/****************************************************************************
** Meta object code from reading C++ file 'ThreadHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ThreadHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ThreadHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ThreadHandler_t {
    QByteArrayData data[7];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadHandler_t qt_meta_stringdata_ThreadHandler = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ThreadHandler"
QT_MOC_LITERAL(1, 14, 19), // "setMessageBoxSignal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "title"
QT_MOC_LITERAL(4, 41, 4), // "text"
QT_MOC_LITERAL(5, 46, 17), // "scanCodeDlgSignal"
QT_MOC_LITERAL(6, 64, 6) // "number"

    },
    "ThreadHandler\0setMessageBoxSignal\0\0"
    "title\0text\0scanCodeDlgSignal\0number"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       5,    1,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void ThreadHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ThreadHandler *_t = static_cast<ThreadHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMessageBoxSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->scanCodeDlgSignal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ThreadHandler::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ThreadHandler::setMessageBoxSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ThreadHandler::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ThreadHandler::scanCodeDlgSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ThreadHandler::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ThreadHandler.data,
      qt_meta_data_ThreadHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ThreadHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadHandler.stringdata0))
        return static_cast<void*>(const_cast< ThreadHandler*>(this));
    return QThread::qt_metacast(_clname);
}

int ThreadHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ThreadHandler::setMessageBoxSignal(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadHandler::scanCodeDlgSignal(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WorkThread_t {
    QByteArrayData data[16];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkThread_t qt_meta_stringdata_WorkThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WorkThread"
QT_MOC_LITERAL(1, 11, 20), // "updateProgressSignal"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "progress"
QT_MOC_LITERAL(4, 42, 25), // "updateCurrentStatusSiganl"
QT_MOC_LITERAL(5, 68, 6), // "status"
QT_MOC_LITERAL(6, 75, 22), // "updateBurnStatusSiganl"
QT_MOC_LITERAL(7, 98, 12), // "burnStatus_t"
QT_MOC_LITERAL(8, 111, 3), // "err"
QT_MOC_LITERAL(9, 115, 22), // "updateGroupTitleSignal"
QT_MOC_LITERAL(10, 138, 5), // "title"
QT_MOC_LITERAL(11, 144, 21), // "setBurnTimerRunSignal"
QT_MOC_LITERAL(12, 166, 3), // "run"
QT_MOC_LITERAL(13, 170, 17), // "progressTimerSlot"
QT_MOC_LITERAL(14, 188, 20), // "getBurnTimerTimeSlot"
QT_MOC_LITERAL(15, 209, 4) // "data"

    },
    "WorkThread\0updateProgressSignal\0\0"
    "progress\0updateCurrentStatusSiganl\0"
    "status\0updateBurnStatusSiganl\0"
    "burnStatus_t\0err\0updateGroupTitleSignal\0"
    "title\0setBurnTimerRunSignal\0run\0"
    "progressTimerSlot\0getBurnTimerTimeSlot\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    2,   55,    2, 0x06 /* Public */,
       9,    1,   60,    2, 0x06 /* Public */,
      11,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   66,    2, 0x0a /* Public */,
      14,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    5,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Bool,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void WorkThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorkThread *_t = static_cast<WorkThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateProgressSignal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->updateCurrentStatusSiganl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateBurnStatusSiganl((*reinterpret_cast< const burnStatus_t(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->updateGroupTitleSignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setBurnTimerRunSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->progressTimerSlot(); break;
        case 6: _t->getBurnTimerTimeSlot((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WorkThread::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkThread::updateProgressSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WorkThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkThread::updateCurrentStatusSiganl)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WorkThread::*_t)(const burnStatus_t & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkThread::updateBurnStatusSiganl)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WorkThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkThread::updateGroupTitleSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (WorkThread::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkThread::setBurnTimerRunSignal)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject WorkThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkThread.data,
      qt_meta_data_WorkThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkThread.stringdata0))
        return static_cast<void*>(const_cast< WorkThread*>(this));
    return QThread::qt_metacast(_clname);
}

int WorkThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void WorkThread::updateProgressSignal(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WorkThread::updateCurrentStatusSiganl(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WorkThread::updateBurnStatusSiganl(const burnStatus_t & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WorkThread::updateGroupTitleSignal(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WorkThread::setBurnTimerRunSignal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
