#include <assert.h>

#include "Image.hpp"
#include "ImageInOut.hpp"

Image::Image(unsigned int width, unsigned int height, SideBar *sideBar, PreviewWindow *previewWindow, QScrollArea *parentScrollArea)
{
	assert(width > 0 && height > 0);

	assert(sideBar);
	this->sideBar = sideBar;

	assert(previewWindow);
	this->previewWindow = previewWindow;

	assert(parentScrollArea);
	this->parentScrollArea = parentScrollArea;

	image = new QImage(QSize(width, height), QImage::Format_Indexed8);

	if (image->isNull())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to create new " + QString::number(width) + "x" + QString::number(height) + " image file.");
		return;
	}

	makeDefaultColorPalette();
	selectedColorIndex = 0;
	image->fill(selectedColorIndex);
	zoomFactor = 1;
	isDrawingLine = false;
	isDrawingGrid = true;
	updateWidgetSize();
	resetColorPaletteHotkeys();
	setCursor(Qt::CrossCursor);
}

Image::~Image()
{
	if (image)
		delete image;
}

bool Image::importFromImageFile(const QString &fileName)
{
	if (!ImageInOut::importFromImageFile(this, fileName))
		return false;

	selectedColorIndex = 0;
	zoomFactor = 1;
	updateWidgetSize();
	resetColorPaletteHotkeys();

	return true;
}

void Image::exportToImageFile(const QString &fileName)
{
	ImageInOut::exportToImageFile(this, fileName);
}

void Image::importColorPalette(const QString &fileName)
{
	ImageInOut::importColorPalette(this, fileName);

	selectedColorIndex = 0;
	resetColorPaletteHotkeys();
}

void Image::zoomIn()
{
	if (zoomFactor >= MAX_ZOOM_FACTOR)
	{
		zoomFactor = MAX_ZOOM_FACTOR;
		return;
	}

	zoomFactor++;
	assert(zoomFactor >= 1 && zoomFactor <= MAX_ZOOM_FACTOR);

	updateWidgetSize();
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
	assert(zoomFactor >= 1 && zoomFactor <= MAX_ZOOM_FACTOR);

	updateWidgetSize();
	repaint();
}

void Image::toggleGrid()
{
	isDrawingGrid = !isDrawingGrid;
	repaint();
}

QImage *Image::getImage()
{
	assert(image);
	return image;
}

QColor Image::getSelectedColor()
{
	assert(image);
	return QColor(image->color(getSelectedColorIndex()));
}

void Image::setSelectedColor(const QColor &color)
{
	assert(image);
	image->setColor(getSelectedColorIndex(), color.rgb());
}

unsigned char Image::getSelectedColorIndex()
{
	assert(selectedColorIndex >= 0 && selectedColorIndex < image->colorCount());
	return selectedColorIndex;
}

void Image::setSelectedColorIndex(unsigned char index)
{
	assert(index >= 0 && index < image->colorCount());
	selectedColorIndex = index;
}

void Image::hotkeySelectedColor(short hotkeyGroup)
{
	assert(hotkeyGroup < MAX_COLOR_HOTKEYS);

	const unsigned char selectedColorIndex = getSelectedColorIndex();

	for (int i = 0; i < MAX_COLOR_HOTKEYS; ++i)
	{
		if (hotkeyedColors[i] == selectedColorIndex)
			hotkeyedColors[i] = -1;
	}

	hotkeyedColors[hotkeyGroup] = selectedColorIndex;
}

void Image::recallHotkeyedColor(short hotkeyGroup)
{
	assert(hotkeyGroup >= 0 && hotkeyGroup < MAX_COLOR_HOTKEYS);
	short color = hotkeyedColors[hotkeyGroup];

	if (color >= 0)
		setSelectedColorIndex(color);
}

short Image::getHotkeyGroupForColorIndex(unsigned char index)
{
	for (int i = 0; i < MAX_COLOR_HOTKEYS; ++i)
	{
		if (index == hotkeyedColors[i])
			return i;
	}

	return -1;
}

void Image::clipColorPaletteToNearestPowerOfTwo()
{
	assert(image);

	for (int i = 15; i >= 1; --i)
	{
		if (image->colorCount() > i * i)
		{
			image->setColorCount((i + 1) * (i + 1));
			break;
		}
	}
}

bool Image::recreateImage(int width, int height)
{
	if (image)
		delete image;

	image = new QImage(QSize(width, height), QImage::Format_Indexed8);

	if (image->isNull())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to allocate memory for " + QString::number(width) + "x" + QString::number(height) + " image.");
		return false;
	}

	return true;
}

void Image::paintEvent(QPaintEvent *)
{
	assert(image);
	assert(zoomFactor >= 1 && zoomFactor <= MAX_ZOOM_FACTOR);

	QPainter painter(this);
	QRect rect(0, 0, image->width() * zoomFactor, image->height() * zoomFactor);
	painter.drawImage(rect, *image);

	if (isDrawingGrid && zoomFactor > 4)
	{
		QPen pen(Qt::gray);
		pen.setWidth(1);
		painter.setPen(pen);

		for (int y = 1; y < image->height(); ++y)
			painter.drawLine(0, y * zoomFactor, image->width()* zoomFactor, y * zoomFactor);

		for (int x = 1; x < image->width(); ++x)
			painter.drawLine(x * zoomFactor, 0, x * zoomFactor, image->height()* zoomFactor);
	}

	if (isDrawingLine)
	{
		QPen pen(getSelectedColor());
		pen.setWidth(getZoomFactor());
		painter.setPen(pen);

		painter.drawLine(lastMousePositionForLineDrawing.x(), lastMousePositionForLineDrawing.y(),
			currentMousePositionForLineDrawing.x(), currentMousePositionForLineDrawing.y());
	}
}

void Image::mousePressEvent(QMouseEvent *event)
{
	assert(sideBar);
	DrawingToolsModel *drawingToolsModel = sideBar->getDrawingToolsModel();
	assert(drawingToolsModel);

	if (event->button() == Qt::MiddleButton)
	{
		lastMousePositionForScrubbing = event->globalPos();
		setCursor(Qt::ClosedHandCursor);
	}
	else
	{
		if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::BRUSH)
		{
			if (event->button() == Qt::LeftButton)
			{
				lastMousePositionForPixelDrawing.setX(-1);
				lastMousePositionForPixelDrawing.setY(-1);
				mouseMoveEvent(event);
			}
			else if (event->button() == Qt::RightButton)
			{
				lastMousePositionForLineDrawing.setX(event->localPos().x());
				lastMousePositionForLineDrawing.setY(event->localPos().y());
				isDrawingLine = true;
			}
		}
		else if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::COLOR_PICKER)
		{
			if (event->button() == Qt::LeftButton)
				mouseMoveEvent(event);
		}
		else if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::FILL)
		{
			if (event->button() == Qt::LeftButton)
				mouseMoveEvent(event);
		}
	}
}

void Image::mouseMoveEvent(QMouseEvent *event)
{
	assert(event);

	if (event->buttons() & Qt::LeftButton)
	{
		assert(image);
		assert(zoomFactor >= 1 && zoomFactor <= MAX_ZOOM_FACTOR);

		const unsigned int windowWidth = width();
		const unsigned int windowHeight = height();
		const unsigned int originalImageWidth = image->width();
		const unsigned int originalImageHeight = image->height();
		const unsigned int scaledImageWidth = originalImageWidth * zoomFactor;
		const unsigned int scaledImageHeight = originalImageHeight * zoomFactor;
		const unsigned int centerOffsetX = (windowWidth - scaledImageWidth) / 2;
		const unsigned int centerOffsetY = (windowHeight - scaledImageHeight) / 2;

		const unsigned int x = (event->localPos().x() - centerOffsetX) / zoomFactor;
		const unsigned int y = (event->localPos().y() - centerOffsetY) / zoomFactor;

		if (x < 0 || x >= originalImageWidth || y < 0 || y >= originalImageHeight)
			return;

		if (lastMousePositionForPixelDrawing.x() < 0 && lastMousePositionForPixelDrawing.y() < 0)
		{
			lastMousePositionForPixelDrawing.setX(x);
			lastMousePositionForPixelDrawing.setY(y);
		}

		assert(sideBar);
		DrawingToolsModel *drawingToolsModel = sideBar->getDrawingToolsModel();
		assert(drawingToolsModel);

		if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::BRUSH)
		{
			drawLine(lastMousePositionForPixelDrawing.x(), lastMousePositionForPixelDrawing.y(), x, y);
			repaint();

			assert(previewWindow);
			previewWindow->repaint();

			lastMousePositionForPixelDrawing.setX(x);
			lastMousePositionForPixelDrawing.setY(y);
		}
		else if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::COLOR_PICKER)
		{
			setSelectedColorIndex(image->pixelIndex(x, y));

			ColorPaletteSwatchArea *colorPaletteSwatchArea = sideBar->getColorPaletteSwatchArea();
			assert(colorPaletteSwatchArea);
			colorPaletteSwatchArea->repaint();
		}
		else if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::FILL)
		{
			//drawLine(lastMousePositionForPixelDrawing.x(), lastMousePositionForPixelDrawing.y(), x, y);
			fill(x, y);
			repaint();

			assert(previewWindow);
			previewWindow->repaint();
		}
	}
	else if (event->buttons() & Qt::RightButton)
	{
		currentMousePositionForLineDrawing.setX(event->localPos().x());
		currentMousePositionForLineDrawing.setY(event->localPos().y());
		repaint();
	}
	else if (event->buttons() & Qt::MiddleButton)
	{
		QPoint delta(event->globalPos() - lastMousePositionForScrubbing);

		assert(parentScrollArea);
		QScrollBar *scrollBarX = parentScrollArea->horizontalScrollBar();
		QScrollBar *scrollBarY = parentScrollArea->verticalScrollBar();

		scrollBarX->setValue(scrollBarX->value() - delta.x());
		scrollBarY->setValue(scrollBarY->value() - delta.y());

		lastMousePositionForScrubbing = event->globalPos();
	}
}

void Image::mouseReleaseEvent(QMouseEvent *event)
{
	assert(sideBar);
	DrawingToolsModel *drawingToolsModel = sideBar->getDrawingToolsModel();
	assert(drawingToolsModel);

	if (event->button() == Qt::MiddleButton)
		setCursor(Qt::CrossCursor);
	else
	{
		if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::BRUSH)
		{
			if (event->button() == Qt::RightButton)
			{
				const unsigned int windowWidth = width();
				const unsigned int windowHeight = height();
				const unsigned int originalImageWidth = image->width();
				const unsigned int originalImageHeight = image->height();
				const unsigned int scaledImageWidth = originalImageWidth * zoomFactor;
				const unsigned int scaledImageHeight = originalImageHeight * zoomFactor;
				const unsigned int centerOffsetX = (windowWidth - scaledImageWidth) / 2;
				const unsigned int centerOffsetY = (windowHeight - scaledImageHeight) / 2;

				const unsigned int x1 = (lastMousePositionForLineDrawing.x() - centerOffsetX) / zoomFactor;
				const unsigned int y1 = (lastMousePositionForLineDrawing.y() - centerOffsetY) / zoomFactor;
				const unsigned int x2 = (currentMousePositionForLineDrawing.x() - centerOffsetX) / zoomFactor;
				const unsigned int y2 = (currentMousePositionForLineDrawing.y() - centerOffsetY) / zoomFactor;

				isDrawingLine = false;

				if (x1 < 0 || x1 >= originalImageWidth || y1 < 0 || y1 >= originalImageHeight ||
					x2 < 0 || x2 >= originalImageWidth || y2 < 0 || y2 >= originalImageHeight)
				{
					repaint();
					return;
				}

				drawLine(x1, y1, x2, y2);
				repaint();

				assert(previewWindow);
				previewWindow->repaint();
			}
		}
	}
}

void Image::drawPixel(int x, int y)
{
	assert(image);
	assert(x >= 0 && x < image->width() && y >= 0 && y < image->height());
	image->setPixel(x, y, getSelectedColorIndex());
}

void Image::drawLine(int x1, int y1, int x2, int y2)
{
	assert(image);
	assert(x1 >= 0 && x1 < image->width() && y1 >= 0 && y1 < image->height());
	assert(x2 >= 0 && x2 < image->width() && y2 >= 0 && y2 < image->height());

	if (x1 == x2 && y1 == y2)
	// trivial case
	{
		drawPixel(x1, y1);
		return;
	}

	// make sure start and end are part of the line
	// (not guaranteed by bresenham's algorithm)
	drawPixel(x1, y1);
	drawPixel(x2, y2);


	// bresenham's algorithm

	const bool steep = abs(y2 - y1) > abs(x2 - x1);

	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = abs(y2 - y1);

	float error = dx / 2.f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = y1;

	const int maxX = x2;

	for (int x = x1; x < maxX; ++x)
	{
		if (steep)
			drawPixel(y, x);
		else
			drawPixel(x, y);

		error -= dy;

		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void Image::fill(int x, int y, int backgroundColor)
{
	assert(image);

	if (x < 0 || x >= image->width() || y < 0 || y >= image->height())
		return;

	int sampledColor = image->pixelIndex(x, y);

	if (backgroundColor < 0)
	// if we haven't determined the background color yet
		backgroundColor = sampledColor;

	if (backgroundColor == getSelectedColorIndex())
	// if we're trying to fill something that already is that color
		// we're done rightaway
		return;

	if (sampledColor != backgroundColor)
	// if we hit a color that is not the color we're trying to fill
		// we can stop
		return;

	drawPixel(x, y);
	fill(x - 1, y, backgroundColor);
	fill(x + 1, y, backgroundColor);
	fill(x, y - 1, backgroundColor);
	fill(x, y + 1, backgroundColor);
}

void Image::makeDefaultColorPalette()
{
	image->setColorCount(16);

	QColor color = Qt::black;
	image->setColor(0, color.rgb());

	color = Qt::white;
	image->setColor(1, color.rgb());

	color = Qt::lightGray;
	image->setColor(2, color.rgb());

	color = Qt::darkGray;
	image->setColor(3, color.rgb());

	color = Qt::red;
	image->setColor(4, color.rgb());

	color = Qt::darkRed;
	image->setColor(5, color.rgb());

	color = Qt::green;
	image->setColor(6, color.rgb());

	color = Qt::darkGreen;
	image->setColor(7, color.rgb());

	color = Qt::blue;
	image->setColor(8, color.rgb());

	color = Qt::darkBlue;
	image->setColor(9, color.rgb());

	color = Qt::yellow;
	image->setColor(10, color.rgb());

	color = Qt::darkYellow;
	image->setColor(11, color.rgb());

	color = Qt::magenta;
	image->setColor(12, color.rgb());

	color = Qt::darkMagenta;
	image->setColor(13, color.rgb());

	color = Qt::cyan;
	image->setColor(14, color.rgb());

	color = Qt::darkCyan;
	image->setColor(15, color.rgb());
}

void Image::resetColorPaletteHotkeys()
{
	for (int i = 0; i < MAX_COLOR_HOTKEYS; ++i)
		hotkeyedColors[i] = (i == 0) ? 9 : i - 1;
}

void Image::updateWidgetSize()
{
	assert(image);
	assert(zoomFactor >= 1 && zoomFactor <= MAX_ZOOM_FACTOR);
	setMinimumSize(image->width() * zoomFactor, image->height() * zoomFactor);
	setMaximumSize(minimumSize());
}
