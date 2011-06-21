#-------------------------------------------------
#
# Project created by QtCreator 2010-11-03T22:58:40
#
#-------------------------------------------------

QT       += core gui xml

TARGET = jkl-dvd
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlread.cpp \
    files.cpp \
    flowlayout.cpp \
    search.cpp \
    googlesuggest.cpp \
    searchbox.cpp \
    categories.cpp \
    timeline.cpp

HEADERS  += mainwindow.h \
    xmlread.h \
    files.h \
    flowlayout.h \
    search.h \
    googlesuggest.h \
    searchbox.h \
    categories.h \
    timeline.h

FORMS    += mainwindow.ui

RESOURCES +=

DEFINES -= UNICODE
