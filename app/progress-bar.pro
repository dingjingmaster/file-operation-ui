TEMPLATE = app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 no_keywords link_pkgconfig

DEFINES += QT_DEPRECATED_WARNINGS

PKGCONFIG += gio-unix-2.0 gio-2.0

SOURCES += \
    $$PWD/main.cpp\
    file-operation-error-handler.cpp \
    file-operation-progressbar.cpp \
    tooltip.cpp

HEADERS += \
    file-operation-error-handler.h \
    file-operation-progressbar.h \
    tooltip.h



