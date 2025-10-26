QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        album.cpp \
        artista.cpp \
        cancion.cpp \
        credito.cpp \
        fecha.cpp \
        listafavoritos.cpp \
        main.cpp \
        publicidad.cpp \
        reproductor.cpp \
        usuario.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    album.h \
    arreglo.h \
    artista.h \
    cancion.h \
    credito.h \
    fecha.h \
    listafavoritos.h \
    publicidad.h \
    reproductor.h \
    usuario.h
