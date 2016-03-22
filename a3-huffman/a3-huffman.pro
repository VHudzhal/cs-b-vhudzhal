QT += core
QT -= gui

CONFIG += c++11

TARGET = a3-huffman
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DISTFILES += \
    input.txt \
    output.txt \
    teemp.txt
