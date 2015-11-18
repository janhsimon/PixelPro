#include <assert.h>

#include "Image.hpp"

Image::Image()
{
	zoomFactor = 1;
}

void Image::newEmpty()
{
	pixmap = new QPixmap(256, 256);
	assert(pixmap);

	setMinimumSize(pixmap->width(), pixmap->height());

	setWindowTitle("[Unsaved Image] @");
	updateTitle();
}

bool Image::open(const QString &fileName)
{
	assert(!fileName.isNull() && !fileName.isEmpty());

	pixmap = new QPixmap(fileName);
	assert(pixmap);

	if (pixmap->isNull())
	{
		QMessageBox::critical(0, "Error", "Failed to open image file \"" + fileName + "\".");
		return false;
	}

	/*
	QImage img = pixmap.toImage();
	assert(!img.isNull());

	QRgb *rowData = (QRgb *)img.scanLine(10);
	rowData += 10;
	*rowData = qRgb(255, 0, 0);

	pixmap = QPixmap::fromImage(img);
	*/

	//QScrollArea *tagCloudScrollArea = new QScrollArea;
	//tagCloudScrollArea->setWidget(tagCloudDisplay);

	setMinimumSize(pixmap->width(), pixmap->height());

	setWindowTitle("[" + fileName.right(fileName.length() - fileName.lastIndexOf("/") - 1) + "] @");
	updateTitle();

	return true;
}

void Image::zoomIn()
{
	assert(pixmap);
	assert(!pixmap->isNull());

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
	assert(pixmap);
	assert(!pixmap->isNull());

	if (zoomFactor <= 1)
	{
		zoomFactor = 1;
		return;
	}

	zoomFactor--;

	updateTitle();
	repaint();
}

void Image::paintEvent(QPaintEvent*)
{
	assert(pixmap);
	assert(!pixmap->isNull());

	QPainter painter(this);
	painter.drawPixmap(0, 0, pixmap->scaled(pixmap->width() * zoomFactor, pixmap->height() * zoomFactor));
}

void Image::updateTitle()
{
	QString title = windowTitle().left(windowTitle().lastIndexOf("@") + 1);
	title.append(QString::number(zoomFactor) + "x");
	setWindowTitle(title);
}
