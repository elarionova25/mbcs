QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application.cpp \
    main.cpp \
    adminpanel.cpp \
    settingspanel.cpp \
    userpanel.cpp

HEADERS += \
    adminpanel.h \
    application.h \
    settingspanel.h \
    userpanel.h

FORMS += \
    adminpanel.ui \
    settingspanel.ui \
    userpanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target