/****************************************************************************
** Meta object code from reading C++ file 'DownloadDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DownloadDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DownloadDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DownloadDlg_t {
    QByteArrayData data[10];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DownloadDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DownloadDlg_t qt_meta_stringdata_DownloadDlg = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DownloadDlg"
QT_MOC_LITERAL(1, 12, 10), // "resultSlot"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 14), // "DownloadResult"
QT_MOC_LITERAL(4, 39, 6), // "result"
QT_MOC_LITERAL(5, 46, 5), // "error"
QT_MOC_LITERAL(6, 52, 12), // "progressSlot"
QT_MOC_LITERAL(7, 65, 7), // "receive"
QT_MOC_LITERAL(8, 73, 5), // "total"
QT_MOC_LITERAL(9, 79, 5) // "speed"

    },
    "DownloadDlg\0resultSlot\0\0DownloadResult\0"
    "result\0error\0progressSlot\0receive\0"
    "total\0speed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DownloadDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x08 /* Private */,
       6,    3,   29,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::Float,    7,    8,    9,

       0        // eod
};

void DownloadDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DownloadDlg *_t = static_cast<DownloadDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultSlot((*reinterpret_cast< const DownloadResult(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->progressSlot((*reinterpret_cast< const qint64(*)>(_a[1])),(*reinterpret_cast< const qint64(*)>(_a[2])),(*reinterpret_cast< const float(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject DownloadDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DownloadDlg.data,
      qt_meta_data_DownloadDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DownloadDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DownloadDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DownloadDlg.stringdata0))
        return static_cast<void*>(const_cast< DownloadDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int DownloadDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
