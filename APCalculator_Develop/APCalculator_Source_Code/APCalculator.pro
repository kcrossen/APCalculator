QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

## OS-X:
# $ cd ~/Documents/APCalculator_Develop/build-APCalculator-Desktop_Qt_5_6_1_clang_64bit-Release
# $ /Developer/5.6/clang_64/bin/macdeployqt APCalculator.app -dmg

TARGET = APCalculator
TEMPLATE = app

HEADERS     = \
    Calculator_UI.h \
    libAPCalc.h \
    History.h \
    Solves.h \
    Geometry.h \
    Finance.h \
    Equations.h \
    Constants.h \
    Units.h \
    Modes.h \
    User.h \
    APCalc_Init.h \
    PlainTextEdit.h \
    LineEdit.h \
    ButtonDefinitions.h \
    StringExt.h
SOURCES     = \
    APCalculator.cpp \
    Calculator_UI.cpp \
    Calculator_UI_Menu.cpp \
    Calculator_APCalc_Init.cpp \
    History.c \
    Calculator_RPN.cpp \
    Calculator_Algebraic.cpp \
    Calculator_Solve.cpp \
    PlainTextEdit.cpp \
    LineEdit.cpp \
    Calculator_Buttons.cpp \
    Calculator_Program.cpp

OTHER_FILES += \
    APCalculator.icns

ICON = APCalculator.icns

VERSION = 2017.02.05

DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

## OS-X:
macx:LIBS += $$PWD/libcalc.a
# macx:LIBS += ~/Documents/APCalculator_Develop/APCalculator_Source_Code/libcalc.a

## Windows (this has not been tried since 2012 against Qt4.8.5 SDK)
#win32:LIBS += %HOMEPATH%/Documents/APCalculator_Develop/APCalculator_Source_Code/libAPCalc.a
#win32:LIBS += %HOMEPATH%/Documents/APCalculator_Develop/APCalculator_Source_Code/libgcc_s.a
#win32:LIBS += %HOMEPATH%/Documents/APCalculator_Develop/APCalculator_Source_Code/libstdc++.a
#win32:LIBS += %HOMEPATH%/Documents/APCalculator_Develop/APCalculator_Source_Code/libwinpthread.a
