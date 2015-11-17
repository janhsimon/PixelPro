#pragma once

#include <QColor>

class ColorPaletteModel
{
public:
	const static unsigned short MAX_COLORS = 256;

	ColorPaletteModel();

	QColor getColor(int i);
	void import(const QString &fileName);

private:
	QColor colors[MAX_COLORS];

	QColor getColorFromByteArray(const QByteArray &bytes, unsigned short colorIndex);
	void loadDefaultColorPalette();
};
