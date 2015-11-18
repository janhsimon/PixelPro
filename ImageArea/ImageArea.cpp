#include <assert.h>

#include "ImageArea.hpp"

ImageArea::ImageArea()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

Image *ImageArea::getCurrentImage()
{
	Image *currentImage = (Image*)currentSubWindow()->widget();

	if (currentImage)
		return currentImage;

	return nullptr;
}

void ImageArea::newImage()
{
	Image *image = new Image();
	image->newEmpty();
	addSubWindow(image);
	image->show();
}

void ImageArea::openImage()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Portable Network Graphics (*.png)"));

	if (fileName.isNull() || fileName.isEmpty())
		return;

	Image *image = new Image();

	if (image->open(fileName))
	{
		addSubWindow(image);
		image->show();
	}
}

void ImageArea::zoomInCurrentImage()
{
	Image *currentImage = getCurrentImage();

	if (currentImage)
		currentImage->zoomIn();
}

void ImageArea::zoomOutCurrentImage()
{
	Image *currentImage = getCurrentImage();

	if (currentImage)
		currentImage->zoomOut();
}
