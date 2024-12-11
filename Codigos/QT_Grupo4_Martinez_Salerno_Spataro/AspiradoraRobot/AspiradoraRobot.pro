QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET = SocketConnect

SOURCES += \
    main.cpp \
    pantallaacercade.cpp \
    pantallahora.cpp \
    pantallaprincipal.cpp \
    pestaniaconfig.cpp \
    pestaniahistorial.cpp

HEADERS += \
    configuracion.h \
    pantallaacercade.h \
    pantallahora.h \
    pantallaprincipal.h \
    pestaniaconfig.h \
    pestaniahistorial.h

FORMS += \
    pantallaacercade.ui \
    pantallahora.ui \
    pantallaprincipal.ui \
    pestaniaconfig.ui \
    pestaniahistorial.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes_pantalla_principal.qrc

DISTFILES += \
    ../../../../../../../../save (1).svg
