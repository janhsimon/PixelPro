#include <assert.h>

#include "Image.hpp"

Image::Image(ColorPaletteSwatchArea *colorPaletteSwatchArea, DrawingToolsModel *drawingToolsModel, PreviewWindow *previewWindow)
{
	assert(colorPaletteSwatchArea);
	this->colorPaletteSwatchArea = colorPaletteSwatchArea;

	assert(drawingToolsModel);
	this->drawingToolsModel = drawingToolsModel;

	assert(previewWindow);
	this->previewWindow = previewWindow;

	imageModel = new ImageModel();
	zoomFactor = 1;
}

Image::~Image()
{
	if (imageModel)
		delete imageModel;
}

void Image::newEmpty(unsigned int width, unsigned int height)
{
	assert(imageModel);
	if (!imageModel->newEmpty(width, height))
		close();

	unsigned int minWindowWidth = width > MIN_WINDOW_WIDTH ? width : MIN_WINDOW_WIDTH;
	unsigned int minWindowHeight = height > MIN_WINDOW_HEIGHT ? height : MIN_WINDOW_HEIGHT;
	setMinimumSize(minWindowWidth, minWindowHeight);

	setWindowTitle("[New Project] @");
	updateTitle();
}

bool Image::importFromImageFile(const QString &fileName)
{
	assert(!fileName.isNull() && !fileName.isEmpty());

	/*
	QPixmap *pixmap = new QPixmap(fileName);

	if (pixmap->isNull())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to import image file \"" + fileName + "\".");
		return false;
	}

	//QScrollArea *tagCloudScrollArea = new QScrollArea;
	//tagCloudScrollArea->setWidget(tagCloudDisplay);

	//assert(imageModel);
	//assert(colorPaletteModel);
	//if (!imageModel->openFromPixmap(*pixmap, colorPaletteModel))
		//close();

	delete pixmap;

	setMinimumSize(pixmap->width(), pixmap->height());

	setWindowTitle("[" + fileName.right(fileName.length() - fileName.lastIndexOf("/") - 1) + "] @");
	updateTitle();
	*/

	return true;
}

void Image::exportToImageFile(const QString &fileName)
{
	assert(!fileName.isNull() && !fileName.isEmpty());

	/*
	assert(pixmap);
	assert(!pixmap->isNull());

	if (!pixmap->save(fileName))
		QMessageBox::critical(nullptr, "Error", "Failed to save image file as \"" + fileName + "\".");
	*/
}

void Image::zoomIn()
{
	if (zoomFactor >= MAX_ZOOM_FACTOR)
	{
		zoomFactor = MAX_ZOOM_FACTOR;
		return;
	}

	zoomFactor++;

	//this->setSizePolicy(Qt::Scro);
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	//setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	updateTitle();
	repaint();
}

void Image::zoomOut()
{
	if (zoomFactor <= 1)
	{
		zoomFactor = 1;
		return;
	}

	zoomFactor--;

	updateTitle();
	repaint();
}

ImageModel *Image::getImageModel()
{
	assert(imageModel);
	return imageModel;
}

void Image::paintEvent(QPaintEvent*)
{
	assert(zoomFactor > 0);
	assert(imageModel);

	const unsigned int windowWidth = width();
	const unsigned int windowHeight = height();
	const unsigned int originalImageWidth = imageModel->getWidth();
	const unsigned int originalImageHeight = imageModel->getHeight();
	const unsigned int scaledImageWidth = originalImageWidth * zoomFactor;
	const unsigned int scaledImageHeight = originalImageHeight * zoomFactor;
	const unsigned int centerOffsetX = (windowWidth - scaledImageWidth) / 2;
	const unsigned int centerOffsetY = (windowHeight - scaledImageHeight) / 2;

	QPainter painter(this);

	painter.setPen(Qt::darkGray);
	painter.setBrush(Qt::darkGray);
	painter.drawRect(0, 0, windowWidth, windowHeight);

	for (unsigned int y = 0; y < originalImageWidth; ++y)
	{
		for (unsigned int x = 0; x < originalImageHeight; ++x)
		{
			QColor color = imageModel->getColorAt(x, y);
			painter.setPen(color);
			painter.setBrush(color);

			if (zoomFactor == 1)
				painter.drawPoint(x + centerOffsetX, y + centerOffsetY);
			else
				painter.drawRect(x * zoomFactor + centerOffsetX, y * zoomFactor + centerOffsetY, zoomFactor, zoomFactor);
		}
	}
}

void Image::mousePressEvent(QMouseEvent *event)
{
	mouseMoveEvent(event);
}

void Image::mouseMoveEvent(QMouseEvent *event)
{
	assert(event);

	if(event->buttons() != Qt::LeftButton)
		return;

	assert(zoomFactor > 0);
	assert(imageModel);

	const unsigned int windowWidth = width();
	const unsigned int windowHeight = height();
	const unsigned int originalImageWidth = imageModel->getWidth();
	const unsigned int originalImageHeight = imageModel->getHeight();
	const unsigned int scaledImageWidth = originalImageWidth * zoomFactor;
	const unsigned int scaledImageHeight = originalImageHeight * zoomFactor;
	const unsigned int centerOffsetX = (windowWidth - scaledImageWidth) / 2;
	const unsigned int centerOffsetY = (windowHeight - scaledImageHeight) / 2;

	const unsigned int x = (event->localPos().x() - centerOffsetX) / zoomFactor;
	const unsigned int y = (event->localPos().y() - centerOffsetY) / zoomFactor;

	if (x < 0 || x >= originalImageWidth || y < 0 || y >= originalImageHeight)
		return;

	assert(drawingToolsModel);
	if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::BRUSH)
	{
		imageModel->setDataToSelectedColorAt(x, y);

		assert(previewWindow);
		previewWindow->updatePreview();
	}
	else if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::COLOR_PICKER)
	{
		imageModel->setSelectedColorToIndex(imageModel->getDataAt(x, y));

		assert(colorPaletteSwatchArea);
		colorPaletteSwatchArea->repaint();
	}

	repaint();
}

void Image::wheelEvent(QWheelEvent *event)
{
	assert(event);

	Qt::KeyboardModifiers keyboardModifiers = QApplication::keyboardModifiers();

	if (!keyboardModifiers.testFlag(Qt::ControlModifier))
		return;

	if (event->delta() > 0)
		zoomIn();
	else if (event->delta() < 0)
		zoomOut();
}

void Image::updateTitle()
{
	QString title = windowTitle().left(windowTitle().lastIndexOf("@") + 1);
	title.append(QString::number(zoomFactor) + "x");
	setWindowTitle(title);
}
