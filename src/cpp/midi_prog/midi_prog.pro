TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        config.cpp \
        main.cpp \
        midicommand.cpp \
        parameter.cpp \
        synth.cpp

HEADERS += \
    command_parsing.h \
    config.h \
    midicommand.h \
    parameter.h \
    synth.h \
    utils.h
