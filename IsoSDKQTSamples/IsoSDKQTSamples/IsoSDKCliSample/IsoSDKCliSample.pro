QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
unix:!macx {
DEFINES += LINUX
}

win32: DEFINES += WIN32 UNICODE _UNICODE
macx: DEFINES += MAC

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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
