/****************************************************************************
** Meta object code from reading C++ file 'UpdateDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UpdateDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UpdateDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UpdateDlg_t {
    QByteArrayData data[17];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpdateDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpdateDlg_t qt_meta_stringdata_UpdateDlg = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UpdateDlg"
QT_MOC_LITERAL(1, 10, 20), // "setQuestionBoxSignal"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "title"
QT_MOC_LITERAL(4, 38, 4), // "text"
QT_MOC_LITERAL(5, 43, 5), // "bool*"
QT_MOC_LITERAL(6, 49, 6), // "result"
QT_MOC_LITERAL(7, 56, 17), // "setProgressSignal"
QT_MOC_LITERAL(8, 74, 16), // "setShowDlgSignal"
QT_MOC_LITERAL(9, 91, 14), // "setTitleSignal"
QT_MOC_LITERAL(10, 106, 13), // "restartSignal"
QT_MOC_LITERAL(11, 120, 4), // "name"
QT_MOC_LITERAL(12, 125, 18), // "setQuestionBoxSlot"
QT_MOC_LITERAL(13, 144, 15), // "setProgressSlot"
QT_MOC_LITERAL(14, 160, 14), // "setShowDlgSlot"
QT_MOC_LITERAL(15, 175, 4), // "show"
QT_MOC_LITERAL(16, 180, 12) // "setTitleSlot"

    },
    "UpdateDlg\0setQuestionBoxSignal\0\0title\0"
    "text\0bool*\0result\0setProgressSignal\0"
    "setShowDlgSignal\0setTitleSignal\0"
    "restartSignal\0name\0setQuestionBoxSlot\0"
    "setProgressSlot\0setShowDlgSlot\0show\0"
    "setTitleSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpdateDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,
       7,    3,   66,    2, 0x06 /* Public */,
       8,    1,   73,    2, 0x06 /* Public */,
       9,    1,   76,    2, 0x06 /* Public */,
      10,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    3,   82,    2, 0x0a /* Public */,
      13,    3,   89,    2, 0x0a /* Public */,
      14,    1,   96,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::ULong, QMetaType::ULong, QMetaType::ULong,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::ULong, QMetaType::ULong, QMetaType::ULong,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void UpdateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UpdateDlg *_t = static_cast<UpdateDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setQuestionBoxSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool*(*)>(_a[3]))); break;
        case 1: _t->setProgressSignal((*reinterpret_cast< ulong(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< ulong(*)>(_a[3]))); break;
        case 2: _t->setShowDlgSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setTitleSignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->restartSignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setQuestionBoxSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool*(*)>(_a[3]))); break;
        case 6: _t->setProgressSlot((*reinterpret_cast< ulong(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< ulong(*)>(_a[3]))); break;
        case 7: _t->setShowDlgSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setTitleSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UpdateDlg::*_t)(const QString & , const QString & , bool * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateDlg::setQuestionBoxSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UpdateDlg::*_t)(ulong , ulong , ulong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateDlg::setProgressSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (UpdateDlg::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateDlg::setShowDlgSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (UpdateDlg::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateDlg::setTitleSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (UpdateDlg::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateDlg::restartSignal)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject UpdateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UpdateDlg.data,
      qt_meta_data_UpdateDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UpdateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpdateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateDlg.stringdata0))
        return static_cast<void*>(const_cast< UpdateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int UpdateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void UpdateDlg::setQuestionBoxSignal(const QString & _t1, const QString & _t2, bool * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UpdateDlg::setProgressSignal(ulong _t1, ulong _t2, ulong _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UpdateDlg::setShowDlgSignal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UpdateDlg::setTitleSignal(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UpdateDlg::restartSignal(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
