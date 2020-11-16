QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH += /usr/include/glib-2.0/
#INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include/
#INCLUDEPATH += /usr/lib/

LIBS    +=  -L/usr/lib/ -laudio -L/usr/lib/x86_64-linux-gnu/ -lglib-2.0 -lgio-2.0

SOURCES += \
    audio_helper_common.cpp \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp

HEADERS += \
    audio_helper_common.h \
    lib_audio_api.h \
    mainwindow.h \
    mythread.h

FORMS +=

DISTFILES += \
    org.ukui.audio_api.gschema.xml

schemes.files += org.ukui.audio_api.gschema.xml
schemes.path =  /usr/share/glib-2.0/schemas/

INSTALLS += schemes

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
