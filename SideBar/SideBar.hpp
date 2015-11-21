#pragma once

#include <QtWidgets>

#include "ColorPaletteRollOut.hpp"
#include "DrawingToolsRollOut.hpp"

class SideBar : public QWidget
{
	Q_OBJECT

public:
	SideBar();
	~SideBar();

	DrawingToolsRollOut *getDrawingToolsRollOut();

	ColorPaletteModel *getColorPaletteModel();
	ColorPaletteRollOut *getColorPaletteRollOut();

private:
	QVBoxLayout *layout;

	QPushButton *drawingToolsRollOutButton;
	DrawingToolsRollOut *drawingToolsRollOut;

	ColorPaletteModel *colorPaletteModel;
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
