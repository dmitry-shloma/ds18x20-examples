TEMPLATE = lib

CONFIG += static

win32: INCLUDEPATH = "C:\Program Files (x86)\avr8-gnu-toolchain\avr\include"

HEADERS = \
    onewire.h

SOURCES = \
    onewire.c
