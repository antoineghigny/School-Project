TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(../../config.pri)

SOURCES += \
    Controller.cpp \
    ViewConsole.cpp \
    main.cpp

HEADERS += \
    Controller.h \
    ViewConsole.h
