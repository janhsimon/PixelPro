#include <assert.h>

#include "ImageModel.hpp"

ImageModel::ImageModel()
{
	imageColorPaletteModel = new ImageColorPaletteModel();
}

ImageModel::~ImageModel()
{
	assert(data);
	delete [] data;

	assert(imageColorPaletteModel);
	delete imageColorPaletteModel;
}

bool ImageModel::newEmpty(unsigned int width, unsigned int height)
{
	assert(width > 0 && height > 0);
	this->width = width;
	this->height = height;

	data = new unsigned char[width * height];

	if (!data)
	{
		QMessageBox::critical(nullptr, "Error", "Failed to allocate enough memory (" + QString::number(width * height) + " bytes requested) for new image.");
		return false;
	}

	for (unsigned int y = 0; y < height; ++y)
		for (unsigned int x = 0; x < width; ++x)
			setDataAt(x, y, 0);

	return true;
}

/*
bool ImageModel::openFromPixmap(const QPixmap &pixmap, ColorPaletteModel *colorPaletteModel)
{
	assert(!pixmap.isNull());
	assert(colorPaletteModel);

	width = pixmap.width();
	height = pixmap.height();

	data = new unsigned char[width * height];

	if (!data)
	{
		QMessageBox::critical(nullptr, "Error", "Failed to allocate enough memory (" + QString::number(width * height) + " bytes requested) for image to be opened.");
		return false;
	}

	QImage img = pixmap.toImage();
	assert(!img.isNull());

	for (unsigned int y = 0; y < height; ++y)
	{
		QRgb *rowData = (QRgb*)img.scanLine(y);

		for (unsigned int x = 0; x < width; ++x)
		{
			QRgb *pixelData = rowData + x;

			const unsigned char r = pixelData[0];
			const unsigned char g = pixelData[1];
			const unsigned char b = pixelData[2];

			unsigned short colorIndex = colorPaletteModel->getColorIndexClosestToColor(QColor(r, g, b));

			//qDebug() << "PIXEL @ " << x << "/" << y << " has raw RGB values: " << r << "/" << g << "/" << b << " which results in color palette index " << colorIndex;

			setDataAt(x, y, colorIndex);
		}
	}

	return true;
}
*/

unsigned char ImageModel::getDataAt(unsigned int x, unsigned int y)
{
	assert(x >= 0 && x < width && y >= 0 && y < height);
	assert(data);
	return data[y * width + x];
}

void ImageModel::setDataAt(unsigned int x, unsigned y, unsigned char colorIndex)
{
	assert(x >= 0 && x < width && y >= 0 && y < height);
	data[y * width + x] = colorIndex;
}

void ImageModel::setDataToSelectedColorAt(unsigned int x, unsigned y)
{
	assert(imageColorPaletteModel);
	setDataAt(x, y, imageColorPaletteModel->getSelectedColorIndex());
}

QColor &ImageModel::getColorAt(unsigned int x, unsigned int y)
{
	assert(imageColorPaletteModel);
	return imageColorPaletteModel->getColor(getDataAt(x, y));
}

ImageColorPaletteModel *ImageModel::getImageColorPaletteModel()
{
	assert(imageColorPaletteModel);
	return imageColorPaletteModel;
}
