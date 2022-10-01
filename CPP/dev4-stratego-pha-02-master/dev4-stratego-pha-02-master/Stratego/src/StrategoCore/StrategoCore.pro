CONFIG -= qt

TEMPLATE = lib

include(../../config.pri)

CONFIG += $${CORELIBMODE}

SOURCES += \
        Board.cpp \
        Deck.cpp \
        Game.cpp \
        Graveyard.cpp \
        Pawn.cpp \
        Player.cpp \
        Position.cpp

DISTFILES += \
    StrategoCore.pri

HEADERS += \
    Board.h \
    Deck.h \
    Game.h \
    GameResult.h \
    Graveyard.h \
    Model.h \
    Observable.h \
    Observer.h \
    Pawn.h \
    Player.h \
    Position.h \
    State.h \
    Team.h
