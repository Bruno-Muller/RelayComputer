#-------------------------------------------------
#
# Project created by QtCreator 2011-11-07T18:47:48
#
#-------------------------------------------------

QT       += core gui

TARGET = RelayComputer
TEMPLATE = app


SOURCES += main.cpp\
        fenetre.cpp \
    Bus.cpp \
    ALU.cpp \
    Registre.cpp \
    Memory.cpp \
    InterfaceRegistre8_16.cpp \
    Incr16bit.cpp \
    Horloge.cpp \
    EEPROM.cpp \
    Ordinateur.cpp

HEADERS  += fenetre.h \
    Bus.h \
    ALU.h \
    Registre.h \
    Memory.h \
    InterfaceRegistre8_16.h \
    Incr16bit.h \
    Horloge.h \
    EEPROM.h \
    Ordinateur.h

FORMS    += fenetre.ui

OTHER_FILES += \
    EEPROM5.dat \
    EEPROM4.dat \
    EEPROM3.dat \
    EEPROM2.dat \
    EEPROM1.dat \
    code.txt

RESOURCES +=
