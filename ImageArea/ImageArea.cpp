#include <assert.h>

#include "ImageArea.hpp"

Image *ImageArea::currentImage = nullptr;

ImageArea::ImageArea(ColorPaletteSwatchArea *colorPaletteSwatchArea, DrawingToolsModel *drawingToolsModel, PreviewWindow *previewWindow)
{
	assert(colorPaletteSwatchArea);
	this->colorPaletteSwatchArea = colorPaletteSwatchArea;

	assert(drawingToolsModel);
	this->drawingToolsModel = drawingToolsModel;

	assert(previewWindow);
	this->previewWindow = previewWindow;

	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(setCurrentImage(QMdiSubWindow*)));
}

Image *ImageArea::getCurrentImage()
{
	return currentImage;
}

void ImageArea::newProject()
{
	assert(colorPaletteSwatchArea);
	assert(drawingToolsModel);
	assert(previewWindow);
	Image *image = new Image(colorPaletteSwatchArea, drawingToolsModel, previewWindow);
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

	assert(colorPaletteSwatchArea);
	assert(drawingToolsModel);
	assert(previewWindow);
	Image *image = new Image(colorPaletteSwatchArea, drawingToolsModel, previewWindow);

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

void ImageArea::setCurrentImage(QMdiSubWindow *currentImage)
{
	if (!currentImage)
	{
		this->currentImage = nullptr;
		return;
	}

	Image *image = (Image*)currentImage->widget();

	if (!image)
		return;

	this->currentImage = image;
}
