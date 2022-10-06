TEMPLATE = subdirs
SUBDIRS += \
    src/StrategoCore \
    # Tests \
    src/Console \
    src/GUI

src-Console.depends = src/StrategoCore
Tests.depends = src/StrategoCore
src-GUI.depends = src/StrategoCore

OTHER_FILES += config.pri \
    Doxyfile \
    ../.gitignore


