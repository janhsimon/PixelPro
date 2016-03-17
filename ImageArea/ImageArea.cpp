#include <assert.h>

#include "ImageArea.hpp"

ImageWindow *ImageArea::currentImageWindow = nullptr;

ImageArea::ImageArea(SideBar *sideBar, PreviewWindow *previewWindow)
{
	assert(sideBar);
	this->sideBar = sideBar;

	assert(previewWindow);
	this->previewWindow = previewWindow;

	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(setCurrentImageWindow(QMdiSubWindow*)));
}

ImageWindow *ImageArea::getCurrentImageWindow()
{
	return currentImageWindow;
}

Image *ImageArea::getCurrentImage()
{
	if (!currentImageWindow)
		return nullptr;

	Image *currentImage = currentImageWindow->getImage();
	assert(currentImage);
	return currentImage;
}

void ImageArea::newProject(unsigned int width, unsigned int height)
{
	assert(sideBar);
	assert(previewWindow);
	ImageWindow *imageWindow = new ImageWindow(width, height, sideBar, previewWindow);
	assert(imageWindow);
	addSubWindow(imageWindow);
	imageWindow->show();
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

	assert(sideBar);
	assert(previewWindow);
	ImageWindow *imageWindow = new ImageWindow(1, 1, sideBar, previewWindow);
	assert(imageWindow);

	Image *image = imageWindow->getImage();
	assert(image);
	if (image->importFromImageFile(fileName))
	{
		addSubWindow(imageWindow);
		imageWindow->show();
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

void ImageArea::zoomIn()
{
	Image *currentImage = getCurrentImage();

	if (currentImage)
		currentImage->zoomIn();
}

void ImageArea::zoomOut()
{
	Image *currentImage = getCurrentImage();

	if (currentImage)
		currentImage->zoomOut();
}

void ImageArea::toggleGrid()
{
	Image *currentImage = getCurrentImage();

	if (currentImage)
		currentImage->toggleGrid();
}

void ImageArea::setCurrentImageWindow(QMdiSubWindow *currentImageWindow)
{
	if (!currentImageWindow)
	{
		this->currentImageWindow = nullptr;
		return;
	}

	ImageWindow *image = (ImageWindow*)currentImageWindow->widget();

	if (!image)
		return;

	this->currentImageWindow = image;
}
