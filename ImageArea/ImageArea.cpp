#include <assert.h>

#include "ImageArea.hpp"

ImageArea::ImageArea()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

Image *ImageArea::getCurrentImage()
{
	if (!currentSubWindow())
		return nullptr;

	Image *currentImage = (Image*)currentSubWindow()->widget();

	if (!currentImage)
		return nullptr;

	return currentImage;
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

void ImageArea::saveImageAs()
{
	Image *currentImage = getCurrentImage();

	if (!currentImage)
		return;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image As"), "", tr("Portable Network Graphics (*.png)"));

	if (fileName.isNull() || fileName.isEmpty())
		return;

	currentImage->saveAs(fileName);
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
