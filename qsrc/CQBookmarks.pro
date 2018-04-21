TEMPLATE = app

QT += widgets

TARGET = CQBookmarks

DEPENDPATH += .

INCLUDEPATH += . ../include

QMAKE_CXXFLAGS += -std=c++14 -DGNUPLOT_EXPR

CONFIG += debug

# Input
SOURCES += \
main.cpp \
CQBookmarks.cpp \

HEADERS += \
CQBookmarks.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. \
../../CQUtil/include \
../../CUtil/include \
../../CHtml/include \
../../CFile/include \
../../CStrUtil/include \

unix:LIBS += \
-L$$LIB_DIR \
-L../../CBookmarks/lib \
-L../../CHtml/lib \
-L../../CQUtil/lib \
-L../../CStrUtil/lib \
-L../../CFile/lib \
-L../../CRegExp/lib \
-L../../COS/lib \
-lCBookmarks -lCHtml -lCQUtil -lCFile -lCStrUtil -lCRegExp -lCOS \
-lreadline -lcurses -ltre
