#include <assert.h>

#include "Image.hpp"

Image::Image(ColorPaletteModel *colorPaletteModel)
{
	assert(colorPaletteModel);
	this->colorPaletteModel = colorPaletteModel;
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
		QMessageBox::critical(nullptr, "Error", "Failed to open image file \"" + fileName + "\".");
		return false;
	}

	//QScrollArea *tagCloudScrollArea = new QScrollArea;
	//tagCloudScrollArea->setWidget(tagCloudDisplay);

	setMinimumSize(pixmap->width(), pixmap->height());

	setWindowTitle("[" + fileName.right(fileName.length() - fileName.lastIndexOf("/") - 1) + "] @");
	updateTitle();

	return true;
}

void Image::saveAs(const QString &fileName)
{
	assert(!fileName.isNull() && !fileName.isEmpty());
	assert(pixmap);
	assert(!pixmap->isNull());

	if (!pixmap->save(fileName))
		QMessageBox::critical(nullptr, "Error", "Failed to save image file as \"" + fileName + "\".");
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

void Image::mouseMoveEvent(QMouseEvent *event)
{
	assert(event);

	if(event->buttons() != Qt::LeftButton)
		return;

	assert(zoomFactor > 0);
	int x = event->localPos().x() / zoomFactor;
	int y = event->localPos().y() / zoomFactor;

	if (x < 0 || x >= width() || y < 0 || y >= height())
		return;

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
