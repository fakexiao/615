/****************************************************************************
** Meta object code from reading C++ file 'linesandpoints.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/linesandpoints.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'linesandpoints.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LinesAndPoints_t {
    QByteArrayData data[9];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LinesAndPoints_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LinesAndPoints_t qt_meta_stringdata_LinesAndPoints = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LinesAndPoints"
QT_MOC_LITERAL(1, 15, 15), // "geometryClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "Geometry*"
QT_MOC_LITERAL(4, 42, 4), // "geom"
QT_MOC_LITERAL(5, 47, 8), // "coord_px"
QT_MOC_LITERAL(6, 56, 11), // "resizeEvent"
QT_MOC_LITERAL(7, 68, 13), // "QResizeEvent*"
QT_MOC_LITERAL(8, 82, 6) // "qEvent"

    },
    "LinesAndPoints\0geometryClicked\0\0"
    "Geometry*\0geom\0coord_px\0resizeEvent\0"
    "QResizeEvent*\0qEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinesAndPoints[] = {

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
       1,    2,   24,    2, 0x0a /* Public */,
       6,    1,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPoint,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void LinesAndPoints::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LinesAndPoints *_t = static_cast<LinesAndPoints *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->geometryClicked((*reinterpret_cast< Geometry*(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 1: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Geometry* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LinesAndPoints::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LinesAndPoints.data,
      qt_meta_data_LinesAndPoints,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LinesAndPoints::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinesAndPoints::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinesAndPoints.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LinesAndPoints::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
