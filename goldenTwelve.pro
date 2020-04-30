TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += includes/

SOURCES += \
        src/diceset.cpp \
        src/main.cpp \
        src/player.cpp

HEADERS += \
    includes/diceset.h \
    includes/player.h \
    includes/regras.h 
	
