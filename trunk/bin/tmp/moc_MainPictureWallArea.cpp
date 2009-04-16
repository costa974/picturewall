/****************************************************************************
** Meta object code from reading C++ file 'MainPictureWallArea.h'
**
** Created: Thu Apr 16 21:17:01 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/MainPictureWallArea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainPictureWallArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMainPictureWallArea[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      36,   22,   21,   21, 0x0a,
      88,   84,   21,   21, 0x0a,
     131,  119,   21,   21, 0x0a,
     177,  171,   21,   21, 0x0a,
     213,   21,   21,   21, 0x0a,
     262,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CMainPictureWallArea[] = {
    "CMainPictureWallArea\0\0directoryPath\0"
    "loadImagesFromDirectoryRecursivelySlot(QString)\0"
    "num\0showImageOnWallAtPosition(int)\0"
    "factor,zoom\0changeZoomLevelByFactor(int,EZoomFocus)\0"
    "steps\0updateScrollingAnimationStep(qreal)\0"
    "scrollingAnimationStateChanged(QTimeLine::State)\0"
    "scrollingAnimationFinsihed()\0"
};

const QMetaObject CMainPictureWallArea::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_CMainPictureWallArea,
      qt_meta_data_CMainPictureWallArea, 0 }
};

const QMetaObject *CMainPictureWallArea::metaObject() const
{
    return &staticMetaObject;
}

void *CMainPictureWallArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMainPictureWallArea))
        return static_cast<void*>(const_cast< CMainPictureWallArea*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int CMainPictureWallArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadImagesFromDirectoryRecursivelySlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: showImageOnWallAtPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: changeZoomLevelByFactor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< EZoomFocus(*)>(_a[2]))); break;
        case 3: updateScrollingAnimationStep((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: scrollingAnimationStateChanged((*reinterpret_cast< QTimeLine::State(*)>(_a[1]))); break;
        case 5: scrollingAnimationFinsihed(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
