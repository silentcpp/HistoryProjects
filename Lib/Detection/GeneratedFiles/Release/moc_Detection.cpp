/****************************************************************************
** Meta object code from reading C++ file 'Detection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Detection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Detection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dt__Base_t {
    QByteArrayData data[28];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dt__Base_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dt__Base_t qt_meta_stringdata_Dt__Base = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Dt::Base"
QT_MOC_LITERAL(1, 9, 17), // "updateImageSignal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "image"
QT_MOC_LITERAL(4, 34, 19), // "setMessageBoxSignal"
QT_MOC_LITERAL(5, 54, 5), // "title"
QT_MOC_LITERAL(6, 60, 4), // "text"
QT_MOC_LITERAL(7, 65, 21), // "setMessageBoxExSignal"
QT_MOC_LITERAL(8, 87, 5), // "point"
QT_MOC_LITERAL(9, 93, 20), // "setQuestionBoxSignal"
QT_MOC_LITERAL(10, 114, 5), // "bool*"
QT_MOC_LITERAL(11, 120, 6), // "result"
QT_MOC_LITERAL(12, 127, 4), // "auth"
QT_MOC_LITERAL(13, 132, 22), // "setQuestionBoxExSignal"
QT_MOC_LITERAL(14, 155, 19), // "setTestResultSignal"
QT_MOC_LITERAL(15, 175, 21), // "BaseTypes::TestResult"
QT_MOC_LITERAL(16, 197, 22), // "setCurrentStatusSignal"
QT_MOC_LITERAL(17, 220, 6), // "status"
QT_MOC_LITERAL(18, 227, 6), // "append"
QT_MOC_LITERAL(19, 234, 20), // "setScanCodeDlgSignal"
QT_MOC_LITERAL(20, 255, 4), // "show"
QT_MOC_LITERAL(21, 260, 18), // "setUnlockDlgSignal"
QT_MOC_LITERAL(22, 279, 17), // "addListItemSignal"
QT_MOC_LITERAL(23, 297, 4), // "item"
QT_MOC_LITERAL(24, 302, 7), // "logItem"
QT_MOC_LITERAL(25, 310, 19), // "clearListItemSignal"
QT_MOC_LITERAL(26, 330, 16), // "setAuthDlgSignal"
QT_MOC_LITERAL(27, 347, 4) // "flag"

    },
    "Dt::Base\0updateImageSignal\0\0image\0"
    "setMessageBoxSignal\0title\0text\0"
    "setMessageBoxExSignal\0point\0"
    "setQuestionBoxSignal\0bool*\0result\0"
    "auth\0setQuestionBoxExSignal\0"
    "setTestResultSignal\0BaseTypes::TestResult\0"
    "setCurrentStatusSignal\0status\0append\0"
    "setScanCodeDlgSignal\0show\0setUnlockDlgSignal\0"
    "addListItemSignal\0item\0logItem\0"
    "clearListItemSignal\0setAuthDlgSignal\0"
    "flag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dt__Base[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    2,   77,    2, 0x06 /* Public */,
       7,    3,   82,    2, 0x06 /* Public */,
       9,    4,   89,    2, 0x06 /* Public */,
      13,    4,   98,    2, 0x06 /* Public */,
      14,    1,  107,    2, 0x06 /* Public */,
      16,    2,  110,    2, 0x06 /* Public */,
      19,    1,  115,    2, 0x06 /* Public */,
      21,    1,  118,    2, 0x06 /* Public */,
      22,    2,  121,    2, 0x06 /* Public */,
      25,    0,  126,    2, 0x06 /* Public */,
      26,    2,  127,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QPoint,    5,    6,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 10, QMetaType::Bool,    5,    6,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 10, QMetaType::QPoint,    5,    6,   11,    8,
    QMetaType::Void, 0x80000000 | 15,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   17,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   23,   24,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   27,

       0        // eod
};

void Dt::Base::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Base *_t = static_cast<Base *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateImageSignal((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->setMessageBoxSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->setMessageBoxExSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QPoint(*)>(_a[3]))); break;
        case 3: _t->setQuestionBoxSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool*(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 4: _t->setQuestionBoxExSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool*(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        case 5: _t->setTestResultSignal((*reinterpret_cast< const BaseTypes::TestResult(*)>(_a[1]))); break;
        case 6: _t->setCurrentStatusSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->setScanCodeDlgSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setUnlockDlgSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->addListItemSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->clearListItemSignal(); break;
        case 11: _t->setAuthDlgSignal((*reinterpret_cast< bool*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Base::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::updateImageSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Base::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setMessageBoxSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Base::*_t)(const QString & , const QString & , const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setMessageBoxExSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Base::*_t)(const QString & , const QString & , bool * , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setQuestionBoxSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Base::*_t)(const QString & , const QString & , bool * , const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setQuestionBoxExSignal)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Base::*_t)(const BaseTypes::TestResult & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setTestResultSignal)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Base::*_t)(const QString & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setCurrentStatusSignal)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Base::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setScanCodeDlgSignal)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Base::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setUnlockDlgSignal)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Base::*_t)(const QString & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::addListItemSignal)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (Base::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::clearListItemSignal)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (Base::*_t)(bool * , const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Base::setAuthDlgSignal)) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject Dt::Base::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Dt__Base.data,
      qt_meta_data_Dt__Base,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dt::Base::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dt::Base::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dt__Base.stringdata0))
        return static_cast<void*>(const_cast< Base*>(this));
    return QThread::qt_metacast(_clname);
}

int Dt::Base::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Dt::Base::updateImageSignal(const QImage & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dt::Base::setMessageBoxSignal(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Dt::Base::setMessageBoxExSignal(const QString & _t1, const QString & _t2, const QPoint & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Dt::Base::setQuestionBoxSignal(const QString & _t1, const QString & _t2, bool * _t3, bool _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Dt::Base::setQuestionBoxExSignal(const QString & _t1, const QString & _t2, bool * _t3, const QPoint & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Dt::Base::setTestResultSignal(const BaseTypes::TestResult & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Dt::Base::setCurrentStatusSignal(const QString & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Dt::Base::setScanCodeDlgSignal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Dt::Base::setUnlockDlgSignal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Dt::Base::addListItemSignal(const QString & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Dt::Base::clearListItemSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void Dt::Base::setAuthDlgSignal(bool * _t1, const int & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
struct qt_meta_stringdata_Dt__Hardware_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dt__Hardware_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dt__Hardware_t qt_meta_stringdata_Dt__Hardware = {
    {
QT_MOC_LITERAL(0, 0, 12) // "Dt::Hardware"

    },
    "Dt::Hardware"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dt__Hardware[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Dt::Hardware::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Dt::Hardware::staticMetaObject = {
    { &Base::staticMetaObject, qt_meta_stringdata_Dt__Hardware.data,
      qt_meta_data_Dt__Hardware,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dt::Hardware::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dt::Hardware::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dt__Hardware.stringdata0))
        return static_cast<void*>(const_cast< Hardware*>(this));
    return Base::qt_metacast(_clname);
}

int Dt::Hardware::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Base::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Dt__Function_t {
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dt__Function_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dt__Function_t qt_meta_stringdata_Dt__Function = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Dt::Function"
QT_MOC_LITERAL(1, 13, 19), // "getChannelImageSlot"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "channelID"
QT_MOC_LITERAL(4, 44, 15), // "const IplImage*"
QT_MOC_LITERAL(5, 60, 5) // "image"

    },
    "Dt::Function\0getChannelImageSlot\0\0"
    "channelID\0const IplImage*\0image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dt__Function[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,

       0        // eod
};

void Dt::Function::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Function *_t = static_cast<Function *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getChannelImageSlot((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const IplImage*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject Dt::Function::staticMetaObject = {
    { &Base::staticMetaObject, qt_meta_stringdata_Dt__Function.data,
      qt_meta_data_Dt__Function,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dt::Function::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dt::Function::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dt__Function.stringdata0))
        return static_cast<void*>(const_cast< Function*>(this));
    return Base::qt_metacast(_clname);
}

int Dt::Function::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Base::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_Dt__Avm_t {
    QByteArrayData data[1];
    char stringdata0[8];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dt__Avm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dt__Avm_t qt_meta_stringdata_Dt__Avm = {
    {
QT_MOC_LITERAL(0, 0, 7) // "Dt::Avm"

    },
    "Dt::Avm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dt__Avm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Dt::Avm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Dt::Avm::staticMetaObject = {
    { &Function::staticMetaObject, qt_meta_stringdata_Dt__Avm.data,
      qt_meta_data_Dt__Avm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dt::Avm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dt::Avm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dt__Avm.stringdata0))
        return static_cast<void*>(const_cast< Avm*>(this));
    return Function::qt_metacast(_clname);
}

int Dt::Avm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Function::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Dt__Dvr_t {
    QByteArrayData data[1];
    char stringdata0[8];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dt__Dvr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dt__Dvr_t qt_meta_stringdata_Dt__Dvr = {
    {
QT_MOC_LITERAL(0, 0, 7) // "Dt::Dvr"

    },
    "Dt::Dvr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dt__Dvr[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Dt::Dvr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Dt::Dvr::staticMetaObject = {
    { &Function::staticMetaObject, qt_meta_stringdata_Dt__Dvr.data,
      qt_meta_data_Dt__Dvr,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dt::Dvr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dt::Dvr::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dt__Dvr.stringdata0))
        return static_cast<void*>(const_cast< Dvr*>(this));
    return Function::qt_metacast(_clname);
}

int Dt::Dvr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Function::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Dt__Tap_t {
    QByteArrayData data[1];
    char stringdata0[8];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dt__Tap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dt__Tap_t qt_meta_stringdata_Dt__Tap = {
    {
QT_MOC_LITERAL(0, 0, 7) // "Dt::Tap"

    },
    "Dt::Tap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dt__Tap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Dt::Tap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Dt::Tap::staticMetaObject = {
    { &Function::staticMetaObject, qt_meta_stringdata_Dt__Tap.data,
      qt_meta_data_Dt__Tap,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dt::Tap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dt::Tap::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dt__Tap.stringdata0))
        return static_cast<void*>(const_cast< Tap*>(this));
    return Function::qt_metacast(_clname);
}

int Dt::Tap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Function::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Dt__Module_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dt__Module_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dt__Module_t qt_meta_stringdata_Dt__Module = {
    {
QT_MOC_LITERAL(0, 0, 10) // "Dt::Module"

    },
    "Dt::Module"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dt__Module[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Dt::Module::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Dt::Module::staticMetaObject = {
    { &Dvr::staticMetaObject, qt_meta_stringdata_Dt__Module.data,
      qt_meta_data_Dt__Module,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dt::Module::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dt::Module::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dt__Module.stringdata0))
        return static_cast<void*>(const_cast< Module*>(this));
    return Dvr::qt_metacast(_clname);
}

int Dt::Module::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Dvr::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
