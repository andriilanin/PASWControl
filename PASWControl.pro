QT += core gui
QT += websockets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += "$$PWD/vJoySDK/inc"
LIBS += -L$$PWD/vJoySDK/inc -lvJoyInterface

SOURCES += \
    axissmoother.cpp \
    main.cpp \
    mainwindow.cpp \
    steeringwheelwidget.cpp \
    vjoydevice.cpp \
    websocketserver.cpp

HEADERS += \
    axissmoother.h \
    mainwindow.h \
    steeringwheelwidget.h \
    vjoydevice.h \
    websocketserver.h

FORMS += \
    mainwindow.ui

win32:RC_FILE = file.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
