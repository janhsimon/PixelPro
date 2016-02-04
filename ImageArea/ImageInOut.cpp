#include <assert.h>

#include "ImageInOut.hpp"

bool ImageInOut::importFromImageFile(Image *image, const QString &fileName)
{
	assert(image);
	assert(!fileName.isNull() && !fileName.isEmpty());

	QImage importImage(fileName);

	if (importImage.isNull())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to import image file \"" + fileName + "\".");
		return false;
	}

	const unsigned int newWidth = importImage.width();
	const unsigned int newHeight = importImage.height();

	assert(newWidth > 0 && newHeight > 0);

	if (!image->recreateImage(newWidth, newHeight))
		return false;

	QImage *imageQTImage = image->getImage();
	assert(imageQTImage);

	// temporary setting so that we can set pixel index data below
	// will be overwritten afterwards with the color table we're building
	imageQTImage->setColorCount(256);

	QVector<QRgb> newColorTable;
	bool newColorTableIsFull = false;
	for (unsigned int y = 0; y < newHeight; ++y)
	{
		for (unsigned int x = 0; x < newWidth; ++x)
		{
			QColor importColor(importImage.pixel(x, y));

			bool isImportColorInNewColorTable = false;

			for (int i = 0; i < newColorTable.length(); ++i)
			{
				if (newColorTable[i] == importColor.rgb())
				{
					isImportColorInNewColorTable = true;
					imageQTImage->setPixel(x, y, i);
					break;
				}
			}

			if (!isImportColorInNewColorTable)
			{
				imageQTImage->setPixel(x, y, newColorTable.length());
				newColorTable.push_back(importColor.rgb());

				unsigned int newColorTableLength = newColorTable.length();
				if (newColorTableLength >= image->getMaxColorsInPalette())
				{
					newColorTableIsFull = true;
					QMessageBox::critical(nullptr, "Warning", "Too many colors in imported image file \"" + fileName + "\", only a maximum of "
										  + QString::number(image->getMaxColorsInPalette()) + " colors are supported. Additional colors will be discarded.");
					break;
				}
			}
		}

		if (newColorTableIsFull)
			break;
	}

	imageQTImage->setColorTable(newColorTable);
	image->clipColorPaletteToNearestPowerOfTwo();

	return true;
}

void ImageInOut::exportToImageFile(Image *image, const QString &fileName)
{
	assert(image);
	QImage *imageQTImage = image->getImage();
	assert(imageQTImage);

	if (!imageQTImage->save(fileName))
		QMessageBox::critical(nullptr, "Error", "Failed to export image file to \"" + fileName + "\".");
}

void ImageInOut::importColorPalette(Image *image, const QString &fileName)
{
	assert(image);

	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::critical(nullptr, "Error", "Failed to load palette definition file \"" + fileName + "\": " + file.errorString());
		return;
	}

	QByteArray bytes = file.readAll();

	unsigned int numColorsInPalette = bytes.length() / 3;

	if (numColorsInPalette > image->getMaxColorsInPalette())
	{
		QMessageBox::critical(nullptr, "Warning", "Found " + QString::number(numColorsInPalette) + " colors in palette definition file \"" +
										fileName + "\" but only a maximum of " + QString::number(image->getMaxColorsInPalette()) + " colors are supported. " +
										"Additional colors will be discarded.");
		numColorsInPalette = image->getMaxColorsInPalette();
	}

	QImage *imageQTImage = image->getImage();
	assert(imageQTImage);

	for (unsigned short colorIndex = 0; colorIndex < numColorsInPalette; ++colorIndex)
	{
		unsigned short byteIndex = colorIndex * 3;

		assert(byteIndex + 0 >= 0 && byteIndex + 2 < bytes.length());

		const unsigned char r = bytes[byteIndex + 0];
		const unsigned char g = bytes[byteIndex + 1];
		const unsigned char b = bytes[byteIndex + 2];

		QColor color(r, g, b);
		imageQTImage->setColor(colorIndex, color.rgb());
	}

	QColor color = Qt::black;

	for (unsigned short colorIndex = numColorsInPalette; colorIndex < image->getMaxColorsInPalette(); ++colorIndex)
		imageQTImage->setColor(colorIndex, color.rgb());

	image->clipColorPaletteToNearestPowerOfTwo();
}
