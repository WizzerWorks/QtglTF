
QT       += core widgets opengl

QT       -= gui

TARGET = QtglTF
TEMPLATE = lib

DEFINES += QTGLTF_LIBRARY WAIT_FOR_COMPLETION

INCLUDEPATH = include

SOURCES += \
    src/qgltfreader.cpp \
    src/qgltferror.cpp \
    src/qgltfwidget.cpp \
    src/validate.cpp \
    src/qgltfvalidator.cpp

HEADERS +=\
    include/qtgltf_global.h \
    include/qgltfreader.h \
    include/qgltferror.h \
    include/qgltfwidget.h \
    include/qgltfvalidator.h \
    include/validate.h


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES +=
