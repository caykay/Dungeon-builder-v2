TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    abstractcreature.cpp \
    alchemistslaboratory.cpp \
    basicdungeonlevel.cpp \
    basicdungeonlevelbuilder.cpp \
    blockeddoorway.cpp \
    consumeable.cpp \
    doorway.cpp \
    dungeonlevel.cpp \
    dungeonlevelbuilder.cpp \
    enchantedlibrary.cpp \
    game.cpp \
    item.cpp \
    lockeddoorway.cpp \
    magicaldungeonlevel.cpp \
    magicaldungeonlevelbuilder.cpp \
    magicwall.cpp \
    main.cpp \
    menuinterface.cpp \
    monster.cpp \
    onewaydoor.cpp \
    opendoorway.cpp \
    quartzchamber.cpp \
    rockchamber.cpp \
    rockwall.cpp \
    room.cpp \
    roomedge.cpp \
    wall.cpp \
    weapon.cpp

HEADERS += \
    abstractcreature.h \
    alchemistslaboratory.h \
    basicdungeonlevel.h \
    basicdungeonlevelbuilder.h \
    blockeddoorway.h \
    consumeable.h \
    doorway.h \
    dungeonlevel.h \
    dungeonlevelbuilder.h \
    enchantedlibrary.h \
    game.h \
    item.h \
    lockeddoorway.h \
    magicaldungeonlevel.h \
    magicaldungeonlevelbuilder.h \
    magicwall.h \
    menuinterface.h \
    monster.h \
    onewaydoor.h \
    opendoorway.h \
    quartzchamber.h \
    rockchamber.h \
    rockwall.h \
    room.h \
    roomedge.h \
    wall.h \
    weapon.h

DISTFILES += \
    DUNGEON_BUILDER_PROJECT
