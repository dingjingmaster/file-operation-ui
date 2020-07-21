TEMPLATE = app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 no_keywords

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/main.cpp\
    file-operation-progressbar.cpp \
#    main-progress-bar.cpp \
#    other-button.cpp \
    progress-list.cpp
#    $$PWD/progress-bar.cpp          \
#    close-button.cpp \
#    detail-button.cpp \
#    stop-button.cpp \
  #    test-widget.cpp

HEADERS += \
    file-operation-progressbar.h \
#    main-progress-bar.h \
#    other-button.h \
    progress-list.h
#    $$PWD/progress-bar.h            \
#    close-button.h \
#    detail-button.h \
#    stop-button.h \
  #    test-widget.h


