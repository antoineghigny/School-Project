QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../config.pri)


SOURCES += \
    BoardGui.cpp \
    ControllerGui.cpp \
    DropFile.cpp \
    FileDropArea.cpp \
    GraveyardArea.cpp \
    GraveyardsGui.cpp \
    Parameter.cpp \
    PlacementChoice.cpp \
    Rules.cpp \
    WinScreen.cpp \
    deckgui.cpp \
    leftWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BoardGui.h \
    ControllerGui.h \
    DropFile.h \
    FileDropArea.h \
    GraveyardArea.h \
    GraveyardsGui.h \
    Parameter.h \
    PlacementChoice.h \
    Rules.h \
    WinScreen.h \
    deckgui.h \
    leftWidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
