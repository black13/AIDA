#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T01:16:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AIDA
TEMPLATE = app
INCLUDEPATH += /usr/include/opencv

LIBS += -L/lib -I/usr/include/opencv -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_objdetect -lopencv_video -lopencv_videoio -lopencv_videostab
LIBS += -lopencv_highgui
SOURCES += main.cpp\
        mainwindow.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    camera.h


FORMS    += mainwindow.ui

DISTFILES += \
    img/favicon.ico
