/****************************************************************************
** Meta object code from reading C++ file 'PhotoPrinter.h'
**
** Created: Thu 28. Apr 00:39:11 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/PhotoPrinter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PhotoPrinter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PhotoPrinter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      24,   13,   13,   13, 0x0a,
      43,   35,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PhotoPrinter[] = {
    "PhotoPrinter\0\0capture()\0setPrefs()\0"
    "printer\0drawPage(QPrinter*)\0"
};

const QMetaObject PhotoPrinter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PhotoPrinter,
      qt_meta_data_PhotoPrinter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PhotoPrinter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PhotoPrinter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PhotoPrinter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhotoPrinter))
        return static_cast<void*>(const_cast< PhotoPrinter*>(this));
    return QObject::qt_metacast(_clname);
}

int PhotoPrinter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: capture(); break;
        case 1: setPrefs(); break;
        case 2: drawPage((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
