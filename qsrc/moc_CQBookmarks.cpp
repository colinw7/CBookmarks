/****************************************************************************
** Meta object code from reading C++ file 'CQBookmarks.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CQBookmarks.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQBookmarks.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQBookmarks_t {
    QByteArrayData data[5];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQBookmarks_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQBookmarks_t qt_meta_stringdata_CQBookmarks = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CQBookmarks"
QT_MOC_LITERAL(1, 12, 16), // "treeItemSelected"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 47, 4) // "item"

    },
    "CQBookmarks\0treeItemSelected\0\0"
    "QTreeWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQBookmarks[] = {

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
       1,    2,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    2,

       0        // eod
};

void CQBookmarks::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQBookmarks *_t = static_cast<CQBookmarks *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->treeItemSelected((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CQBookmarks::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CQBookmarks.data,
      qt_meta_data_CQBookmarks,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQBookmarks::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQBookmarks::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQBookmarks.stringdata0))
        return static_cast<void*>(const_cast< CQBookmarks*>(this));
    return QWidget::qt_metacast(_clname);
}

int CQBookmarks::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_CQBookmarksTree_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQBookmarksTree_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQBookmarksTree_t qt_meta_stringdata_CQBookmarksTree = {
    {
QT_MOC_LITERAL(0, 0, 15) // "CQBookmarksTree"

    },
    "CQBookmarksTree"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQBookmarksTree[] = {

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

void CQBookmarksTree::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CQBookmarksTree::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_CQBookmarksTree.data,
      qt_meta_data_CQBookmarksTree,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQBookmarksTree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQBookmarksTree::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQBookmarksTree.stringdata0))
        return static_cast<void*>(const_cast< CQBookmarksTree*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int CQBookmarksTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_CQBookmarksInfo_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQBookmarksInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQBookmarksInfo_t qt_meta_stringdata_CQBookmarksInfo = {
    {
QT_MOC_LITERAL(0, 0, 15) // "CQBookmarksInfo"

    },
    "CQBookmarksInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQBookmarksInfo[] = {

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

void CQBookmarksInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CQBookmarksInfo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CQBookmarksInfo.data,
      qt_meta_data_CQBookmarksInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQBookmarksInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQBookmarksInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQBookmarksInfo.stringdata0))
        return static_cast<void*>(const_cast< CQBookmarksInfo*>(this));
    return QWidget::qt_metacast(_clname);
}

int CQBookmarksInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
