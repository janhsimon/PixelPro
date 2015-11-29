#include <QtWidgets>

#include <assert.h>

#include "ImageColorPaletteModel.hpp"

ImageColorPaletteModel::ImageColorPaletteModel()
{
	loadDefaultColorPalette();
	selectedColor = 0;
}

QColor ImageColorPaletteModel::getColor(unsigned short i)
{
	assert(i >= 0 && i < MAX_COLORS);
	return colors[i];
}

QColor ImageColorPaletteModel::getSelectedColor()
{
	return getColor(selectedColor);
}

void ImageColorPaletteModel::setSelectedColor(const QColor &color)
{
	assert(selectedColor >= 0 && selectedColor < MAX_COLORS);
	colors[selectedColor] = color;
}

unsigned short ImageColorPaletteModel::getSelectedColorIndex()
{
	assert(selectedColor >= 0 && selectedColor < MAX_COLORS);
	return selectedColor;
}

void ImageColorPaletteModel::setSelectedColorIndex(unsigned short index)
{
	assert(index >= 0 && index < MAX_COLORS);
	selectedColor = index;
}

unsigned short ImageColorPaletteModel::getColorIndexClosestToColor(const QColor &color)
{
	short closestColorIndex = -1;
	float shortestDist = 0.f;

	for (unsigned int colorIndex = 0; colorIndex < MAX_COLORS; ++colorIndex)
	{
		QColor compareColor = colors[colorIndex];

		QVector3D diffVector(color.red() - compareColor.red(), color.green() - compareColor.green(), color.blue() - compareColor.blue());
		float thisDist = fabsf(diffVector.lengthSquared());

		if (closestColorIndex < 0 || thisDist < shortestDist)
		{
			closestColorIndex = colorIndex;
			shortestDist = thisDist;
		}
	}

	assert(closestColorIndex >= 0);
	return closestColorIndex;
}

void ImageColorPaletteModel::import(const QString &fileName)
{
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::critical(nullptr, "Error", "Failed to load palette definition file \"" + fileName + "\": " + file.errorString());
		return;
	}

	QByteArray bytes = file.readAll();

	unsigned int numColorsInPalette = bytes.length() / 3;

	if (numColorsInPalette > MAX_COLORS)
	{
		QMessageBox::critical(nullptr, "Warning", "Found " + QString::number(numColorsInPalette) + " colors in palette definition file \"" +
										fileName + "\" but only a maximum of " + QString::number(MAX_COLORS) + " colors are supported. " +
										"Additional colors discarded.");
		numColorsInPalette = MAX_COLORS;
	}

	for (unsigned short colorIndex = 0; colorIndex < numColorsInPalette; ++colorIndex)
		colors[colorIndex] = getColorFromByteArray(bytes, colorIndex);

	for (unsigned short colorIndex = numColorsInPalette; colorIndex < MAX_COLORS; ++colorIndex)
		colors[colorIndex] = Qt::black;
}

QColor ImageColorPaletteModel::getColorFromByteArray(const QByteArray &bytes, unsigned short colorIndex)
{
	unsigned short byteIndex = colorIndex * 3;

	assert(byteIndex + 0 >= 0 && byteIndex + 2 < bytes.length());

	const unsigned char r = bytes[byteIndex + 0];
	const unsigned char g = bytes[byteIndex + 1];
	const unsigned char b = bytes[byteIndex + 2];

	return QColor(r, g, b);
}

void ImageColorPaletteModel::loadDefaultColorPalette()
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
