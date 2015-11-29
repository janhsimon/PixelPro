#pragma once

#include "ColorPaletteSwatchArea.hpp"
#include "../../ImageArea/ImageArea.hpp"

class ColorPaletteRollOut : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteRollOut(ImageArea *imageArea);
	~ColorPaletteRollOut();

	ColorPaletteSwatchArea *getColorPaletteSwatchArea();
	QColorDialog *getColorDialog();

private:
	ColorPaletteSwatchArea *colorPaletteSwatchArea;
	QColorDialog *colorDialog;
	ImageArea *imageArea;

public slots:
	void editColor();

private slots:
	void importColorPalette();
	void exportColorPalette();
};
