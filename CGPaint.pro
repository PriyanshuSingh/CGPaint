#-------------------------------------------------
#
# Project created by QtCreator 2015-08-13T20:58:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CGPaint
TEMPLATE = app

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -lGLEW

SOURCES += main.cpp\
        mainwindow.cpp \
    cgshader.cpp \
    cgcanvas.cpp \
    cgshape.cpp \
    cgcircle.cpp \
    cgpencil.cpp \
    cgtriangle.cpp \
    cgsquare.cpp \
    cgline.cpp

HEADERS  += mainwindow.h \
    cgshader.h \
    cgcanvas.h \
    cgshape.h \
    cgcircle.h \
    cgpencil.h \
    cgtriangle.h \
    cgsquare.h \
    cgundostack.h \
    cgline.h

FORMS    += mainwindow.ui

RESOURCES += \
    myres.qrc

DISTFILES += \
    vertex_shader.vert \
    fragment_shader.frag
