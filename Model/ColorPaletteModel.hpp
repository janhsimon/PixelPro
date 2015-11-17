#pragma once

#include <QColor>

class ColorPaletteModel
{
public:
	ColorPaletteModel();

private:
	const static unsigned int MAX_COLORS = 256;

	QColor colors[MAX_COLORS];
};
