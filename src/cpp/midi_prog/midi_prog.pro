TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        midicommand.cpp \
        parameter.cpp

HEADERS += \
    midicommand.h \
    parameter.h
