/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../23AD11044_LeVanNhan/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "PaginationInWidget",
    "",
    "QTreeWidget*",
    "treeWidget",
    "BSTPhone*",
    "treeRoot",
    "ShowPage",
    "widget",
    "std::vector<PhoneInformation>",
    "nodes",
    "currentPage",
    "showTreeInWidget",
    "CopyTree",
    "node",
    "btnPrePage_2_clicked",
    "btnNextP_2_clicked",
    "treeWidget_itemClicked",
    "QTreeWidgetItem*",
    "item",
    "column",
    "btnAdd_2_clicked",
    "btnDelete_2_clicked",
    "btnUpdate_2_clicked",
    "btnSave_clicked",
    "btnClear_clicked",
    "cbSort_2_currentIndexChanged",
    "index",
    "onPageChanged",
    "page",
    "onChangedIndex",
    "btnFilter_clicked",
    "onSearchTextChanged",
    "text",
    "cbSearch_2_currentIndexChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  122,    2, 0x08,    1 /* Private */,
       7,    3,  127,    2, 0x08,    4 /* Private */,
      12,    2,  134,    2, 0x08,    8 /* Private */,
      13,    1,  139,    2, 0x08,   11 /* Private */,
      15,    0,  142,    2, 0x08,   13 /* Private */,
      16,    0,  143,    2, 0x08,   14 /* Private */,
      17,    2,  144,    2, 0x08,   15 /* Private */,
      21,    0,  149,    2, 0x08,   18 /* Private */,
      22,    0,  150,    2, 0x08,   19 /* Private */,
      23,    0,  151,    2, 0x08,   20 /* Private */,
      24,    0,  152,    2, 0x08,   21 /* Private */,
      25,    0,  153,    2, 0x08,   22 /* Private */,
      26,    1,  154,    2, 0x08,   23 /* Private */,
      28,    1,  157,    2, 0x08,   25 /* Private */,
      30,    0,  160,    2, 0x08,   27 /* Private */,
      31,    0,  161,    2, 0x08,   28 /* Private */,
      32,    1,  162,    2, 0x08,   29 /* Private */,
      34,    1,  165,    2, 0x08,   31 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    0x80000000 | 5, 0x80000000 | 5,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Int,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::Int,   27,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'PaginationInWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<BSTPhone *, std::false_type>,
        // method 'ShowPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<PhoneInformation> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'showTreeInWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<BSTPhone *, std::false_type>,
        // method 'CopyTree'
        QtPrivate::TypeAndForceComplete<BSTPhone *, std::false_type>,
        QtPrivate::TypeAndForceComplete<BSTPhone *, std::false_type>,
        // method 'btnPrePage_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'btnNextP_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'treeWidget_itemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'btnAdd_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'btnDelete_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'btnUpdate_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'btnSave_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'btnClear_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cbSort_2_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onPageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onChangedIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'btnFilter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSearchTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'cbSearch_2_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->PaginationInWidget((*reinterpret_cast< std::add_pointer_t<QTreeWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<BSTPhone*>>(_a[2]))); break;
        case 1: _t->ShowPage((*reinterpret_cast< std::add_pointer_t<QTreeWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::vector<PhoneInformation>>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->showTreeInWidget((*reinterpret_cast< std::add_pointer_t<QTreeWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<BSTPhone*>>(_a[2]))); break;
        case 3: { BSTPhone* _r = _t->CopyTree((*reinterpret_cast< std::add_pointer_t<BSTPhone*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< BSTPhone**>(_a[0]) = std::move(_r); }  break;
        case 4: _t->btnPrePage_2_clicked(); break;
        case 5: _t->btnNextP_2_clicked(); break;
        case 6: _t->treeWidget_itemClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->btnAdd_2_clicked(); break;
        case 8: _t->btnDelete_2_clicked(); break;
        case 9: _t->btnUpdate_2_clicked(); break;
        case 10: _t->btnSave_clicked(); break;
        case 11: _t->btnClear_clicked(); break;
        case 12: _t->cbSort_2_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->onPageChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->onChangedIndex(); break;
        case 15: _t->btnFilter_clicked(); break;
        case 16: _t->onSearchTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->cbSearch_2_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTreeWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTreeWidget* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTreeWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
