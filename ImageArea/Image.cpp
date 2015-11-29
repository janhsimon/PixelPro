#include <assert.h>

#include "Image.hpp"

Image::Image()
{
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
	/*
	assert(!fileName.isNull() && !fileName.isEmpty());

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
	/*
	assert(!fileName.isNull() && !fileName.isEmpty());
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
	/*
	assert(pixmap);
	assert(!pixmap->isNull());

	QPainter painter(this);
	painter.drawPixmap(0, 0, pixmap->scaled(pixmap->width() * zoomFactor, pixmap->height() * zoomFactor));
	*/

	assert(zoomFactor > 0);

	const unsigned int WINDOW_WIDTH = width();
	const unsigned int WINDOW_HEIGHT = height();
	const unsigned int ORIGINAL_IMAGE_WIDTH = imageModel->getWidth();
	const unsigned int ORIGINAL_IMAGE_HEIGHT = imageModel->getHeight();
	const unsigned int SCALED_IMAGE_WIDTH = ORIGINAL_IMAGE_WIDTH * zoomFactor;
	const unsigned int SCALED_IMAGE_HEIGHT = ORIGINAL_IMAGE_HEIGHT * zoomFactor;
	const unsigned int CENTER_OFFSET_X = (WINDOW_WIDTH - SCALED_IMAGE_WIDTH) / 2;
	const unsigned int CENTER_OFFSET_Y = (WINDOW_HEIGHT - SCALED_IMAGE_HEIGHT) / 2;

	assert(imageModel);

	QPainter painter(this);

	painter.setPen(Qt::darkGray);
	painter.setBrush(Qt::darkGray);
	painter.drawRect(0, 0, width(), height());

	for (unsigned int y = 0; y < ORIGINAL_IMAGE_HEIGHT; ++y)
	{
		for (unsigned int x = 0; x < ORIGINAL_IMAGE_WIDTH; ++x)
		{
			QColor color = imageModel->getColorAt(x, y);
			painter.setPen(color);
			painter.setBrush(color);

			if (zoomFactor == 1)
				painter.drawPoint(x + CENTER_OFFSET_X, y + CENTER_OFFSET_Y);
			else
				painter.drawRect(x * zoomFactor + CENTER_OFFSET_X, y * zoomFactor + CENTER_OFFSET_Y, zoomFactor, zoomFactor);
		}
	}
}

void Image::mouseMoveEvent(QMouseEvent *event)
{
	assert(event);

	if(event->buttons() != Qt::LeftButton)
		return;

	const unsigned int WINDOW_WIDTH = width();
	const unsigned int WINDOW_HEIGHT = height();
	const unsigned int ORIGINAL_IMAGE_WIDTH = imageModel->getWidth();
	const unsigned int ORIGINAL_IMAGE_HEIGHT = imageModel->getHeight();
	const unsigned int SCALED_IMAGE_WIDTH = ORIGINAL_IMAGE_WIDTH * zoomFactor;
	const unsigned int SCALED_IMAGE_HEIGHT = ORIGINAL_IMAGE_HEIGHT * zoomFactor;
	const unsigned int CENTER_OFFSET_X = (WINDOW_WIDTH - SCALED_IMAGE_WIDTH) / 2;
	const unsigned int CENTER_OFFSET_Y = (WINDOW_HEIGHT - SCALED_IMAGE_HEIGHT) / 2;

	assert(zoomFactor > 0);
	int x = (event->localPos().x() - CENTER_OFFSET_X) / zoomFactor;
	int y = (event->localPos().y() - CENTER_OFFSET_Y) / zoomFactor;

	if (x < 0 || x >= width() || y < 0 || y >= height())
		return;

	assert(imageModel);
	imageModel->setDataToSelectedColorAt(x, y);

	/*
	assert(pixmap);
	assert(!pixmap->isNull());
	QImage img = pixmap->toImage();
	assert(!img.isNull());

	QRgb *rowData = (QRgb*)img.scanLine(y);
	rowData += x;
	assert(colorPaletteModel);
	*rowData = colorPaletteModel->getSelectedColor().rgb();

	//qDebug() << "drawing pixel at " << x << ", " << y;

	pixmap = new QPixmap(QPixmap::fromImage(img));
	*/

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
