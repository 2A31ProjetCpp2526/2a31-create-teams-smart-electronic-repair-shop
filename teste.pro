QT       += core gui widgets sql charts printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += texttospeech

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    connection.cpp \
    equipement.cpp \
    main.cpp \
    qrcodechai.cpp \
    qrcodogen.cpp \
    smartelectronic.cpp


HEADERS += \
    client.h \
    connection.h \
    equipement.h \
    qrcodechai.h \
    qrcodogen.h \
    smartelectronic.h


FORMS += \
    qrcodechai.ui \
    smartelectronic.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    9443577.png \
    pdf-93-removebg-preview.png \
    png-transparent-bell-notification-communication-information-icon-thumbnail-removebg-preview.png \
    pngtree-delete-button-functionality-icon-image_1127707.jpg
