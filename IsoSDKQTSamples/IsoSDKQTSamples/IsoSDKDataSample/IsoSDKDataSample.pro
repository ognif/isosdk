#-------------------------------------------------
#
# Project created by QtCreator 2019-01-08T08:11:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#DEFINES += BS_GUI
DEFINES += _CRT_SECURE_NO_WARNINGS
unix:!macx {
DEFINES += LINUX
}
win32: DEFINES += WIN32 UNICODE _UNICODE
macx: ICON = IsoSDKDataSample.icns
macx: DEFINES += MAC
TARGET = IsoSDKDataSample
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    IsoSDKDataSample.qrc

win32: LIBS += -L$$PWD/../IsoSDK/ -lIsoSDKCoreU64

unix:!macx {
LIBS += -L$$PWD/../IsoSDK/ -lIsoSDKCore64.2.31
}

INCLUDEPATH += $$PWD/../IsoSDK
DEPENDPATH += $$PWD/../IsoSDK

win32: PRE_TARGETDEPS += $$PWD/../IsoSDK/IsoSDKCoreU64.lib
unix:!macx {
PRE_TARGETDEPS += $$PWD/../IsoSDK/libIsoSDKCore64.2.31.so
}

macx:{
LIBS += -L$$PWD/../IsoSDK/ -lIsoSDKCore64
MediaFiles.files += ../IsoSDK/libIsoSDKCore64.dylib
MediaFiles.path = Contents/MacOS
QMAKE_BUNDLE_DATA += MediaFiles
}

