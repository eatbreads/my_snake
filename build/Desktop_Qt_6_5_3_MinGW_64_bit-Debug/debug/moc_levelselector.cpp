/****************************************************************************
** Meta object code from reading C++ file 'levelselector.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../levelselector.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'levelselector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSLevelSelectorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSLevelSelectorENDCLASS = QtMocHelpers::stringData(
    "LevelSelector",
    "goToPreviousLevel",
    "",
    "goToNextLevel",
    "startGame",
    "onPreviousLevelButtonClicked",
    "onNextLevelButtonClicked",
    "onStartGameButtonClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSLevelSelectorENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[14];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[10];
    char stringdata5[29];
    char stringdata6[25];
    char stringdata7[25];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSLevelSelectorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSLevelSelectorENDCLASS_t qt_meta_stringdata_CLASSLevelSelectorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "LevelSelector"
        QT_MOC_LITERAL(14, 17),  // "goToPreviousLevel"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 13),  // "goToNextLevel"
        QT_MOC_LITERAL(47, 9),  // "startGame"
        QT_MOC_LITERAL(57, 28),  // "onPreviousLevelButtonClicked"
        QT_MOC_LITERAL(86, 24),  // "onNextLevelButtonClicked"
        QT_MOC_LITERAL(111, 24)   // "onStartGameButtonClicked"
    },
    "LevelSelector",
    "goToPreviousLevel",
    "",
    "goToNextLevel",
    "startGame",
    "onPreviousLevelButtonClicked",
    "onNextLevelButtonClicked",
    "onStartGameButtonClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLevelSelectorENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    0,   51,    2, 0x06,    2 /* Public */,
       4,    0,   52,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject LevelSelector::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSLevelSelectorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLevelSelectorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLevelSelectorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LevelSelector, std::true_type>,
        // method 'goToPreviousLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToNextLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPreviousLevelButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNextLevelButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStartGameButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void LevelSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LevelSelector *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->goToPreviousLevel(); break;
        case 1: _t->goToNextLevel(); break;
        case 2: _t->startGame(); break;
        case 3: _t->onPreviousLevelButtonClicked(); break;
        case 4: _t->onNextLevelButtonClicked(); break;
        case 5: _t->onStartGameButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LevelSelector::*)();
            if (_t _q_method = &LevelSelector::goToPreviousLevel; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LevelSelector::*)();
            if (_t _q_method = &LevelSelector::goToNextLevel; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LevelSelector::*)();
            if (_t _q_method = &LevelSelector::startGame; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *LevelSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LevelSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLevelSelectorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LevelSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void LevelSelector::goToPreviousLevel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LevelSelector::goToNextLevel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LevelSelector::startGame()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
