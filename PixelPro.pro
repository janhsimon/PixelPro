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
    SideBar/SideBar.cpp \
    Editor.cpp \
    ImageArea/ImageArea.cpp \
    SideBar/ColorPalette/ColorPaletteRollOut.cpp \
    SideBar/ColorPalette/ColorPaletteSwatchArea.cpp \
    SideBar/DrawingTools/DrawingToolsRollOut.cpp \
    SideBar/DrawingTools/DrawingToolsModel.cpp \
    PreviewWindow/PreviewWindow.cpp \
    ImageArea/ImageWindow.cpp \
    ImageArea/Image.cpp \
    ImageArea/ImageScrollBarFilter.cpp \
    ImageArea/ImageInOut.cpp

HEADERS  += \
    SideBar/SideBar.hpp \
    Editor.hpp \
    ImageArea/ImageArea.hpp \
    SideBar/ColorPalette/ColorPaletteRollOut.hpp \
    SideBar/ColorPalette/ColorPaletteSwatchArea.hpp \
    SideBar/DrawingTools/DrawingToolsRollOut.hpp \
    SideBar/DrawingTools/DrawingToolsModel.hpp \
    PreviewWindow/PreviewWindow.hpp \
    ImageArea/ImageWindow.hpp \
    ImageArea/Image.hpp \
    ImageArea/ImageScrollBarFilter.hpp \
    ImageArea/ImageInOut.hpp
