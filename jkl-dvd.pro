#-------------------------------------------------
#
# Project created by QtCreator 2010-11-03T22:58:40
#
#-------------------------------------------------

QT       += core gui xml webkit

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
    timeline.cpp \
    buttonarea.cpp \
    popup.cpp

HEADERS  += mainwindow.h \
    xmlread.h \
    files.h \
    flowlayout.h \
    search.h \
    googlesuggest.h \
    searchbox.h \
    categories.h \
    timeline.h \
    buttonarea.h \
    popup.h

FORMS    += mainwindow.ui \
    popup.ui

RESOURCES += \
    resources.qrc

RC_FILE = jklry-dvd.rc

DEFINES -= UNICODE
