#pragma once

#include <QtWidgets>

#include "ColorPaletteRollOut.hpp"

class SideBar : public QWidget
{
	Q_OBJECT

public:
	SideBar();
	~SideBar();

	ColorPaletteRollOut *getColorPaletteRollOut();

private:
	QVBoxLayout *layout;

	QPushButton *drawingToolsRollOutButton;
	//ColorPaletteRollOut *colorPaletteRollOut;

	ColorPaletteModel *colorPaletteModel;
	QPushButton *colorPaletteRollOutButton;
	ColorPaletteRollOut *colorPaletteRollOut;

	QPushButton *tileGridRollOutButton;
	//ColorPaletteRollOut *colorPaletteRollOut;

	QPushButton *animationRollOutButton;
	//ColorPaletteRollOut *colorPaletteRollOut;

private slots:
	void toggleColorPaletteRollOut();
};
