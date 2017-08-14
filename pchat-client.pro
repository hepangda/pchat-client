#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T15:02:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pchat-client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ./include


SOURCES += \
    service/service.cpp \
    network/rvpkg.cpp \
    network/spkg.cpp \
    network/dpkg.cpp \
    network/package.cpp \
    extra/watchdog.cpp \
    pchat.cpp \
    ui/uilogin.cpp \
    ui/uiregister.cpp \
    ui/uiresetpwd.cpp

HEADERS += \
    include/fpkg.h \
    include/package.h \
    include/service.h \
    include/ui.h \
    include/watchdog.h \
    include/uilogin.h \
    include/uiregister.h \
    include/uiresetpwd.h

#FORMS +=



unix:!macx: LIBS += -L$$PWD/../libportal/src/ -lportal
unix:!macx: LIBS += -ljsoncpp

INCLUDEPATH += $$PWD/../libportal/include
DEPENDPATH += $$PWD/../libportal/include

FORMS += \
    ui/uilogin.ui \
    ui/uiregister.ui \
    ui/uiresetpwd.ui
