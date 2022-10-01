CONFIG += c++17

# This option is used to disabled the default option on Windows
# that creates a dir release and debug each time we build
CONFIG -= debug_and_release debug_and_release_target

INCLUDEPATH += $${PWD}/libs/

# Or sharedlib
CORELIBMODE = staticlib

!equals(TARGET, StrategoCore) {
    include($${PWD}/src/StrategoCore/StrategoCore.pri)
}

QMAKE_CXXFLAGS += -Wall

lessThan(QT_MAJOR_VERSION, 5) {
    error("use Qt 5 or newer")
}

lessThan(QT_MINOR_VERSION, 12) {
    QMAKE_CXXFLAGS += -std=c++17
}
