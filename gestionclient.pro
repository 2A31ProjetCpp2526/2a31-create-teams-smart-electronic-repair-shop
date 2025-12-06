TEMPLATE = app
TARGET = gestionclient

CONFIG += c++17

QT += widgets sql serialport texttospeech

SOURCES += \
    arduino.cpp \
    client.cpp \
    connexion.cpp \
    equipement.cpp \
    gestionclient.cpp \
    main.cpp \
    qrcodechai.cpp \
    qrcodogen.cpp

HEADERS += \
    arduino.h \
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
