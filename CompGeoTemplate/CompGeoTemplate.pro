
TEMPLATE = app
TARGET = CompGeoTemplate
DESTDIR = ../Win32/Debug
QT += core opengl widgets gui  openglwidgets
CONFIG += debug
DEFINES += QT_DLL QT_DLL QT_OPENGL_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
LIBS += -lopengl32 \
    -lglu32
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./mainwindow.h \
    ./glwidget.h
SOURCES += ./glwidget.cpp \
    ./main.cpp \
    ./mainwindow.cpp
FORMS += ./mainwindow.ui
