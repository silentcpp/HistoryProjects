/****************************************************************************
** Meta object code from reading C++ file 'SettingDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SettingDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SettingDlg_t {
    QByteArrayData data[20];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingDlg_t qt_meta_stringdata_SettingDlg = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SettingDlg"
QT_MOC_LITERAL(1, 11, 16), // "setAuthDlgSignal"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "bool*"
QT_MOC_LITERAL(4, 35, 6), // "result"
QT_MOC_LITERAL(5, 42, 4), // "flag"
QT_MOC_LITERAL(6, 47, 21), // "addCanTableItemSignal"
QT_MOC_LITERAL(7, 69, 11), // "const char*"
QT_MOC_LITERAL(8, 81, 4), // "type"
QT_MOC_LITERAL(9, 86, 7), // "MsgNode"
QT_MOC_LITERAL(10, 94, 3), // "msg"
QT_MOC_LITERAL(11, 98, 25), // "configTreeItemPressedSlot"
QT_MOC_LITERAL(12, 124, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(13, 141, 4), // "item"
QT_MOC_LITERAL(14, 146, 6), // "column"
QT_MOC_LITERAL(15, 153, 31), // "configTreeItemDoubleClickedSlot"
QT_MOC_LITERAL(16, 185, 25), // "configTreeItemChangedSlot"
QT_MOC_LITERAL(17, 211, 19), // "addCanTableItemSlot"
QT_MOC_LITERAL(18, 231, 15), // "canBaseSendSlot"
QT_MOC_LITERAL(19, 247, 15) // "canBaseStopSlot"

    },
    "SettingDlg\0setAuthDlgSignal\0\0bool*\0"
    "result\0flag\0addCanTableItemSignal\0"
    "const char*\0type\0MsgNode\0msg\0"
    "configTreeItemPressedSlot\0QTreeWidgetItem*\0"
    "item\0column\0configTreeItemDoubleClickedSlot\0"
    "configTreeItemChangedSlot\0addCanTableItemSlot\0"
    "canBaseSendSlot\0canBaseStopSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    2,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   64,    2, 0x0a /* Public */,
      15,    2,   69,    2, 0x0a /* Public */,
      16,    2,   74,    2, 0x0a /* Public */,
      17,    2,   79,    2, 0x0a /* Public */,
      18,    0,   84,    2, 0x0a /* Public */,
      19,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,   14,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,   14,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,   14,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingDlg *_t = static_cast<SettingDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setAuthDlgSignal((*reinterpret_cast< bool*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: _t->addCanTableItemSignal((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< const MsgNode(*)>(_a[2]))); break;
        case 2: _t->configTreeItemPressedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->configTreeItemDoubleClickedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->configTreeItemChangedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->addCanTableItemSlot((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< const MsgNode(*)>(_a[2]))); break;
        case 6: _t->canBaseSendSlot(); break;
        case 7: _t->canBaseStopSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SettingDlg::*_t)(bool * , const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingDlg::setAuthDlgSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SettingDlg::*_t)(const char * , const MsgNode & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingDlg::addCanTableItemSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SettingDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SettingDlg.data,
      qt_meta_data_SettingDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SettingDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SettingDlg.stringdata0))
        return static_cast<void*>(const_cast< SettingDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int SettingDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SettingDlg::setAuthDlgSignal(bool * _t1, const int & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingDlg::addCanTableItemSignal(const char * _t1, const MsgNode & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE