QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addgroup.cpp \
    addhost.cpp \
    exportfile.cpp \
    group.cpp \
    host.cpp \
    importfile.cpp \
    inventfile.cpp \
    main.cpp \
    geninvent.cpp

HEADERS += \
    addgroup.h \
    addhost.h \
    exportfile.h \
    geninvent.h \
    group.h \
    host.h \
    importfile.h \
    inventfile.h

FORMS += \
    addgroup.ui \
    addhost.ui \
    geninvent.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
