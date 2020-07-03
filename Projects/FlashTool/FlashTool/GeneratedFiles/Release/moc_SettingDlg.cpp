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
    QByteArrayData data[16];
    char stringdata0[226];
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
QT_MOC_LITERAL(4, 35, 20), // "updateTypeNameSignal"
QT_MOC_LITERAL(5, 56, 15), // "itemPressedSlot"
QT_MOC_LITERAL(6, 72, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(7, 89, 4), // "item"
QT_MOC_LITERAL(8, 94, 6), // "column"
QT_MOC_LITERAL(9, 101, 21), // "itemDoubleClickedSlot"
QT_MOC_LITERAL(10, 123, 15), // "itemChangedSlot"
QT_MOC_LITERAL(11, 139, 12), // "saveDataSlot"
QT_MOC_LITERAL(12, 152, 13), // "expandAllSlot"
QT_MOC_LITERAL(13, 166, 9), // "closeSlot"
QT_MOC_LITERAL(14, 176, 24), // "appendFileConfigNodeSlot"
QT_MOC_LITERAL(15, 201, 24) // "deleteFileConfigNodeSlot"

    },
    "SettingDlg\0setAuthDlgSignal\0\0bool*\0"
    "updateTypeNameSignal\0itemPressedSlot\0"
    "QTreeWidgetItem*\0item\0column\0"
    "itemDoubleClickedSlot\0itemChangedSlot\0"
    "saveDataSlot\0expandAllSlot\0closeSlot\0"
    "appendFileConfigNodeSlot\0"
    "deleteFileConfigNodeSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   68,    2, 0x0a /* Public */,
       9,    2,   73,    2, 0x0a /* Public */,
      10,    2,   78,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x0a /* Public */,
      15,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 0: _t->setAuthDlgSignal((*reinterpret_cast< bool*(*)>(_a[1]))); break;
        case 1: _t->updateTypeNameSignal(); break;
        case 2: _t->itemPressedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->itemDoubleClickedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->itemChangedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->saveDataSlot(); break;
        case 6: _t->expandAllSlot(); break;
        case 7: _t->closeSlot(); break;
        case 8: _t->appendFileConfigNodeSlot(); break;
        case 9: _t->deleteFileConfigNodeSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SettingDlg::*_t)(bool * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingDlg::setAuthDlgSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SettingDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingDlg::updateTypeNameSignal)) {
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SettingDlg::setAuthDlgSignal(bool * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingDlg::updateTypeNameSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
