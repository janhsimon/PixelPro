#pragma once

#include <QtWidgets>

#include "ColorPalette/ColorPaletteRollOut.hpp"
#include "DrawingTools/DrawingToolsRollOut.hpp"

class SideBar : public QWidget
{
	Q_OBJECT

public:
	SideBar();
	~SideBar();

	DrawingToolsRollOut *getDrawingToolsRollOut();
	DrawingToolsModel *getDrawingToolsModel();
	ColorPaletteRollOut *getColorPaletteRollOut();
	ColorPaletteSwatchArea *getColorPaletteSwatchArea();
	QColorDialog *getColorPaletteColorDialog();

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
