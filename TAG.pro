QT       += core gui widgets

CONFIG += c++14

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    baseobject.cpp \
    geometry.cpp \
    geometryintersection.cpp \
    shadersmanager.cpp \
    tile/tile.cpp \
    tile/tiledrawable.cpp \
    tile/tilemanager.cpp \
    tile/tilerenderer.cpp \
    tile/tiletransformer.cpp


SOURCES += \
    mainwidget.cpp

HEADERS += \
    baseobject.h \
    geometry.h \
    geometryintersection.h \
    mainwidget.h \
    shadersmanager.h \
    tile.h \
    tile/tile.h \
    tile/tiledrawable.h \
    tile/tilemanager.h \
    tile/tilerenderer.h \
    tile/tiletransformer.h


RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=
