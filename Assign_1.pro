#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T01:07:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assign_1
TEMPLATE = app


SOURCES += main.cpp\
    window.cpp \
    Tetrahedron.cpp \
    myglwidget.cpp

HEADERS  += \
    window.h \
    Tetrahedron.h \
    myglwidget.h

FORMS    +=

OTHER_FILES += \
    led_cube.png

mac: LIBS += -framework QtOpenGL                    # QtOpenGL framework is needed to be added manually
else:unix|win32: LIBS += -lQtOpenGL
