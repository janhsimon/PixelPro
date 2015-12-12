#include <assert.h>

#include "ImageWindow.hpp"

ImageWindow::ImageWindow(SideBar *sideBar, PreviewWindow *previewWindow)
{
	assert(sideBar);
	this->sideBar = sideBar;

	assert(previewWindow);
	this->previewWindow = previewWindow;

	image = nullptr;
	zoomFactor = 1;
	selectedColorIndex = 0;

	resetColorPaletteHotkeys();
}

ImageWindow::~ImageWindow()
{
	if (image)
		delete image;
}

void ImageWindow::newEmpty(unsigned int width, unsigned int height)
{
	assert(width > 0 && height > 0);

	if (image)
		delete image;

	image = new QImage(QSize(width, height), QImage::Format_Indexed8);

	if (image->isNull())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to create new image file.");
		return;
	}

	makeDefaultColorPalette();
	image->fill(selectedColorIndex);

	setMinimumSize(width, height);
	setWindowTitle("[New Project] @");
	updateTitle();
}

bool ImageWindow::importFromImageFile(const QString &fileName)
{
	assert(!fileName.isNull() && !fileName.isEmpty());

	QImage importImage(fileName);

	if (importImage.isNull())
	{
		QMessageBox::critical(nullptr, "Error", "Failed to import image file \"" + fileName + "\".");
		return false;
	}

	const unsigned int newWidth = importImage.width();
	const unsigned int newHeight = importImage.height();

	assert(newWidth > 0 && newHeight > 0);
	newEmpty(newWidth, newHeight);

	QVector<QRgb> newColorTable;
	bool newColorTableIsFull = false;
	for (unsigned int y = 0; y < newHeight; ++y)
	{
		for (unsigned int x = 0; x < newWidth; ++x)
		{
			QColor importColor(importImage.pixel(x, y));

			bool isImportColorInNewColorTable = false;

			for (int i = 0; i < newColorTable.length(); ++i)
			{
				if (newColorTable[i] == importColor.rgb())
				{
					isImportColorInNewColorTable = true;
					image->setPixel(x, y, i);
					break;
				}
			}

			if (!isImportColorInNewColorTable)
			{
				image->setPixel(x, y, newColorTable.length());
				newColorTable.push_back(importColor.rgb());

				unsigned int newColorTableLength = newColorTable.length();
				if (newColorTableLength >= MAX_COLORS_IN_PALETTE)
				{
					newColorTableIsFull = true;
					QMessageBox::critical(nullptr, "Warning", "Too many colors in imported image file \"" + fileName + "\", only a maximum of "
										  + QString::number(MAX_COLORS_IN_PALETTE) + " colors are supported. Additional colors will be discarded.");
					break;
				}
			}
		}

		if (newColorTableIsFull)
			break;
	}

	image->setColorTable(newColorTable);
	clipColorPaletteToNearestPowerOfTwo();

	setMinimumSize(image->width(), image->height());
	setWindowTitle("[" + fileName.right(fileName.length() - fileName.lastIndexOf("/") - 1) + "] @");
	updateTitle();

	return true;
}

void ImageWindow::exportToImageFile(const QString &fileName)
{
	assert(image);
	if (!image->save(fileName))
		QMessageBox::critical(nullptr, "Error", "Failed to export image file to \"" + fileName + "\".");
}

void ImageWindow::importColorPalette(const QString &fileName)
{
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::critical(nullptr, "Error", "Failed to load palette definition file \"" + fileName + "\": " + file.errorString());
		return;
	}

	QByteArray bytes = file.readAll();

	unsigned int numColorsInPalette = bytes.length() / 3;

	if (numColorsInPalette > MAX_COLORS_IN_PALETTE)
	{
		QMessageBox::critical(nullptr, "Warning", "Found " + QString::number(numColorsInPalette) + " colors in palette definition file \"" +
										fileName + "\" but only a maximum of " + QString::number(MAX_COLORS_IN_PALETTE) + " colors are supported. " +
										"Additional colors will be discarded.");
		numColorsInPalette = MAX_COLORS_IN_PALETTE;
	}

	assert(image);

	for (unsigned short colorIndex = 0; colorIndex < numColorsInPalette; ++colorIndex)
	{
		unsigned short byteIndex = colorIndex * 3;

		assert(byteIndex + 0 >= 0 && byteIndex + 2 < bytes.length());

		const unsigned char r = bytes[byteIndex + 0];
		const unsigned char g = bytes[byteIndex + 1];
		const unsigned char b = bytes[byteIndex + 2];

		QColor color(r, g, b);
		image->setColor(colorIndex, color.rgb());
	}

	QColor color = Qt::black;

	for (unsigned short colorIndex = numColorsInPalette; colorIndex < MAX_COLORS_IN_PALETTE; ++colorIndex)
		image->setColor(colorIndex, color.rgb());

	clipColorPaletteToNearestPowerOfTwo();
	resetColorPaletteHotkeys();
}

void ImageWindow::zoomIn()
{
	if (zoomFactor >= MAX_ZOOM_FACTOR)
	{
		zoomFactor = MAX_ZOOM_FACTOR;
		return;
	}

	zoomFactor++;

	updateTitle();
	repaint();
}

void ImageWindow::zoomOut()
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

QImage *ImageWindow::getImage()
{
	assert(image);
	return image;
}

QColor ImageWindow::getSelectedColor()
{
	assert(image);
	return QColor(image->color(getSelectedColorIndex()));
}

void ImageWindow::setSelectedColor(const QColor &color)
{
	assert(image);
	image->setColor(getSelectedColorIndex(), color.rgb());
}

unsigned char ImageWindow::getSelectedColorIndex()
{
	assert(selectedColorIndex >= 0 && selectedColorIndex < image->colorCount());
	return selectedColorIndex;
}

void ImageWindow::setSelectedColorIndex(unsigned char index)
{
	assert(index >= 0 && index < image->colorCount());
	selectedColorIndex = index;
}

void ImageWindow::hotkeySelectedColor(short hotkeyGroup)
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

void ImageWindow::recallHotkeyedColor(short hotkeyGroup)
{
	assert(hotkeyGroup >= 0 && hotkeyGroup < MAX_COLOR_HOTKEYS);
	short color = hotkeyedColors[hotkeyGroup];

	if (color >= 0)
		setSelectedColorIndex(color);
}

short ImageWindow::getHotkeyGroupForColorIndex(unsigned char index)
{
	for (int i = 0; i < MAX_COLOR_HOTKEYS; ++i)
	{
		if (index == hotkeyedColors[i])
			return i;
	}

	return -1;
}

void ImageWindow::paintEvent(QPaintEvent*)
{
	assert(image);

	QPainter painter(this);
	painter.setPen(Qt::darkGray);
	painter.setBrush(Qt::darkGray);
	painter.drawRect(0, 0, width(), height());

	const unsigned int windowWidth = width();
	const unsigned int windowHeight = height();
	const unsigned int originalImageWidth = image->width();
	const unsigned int originalImageHeight = image->height();
	const unsigned int scaledImageWidth = originalImageWidth * zoomFactor;
	const unsigned int scaledImageHeight = originalImageHeight * zoomFactor;
	const unsigned int centerOffsetX = (windowWidth - scaledImageWidth) / 2;
	const unsigned int centerOffsetY = (windowHeight - scaledImageHeight) / 2;

	QRect rect(centerOffsetX, centerOffsetY, scaledImageWidth, scaledImageHeight);
	painter.drawImage(rect, *image);
}

void ImageWindow::mousePressEvent(QMouseEvent *event)
{
	mouseMoveEvent(event);
}

void ImageWindow::mouseMoveEvent(QMouseEvent *event)
{
	assert(event);

	if (event->buttons() != Qt::LeftButton)
		return;

	assert(image);

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

	assert(sideBar);
	DrawingToolsModel *drawingToolsModel = sideBar->getDrawingToolsModel();
	assert(drawingToolsModel);

	if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::BRUSH)
	{
		image->setPixel(x, y, getSelectedColorIndex());
		repaint();

		assert(previewWindow);
		previewWindow->updatePreview();
	}
	else if (drawingToolsModel->getActiveDrawingTool() == DrawingTool::COLOR_PICKER)
	{
		setSelectedColorIndex(image->pixelIndex(x, y));

		ColorPaletteSwatchArea *colorPaletteSwatchArea = sideBar->getColorPaletteSwatchArea();
		assert(colorPaletteSwatchArea);
		colorPaletteSwatchArea->repaint();
	}
}

void ImageWindow::wheelEvent(QWheelEvent *event)
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

void ImageWindow::closeEvent(QCloseEvent *event)
{
	if (QMessageBox::question(nullptr, "Save before closing?", "Are you sure want to close without saving?") == QMessageBox::No)
		event->ignore();
}

void ImageWindow::updateTitle()
{
	QString title = windowTitle().left(windowTitle().lastIndexOf("@") + 1);
	title.append(QString::number(zoomFactor) + "x");
	setWindowTitle(title);
}

void ImageWindow::clipColorPaletteToNearestPowerOfTwo()
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

void ImageWindow::makeDefaultColorPalette()
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

void ImageWindow::resetColorPaletteHotkeys()
{
	for (int i = 0; i < MAX_COLOR_HOTKEYS; ++i)
		hotkeyedColors[i] = (i == 0) ? 9 : i - 1;
}
