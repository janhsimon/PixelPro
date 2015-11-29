#include <assert.h>

#include "ColorPaletteSwatchArea.hpp"

ColorPaletteSwatchArea::ColorPaletteSwatchArea(ImageArea *imageArea)
{
	assert(imageArea);
	this->imageArea = imageArea;

	setFixedSize(225, 225);
}

void ColorPaletteSwatchArea::paintEvent(QPaintEvent*)
{
	assert(imageArea);

	Image *currentImage = imageArea->getCurrentImage();

	if (!currentImage)
	{
		QPainter painter(this);

		painter.setPen(QPen(Qt::lightGray));
		painter.setBrush(QBrush(Qt::lightGray));
		painter.drawRect(0, 0, width(), height());

		painter.setPen(QPen(Qt::black));
		painter.setBrush(QBrush(Qt::black));
		painter.drawLine(0, 0, width(), height());
		painter.drawLine(width(), 0, 0, height());

		return;
	}

	ImageModel *imageModel = currentImage->getImageModel();
	assert(imageModel);

	ImageColorPaletteModel *imageColorPaletteModel = imageModel->getImageColorPaletteModel();
	assert(imageColorPaletteModel);

	const int numColorSwatchesXY = sqrt(imageColorPaletteModel->MAX_COLORS);

	const float w = width() / numColorSwatchesXY;
	const float h = height() / numColorSwatchesXY;

	QPainter painter(this);

	painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(0, 0, width(), height());

	for (int y = 0; y < numColorSwatchesXY; ++y)
	{
		for (int x = 0; x < numColorSwatchesXY; ++x)
		{
			const unsigned int index = x + numColorSwatchesXY * y;

			QColor color = imageColorPaletteModel->getColor(index);
			painter.setPen(QPen(color));
			painter.setBrush(QBrush(color));
			painter.drawRect(x * w, y * h, w, h);

			if (index == imageColorPaletteModel->getSelectedColorIndex())
			{
				painter.setBrush(QBrush(Qt::transparent));

				painter.setPen(QPen(Qt::white));
				painter.drawRect(x * w, y * h, w - 1, h - 1);

				painter.setPen(QPen(Qt::black));
				painter.drawRect(x * w + 1, y * h + 1, w - 3, h - 3);
			}
		}
	}
}

void ColorPaletteSwatchArea::mouseReleaseEvent(QMouseEvent *event)
{
	assert(event);

	if (event->button() != Qt::LeftButton)
		return;

	const int x = event->x();
	const int y = event->y();
	const int w = width();
	const int h = height();

	if (x < 0 || x >= w ||y < 0 || y >= h)
		return;

	assert(imageArea);

	Image *currentImage = imageArea->getCurrentImage();

	if (!currentImage)
		return;

	ImageModel *imageModel = currentImage->getImageModel();
	assert(imageModel);

	ImageColorPaletteModel *imageColorPaletteModel = imageModel->getImageColorPaletteModel();
	assert(imageColorPaletteModel);

	const int numColorSwatchesXY = sqrt(imageColorPaletteModel->MAX_COLORS);

	assert(w > 0);
	const int clickColumn = (int)(x * ((float)numColorSwatchesXY / w));

	assert(h > 0);
	const int clickRow = (int)(y * ((float)numColorSwatchesXY / h));

	imageColorPaletteModel->setSelectedColorIndex(clickRow * numColorSwatchesXY + clickColumn);

	repaint();
}

void ColorPaletteSwatchArea::mouseDoubleClickEvent(QMouseEvent *event)
{
	assert(event);

	if (event->button() != Qt::LeftButton)
		return;

	assert(imageArea);

	Image *currentImage = imageArea->getCurrentImage();

	if (!currentImage)
		return;

	emit onDoubleClick();
}
