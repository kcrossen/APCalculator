#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T15:50:45
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Test_ApCalc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += CALC_SRC

SOURCES += \
    main.cpp \
    ../addop.c \
    ../assocfunc.c \
    ../blkcpy.c \
    ../block.c \
    ../byteswap.c \
    ../calcerr.c \
    ../codegen.c \
    ../comfunc.c \
    ../commath.c \
    ../config.c \
    ../const.c \
    ../custom.c \
    ../func.c \
    ../hash.c \
    ../jump.c \
    ../label.c \
    ../lib_calc.c \
    ../lib_util.c \
    ../listfunc.c \
    ../matfunc.c \
    ../math_error.c \
    ../obj.c \
    ../opcodes.c \
    ../pix.c \
    ../poly.c \
    ../prime.c \
    ../qfunc.c \
    ../qio.c \
    ../qmath.c \
    ../qmod.c \
    ../qtrans.c \
    ../quickhash.c \
    ../seed.c \
    ../sha1.c \
    ../size.c \
    ../str.c \
    ../StringExt.c \
    ../symbol.c \
    ../token.c \
    ../User.c \
    ../UserUtil.c \
    ../value.c \
    ../version.c \
    ../zfunc.c \
    ../zio.c \
    ../zmath.c \
    ../zmod.c \
    ../zmul.c \
    ../zprime.c \
    ../zrand.c \
    ../zrandom.c

HEADERS += \
    ../align32.h \
    ../alloc.h \
    ../args.h \
    ../blkcpy.h \
    ../block.h \
    ../byteswap.h \
    ../calcerr.h \
    ../cmath.h \
    ../conf.h \
    ../config.h \
    ../custom.h \
    ../decl.h \
    ../endian_calc.h \
    ../func.h \
    ../hash.h \
    ../jump.h \
    ../label.h \
    ../lib_calc.h \
    ../lib_util.h \
    ../nametype.h \
    ../opcodes.h \
    ../prime.h \
    ../qmath.h \
    ../sha1.h \
    ../str.h \
    ../StringExt.h \
    ../symbol.h \
    ../token.h \
    ../User.h \
    ../UserUtil.h \
    ../value.h \
    ../zmath.h \
    ../zrand.h \
    ../zrandom.h \
    APCalc_Init.h \
    libAPCalc.h \
    StringExt.h \
    User.h
