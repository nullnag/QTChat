/****************************************************************************
** Meta object code from reading C++ file 'reg.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/reg.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
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
struct qt_meta_stringdata_CLASSRegENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRegENDCLASS = QtMocHelpers::stringData(
    "Reg",
    "on_Login_textEdited",
    "",
    "arg1",
    "SignUpButtonEn",
    "LoginCheck",
    "PassCheck",
    "on_PasswordEDIT_textChanged",
    "on_Password2Edit_textChanged",
    "on_CancleButton_clicked",
    "on_SignUpButton_pressed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRegENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[4];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[15];
    char stringdata5[11];
    char stringdata6[10];
    char stringdata7[28];
    char stringdata8[29];
    char stringdata9[24];
    char stringdata10[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRegENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRegENDCLASS_t qt_meta_stringdata_CLASSRegENDCLASS = {
    {
        QT_MOC_LITERAL(0, 3),  // "Reg"
        QT_MOC_LITERAL(4, 19),  // "on_Login_textEdited"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 4),  // "arg1"
        QT_MOC_LITERAL(30, 14),  // "SignUpButtonEn"
        QT_MOC_LITERAL(45, 10),  // "LoginCheck"
        QT_MOC_LITERAL(56, 9),  // "PassCheck"
        QT_MOC_LITERAL(66, 27),  // "on_PasswordEDIT_textChanged"
        QT_MOC_LITERAL(94, 28),  // "on_Password2Edit_textChanged"
        QT_MOC_LITERAL(123, 23),  // "on_CancleButton_clicked"
        QT_MOC_LITERAL(147, 23)   // "on_SignUpButton_pressed"
    },
    "Reg",
    "on_Login_textEdited",
    "",
    "arg1",
    "SignUpButtonEn",
    "LoginCheck",
    "PassCheck",
    "on_PasswordEDIT_textChanged",
    "on_Password2Edit_textChanged",
    "on_CancleButton_clicked",
    "on_SignUpButton_pressed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRegENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x08,    1 /* Private */,
       4,    2,   53,    2, 0x08,    3 /* Private */,
       7,    1,   58,    2, 0x08,    6 /* Private */,
       8,    1,   61,    2, 0x08,    8 /* Private */,
       9,    0,   64,    2, 0x08,   10 /* Private */,
      10,    0,   65,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    5,    6,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Reg::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSRegENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRegENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRegENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Reg, std::true_type>,
        // method 'on_Login_textEdited'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'SignUpButtonEn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool &, std::false_type>,
        // method 'on_PasswordEDIT_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_Password2Edit_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_CancleButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_SignUpButton_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Reg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Reg *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_Login_textEdited((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->SignUpButtonEn((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 2: _t->on_PasswordEDIT_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->on_Password2Edit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->on_CancleButton_clicked(); break;
        case 5: _t->on_SignUpButton_pressed(); break;
        default: ;
        }
    }
}

const QMetaObject *Reg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Reg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRegENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Reg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
