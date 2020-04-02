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
        rtmidi/RtMidi.cpp \
        synth.cpp

HEADERS += \
    config.h \
    interpreter.h \
    midicommand.h \
    midiinterface.h \
    parameter.h \
    parsing/commandparser.h \
    rtmidi/RtMidi.h \
    synth.h \
    utils.h

DEFINES += RTMIDI_DEBUG

win32 {
    DEFINES += __WINDOWS_MM__
    LIBS += -lwinmm
}

unix{
    DEFINES += __LINUX_ALSA__
    LIBS += -lasound -lpthread
}
