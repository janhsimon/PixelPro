#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T20:21:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelPro
TEMPLATE = app


SOURCES +=\
    Main.cpp \
    Model/ColorPaletteModel.cpp \
    View/EditorWindowView.cpp \
    View/ColorPaletteWindowView.cpp

HEADERS  += \
    Model/ColorPaletteModel.hpp \
    View/EditorWindowView.hpp \
    View/ColorPaletteWindowView.hpp
