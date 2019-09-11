TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        config.cpp \
        interpreter.cpp \
        main.cpp \
        midicommand.cpp \
        midiinterface.cpp \
        parameter.cpp \
        parsing/commandparser.cpp \
        synth.cpp

HEADERS += \
    config.h \
    interpreter.h \
    midicommand.h \
    midiinterface.h \
    parameter.h \
    parsing/commandparser.h \
    synth.h \
    utils.h
