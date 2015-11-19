#include <QtWidgets>

#include <assert.h>

#include "ColorPaletteModel.hpp"

ColorPaletteModel::ColorPaletteModel()
{
	loadDefaultColorPalette();
}

QColor ColorPaletteModel::getColor(int i)
{
	assert(i >= 0 && i < MAX_COLORS);
	return colors[i];
}

void ColorPaletteModel::import(const QString &fileName)
{
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::critical(nullptr, "Error", "Failed to load palette definition file \"" + fileName + "\": " + file.errorString());
		return;
	}

	QByteArray bytes = file.readAll();

	const unsigned short numColorsInPalette = bytes.length() / 3;

	for (int colorIndex = 0; colorIndex < numColorsInPalette; ++colorIndex)
		colors[colorIndex] = getColorFromByteArray(bytes, colorIndex);

	for (int colorIndex = numColorsInPalette; colorIndex < MAX_COLORS; ++colorIndex)
		colors[colorIndex] = Qt::black;
}

QColor ColorPaletteModel::getColorFromByteArray(const QByteArray &bytes, unsigned short colorIndex)
{
	unsigned short byteIndex = colorIndex * 3;

	assert(byteIndex + 0 >= 0 && byteIndex + 2 < bytes.length());

	const unsigned char r = bytes[byteIndex + 0];
	const unsigned char g = bytes[byteIndex + 1];
	const unsigned char b = bytes[byteIndex + 2];

	return QColor(r, g, b);
}

void ColorPaletteModel::loadDefaultColorPalette()
{
	colors[0] = Qt::black;
	colors[1] = Qt::white;

	colors[2] = Qt::lightGray;
	colors[3] = Qt::darkGray;

	colors[4] = Qt::red;
	colors[5] = Qt::darkRed;
	colors[6] = Qt::green;
	colors[7] = Qt::darkGreen;
	colors[8] = Qt::blue;
	colors[9] = Qt::darkBlue;

	colors[10] = Qt::yellow;
	colors[11] = Qt::darkYellow;
	colors[12] = Qt::cyan;
	colors[13] = Qt::darkCyan;
	colors[14] = Qt::magenta;
	colors[15] = Qt::darkMagenta;

	for (int i = 16; i < MAX_COLORS; ++i)
		colors[i] = Qt::black;
}
