#include <assert.h>

#include "ImageModel.hpp"

ImageModel::ImageModel(ColorPaletteSwatchArea *colorPaletteSwatchArea)
{
	assert(colorPaletteSwatchArea);
	this->colorPaletteSwatchArea = colorPaletteSwatchArea;

	imageColorPaletteModel = new ImageColorPaletteModel();
	data = nullptr;
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

unsigned char ImageModel::getDataAt(unsigned int x, unsigned int y)
{
	assert(x >= 0 && x < width && y >= 0 && y < height);
	assert(data);
	return data[y * width + x];
}

void ImageModel::setDataAt(unsigned int x, unsigned y, unsigned char colorIndex)
{
	assert(x >= 0 && x < width && y >= 0 && y < height);
	assert(data);
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

void ImageModel::setSelectedColorToIndex(unsigned char index)
{
	assert(imageColorPaletteModel);
	imageColorPaletteModel->setSelectedColorIndex(index);

	assert(colorPaletteSwatchArea);
	colorPaletteSwatchArea->repaint();
}

ImageColorPaletteModel *ImageModel::getImageColorPaletteModel()
{
	assert(imageColorPaletteModel);
	return imageColorPaletteModel;
}
