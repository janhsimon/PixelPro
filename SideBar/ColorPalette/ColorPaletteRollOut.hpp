#pragma once

#include "ColorPaletteSwatchArea.hpp"

class ColorPaletteRollOut : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteRollOut();
	~ColorPaletteRollOut();

	ColorPaletteSwatchArea *getColorPaletteSwatchArea();
	QColorDialog *getColorDialog();

private:
	ColorPaletteSwatchArea *colorPaletteSwatchArea;
	QColorDialog *colorDialog;

public slots:
	void editColor();

private slots:
	void importColorPalette();
	void exportColorPalette();
};
