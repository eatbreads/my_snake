QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    food.cpp \
    gamediffwindow.cpp \
    gameend.cpp \
    gameplay.cpp \
    main.cpp \
    mypoint.cpp \
    mypushbutton.cpp \
    snake.cpp \
    widget.cpp \
    windowscheduler.cpp

HEADERS += \
    config.h \
    food.h \
    gamediffwindow.h \
    gameend.h \
    gamemenu.h \
    gameplay.h \
    mypoint.h \
    mypushbutton.h \
    snake.h \
    widget.h \
    windowscheduler.h

FORMS += \
    widget.ui

TRANSLATIONS += \
    my_snake_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
