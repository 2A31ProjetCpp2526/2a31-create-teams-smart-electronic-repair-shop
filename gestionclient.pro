TEMPLATE = app
TARGET = gestionclient

QT += widgets sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
QT += texttospeech

SOURCES += \
    client.cpp \
    connexion.cpp \
    equipement.cpp \
    gestionclient.cpp \
    main.cpp \
    qrcodechai.cpp \
    qrcodogen.cpp

HEADERS += \
    client.h \
    connexion.h \
    equipement.h \
    gestionclient.h \
    qrcodechai.h \
    qrcodogen.h

FORMS += \
    gestionclient.ui \
    mainwindow.ui \
    qrcodechai.ui

LIBS += -lodbc32

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
