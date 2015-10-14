/****************************************************************************
** Meta object code from reading C++ file 'qtdensity.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtdensity.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtdensity.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtDensity[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   11,   10,   10, 0x08,
      39,   32,   10,   10, 0x08,
      58,   54,   10,   10, 0x08,
      84,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtDensity[] = {
    "QtDensity\0\0bw\0getBandwidth(int)\0kernel\0"
    "getKernel(int)\0txt\0getRandomDataCmd(QString)\0"
    "runRandomDataCmd()\0"
};

void QtDensity::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtDensity *_t = static_cast<QtDensity *>(_o);
        switch (_id) {
        case 0: _t->getBandwidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->getKernel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->getRandomDataCmd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->runRandomDataCmd(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtDensity::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtDensity::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtDensity,
      qt_meta_data_QtDensity, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtDensity::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtDensity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtDensity::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtDensity))
        return static_cast<void*>(const_cast< QtDensity*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtDensity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
