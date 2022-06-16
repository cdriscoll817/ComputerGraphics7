#-------------------------------------------------
#
# Project created by QtCreator 2011-01-18T16:14:14
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = lab8
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    objects.cpp \
    Point.cpp \
    Vector.cpp \
    quat.cpp \
    arcBall.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    objects.h \
    Point.h \
    Vector.h \
    quat.h \
    arcBall.h

FORMS    += mainwindow.ui

mac: INCLUDEPATH += -I/Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/GLUT.framework/Headers
mac: LIBS += -framework GLUT

unix:!macx:!symbian: INCLUDEPATH += -I/usr/X11R6/include
unix:!macx:!symbian: LIBS += -L/usr/X11R6/lib \
                                    -lGL -lglut -lGLU

win32: INCLUDEPATH += C:\QtSDK\mingw\include
win32: LIBS += libfreeglut

OTHER_FILES += \
    comp30020lab08.ppm
