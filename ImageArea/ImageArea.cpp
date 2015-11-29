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

void ImageArea::newProject()
{
	Image *image = new Image();
	image->newEmpty(64, 64);
	addSubWindow(image);
	image->show();
}

void ImageArea::openProject()
{
	QMessageBox::warning(nullptr, "Placeholder", "Open Project");
}

void ImageArea::saveProject()
{
	QMessageBox::warning(nullptr, "Placeholder", "Save Project");
}

void ImageArea::saveProjectAs()
{
	QMessageBox::warning(nullptr, "Placeholder", "Save Project As");
}

void ImageArea::importImage()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Import Image"), "", tr("Portable Network Graphics (*.png)"));

	if (fileName.isNull() || fileName.isEmpty())
		return;

	Image *image = new Image();

	if (image->importFromImageFile(fileName))
	{
		addSubWindow(image);
		image->show();
	}
}

void ImageArea::exportImage()
{
	Image *currentImage = getCurrentImage();

	if (!currentImage)
		return;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Export Image"), "", tr("Portable Network Graphics (*.png)"));

	if (fileName.isNull() || fileName.isEmpty())
		return;

	currentImage->exportToImageFile(fileName);
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
