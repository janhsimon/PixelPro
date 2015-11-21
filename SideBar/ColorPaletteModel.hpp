#pragma once

#include <QtWidgets>

class ColorPaletteModel
{
public:
	const static unsigned short MAX_COLORS = 256;

	ColorPaletteModel();

	QColor getColor(int i);
	QColor getSelectedColor();
	unsigned short getSelectedColorIndex();
	void setSelectedColorIndex(unsigned short index);
	void import(const QString &fileName);

private:
	QColor colors[MAX_COLORS];
	unsigned short selectedColor;

	QColor getColorFromByteArray(const QByteArray &bytes, unsigned short colorIndex);
	void loadDefaultColorPalette();
};
