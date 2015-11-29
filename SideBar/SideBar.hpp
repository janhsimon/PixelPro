#pragma once

#include <QtWidgets>

#include "ColorPalette/ColorPaletteRollOut.hpp"
#include "DrawingTools/DrawingToolsRollOut.hpp"
#include "ImageArea/ImageArea.hpp"

class SideBar : public QWidget
{
	Q_OBJECT

public:
	SideBar(ImageArea *imageArea);
	~SideBar();

	DrawingToolsRollOut *getDrawingToolsRollOut();
	ColorPaletteRollOut *getColorPaletteRollOut();

private:
	QVBoxLayout *layout;

	QPushButton *drawingToolsRollOutButton;
	DrawingToolsRollOut *drawingToolsRollOut;

	QPushButton *colorPaletteRollOutButton;
	ColorPaletteRollOut *colorPaletteRollOut;

	QPushButton *tileGridRollOutButton;
	//ColorPaletteRollOut *colorPaletteRollOut;

	QPushButton *animationRollOutButton;
	//ColorPaletteRollOut *colorPaletteRollOut;

private slots:
	void toggleDrawingToolsRollOut();
	void toggleColorPaletteRollOut();
};
