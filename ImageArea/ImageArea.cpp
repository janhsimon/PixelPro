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

void ImageArea::newProject()
{
	assert(sideBar);
	assert(previewWindow);
	ImageWindow *image = new ImageWindow(sideBar, previewWindow);
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

	assert(sideBar);
	assert(previewWindow);
	ImageWindow *imageWindow = new ImageWindow(sideBar, previewWindow);

	if (imageWindow->importFromImageFile(fileName))
	{
		addSubWindow(imageWindow);
		imageWindow->show();
	}
}

void ImageArea::exportImage()
{
	ImageWindow *currentImageWindow = getCurrentImageWindow();

	if (!currentImageWindow)
		return;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Export Image"), "", tr("Portable Network Graphics (*.png)"));

	if (fileName.isNull() || fileName.isEmpty())
		return;

	currentImageWindow->exportToImageFile(fileName);
}

void ImageArea::zoomInCurrentImage()
{
	ImageWindow *currentImageWindow = getCurrentImageWindow();

	if (currentImageWindow)
		currentImageWindow->zoomIn();
}

void ImageArea::zoomOutCurrentImage()
{
	ImageWindow *currentImageWindow = getCurrentImageWindow();

	if (currentImageWindow)
		currentImageWindow->zoomOut();
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
