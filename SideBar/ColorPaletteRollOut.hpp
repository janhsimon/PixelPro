#pragma once

#include "ColorPaletteSwatchArea.hpp"
#include "ColorPaletteModel.hpp"

class ColorPaletteRollOut : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteRollOut(ColorPaletteModel *colorPaletteModel);

private:
	ColorPaletteModel *colorPaletteModel;
	ColorPaletteSwatchArea *colorPaletteSwatchArea;

private slots:
	void importColorPalette();
};
