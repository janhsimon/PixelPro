#include <assert.h>

#include "ColorPaletteSwatchArea.hpp"
#include "../../ImageArea/ImageArea.hpp"

ColorPaletteSwatchArea::ColorPaletteSwatchArea()
{
	setFixedSize(225, 225);

	//for (int i = 0; i < MAX_COLOR_HOTKEYS; ++i)
		//hotkeyedColors[i] = i;
}

/*
void ColorPaletteSwatchArea::hotkeySelectedColor(short hotkeyGroup)
{
	assert(hotkeyGroup < MAX_COLOR_HOTKEYS);

	ImageWindow *currentImageWindow = ImageArea::getCurrentImageWindow();

	if (!currentImageWindow)
		return;

	const unsigned char selectedColorIndex = currentImageWindow->getSelectedColorIndex();

	for (int i = 0; i < MAX_COLOR_HOTKEYS; ++i)
	{
		if (hotkeyedColors[i] == selectedColorIndex)
			hotkeyedColors[i] = -1;
	}

	hotkeyedColors[hotkeyGroup] = selectedColorIndex;
	repaint();
}

void ColorPaletteSwatchArea::recallHotkeyedColor(short hotkeyGroup)
{
	assert(hotkeyGroup >= 0 && hotkeyGroup < MAX_COLOR_HOTKEYS);

	ImageWindow *currentImageWindow = ImageArea::getCurrentImageWindow();

	if (!currentImageWindow)
		return;

	currentImageWindow->setSelectedColorIndex(hotkeyGroup);
	repaint();
}
*/

void ColorPaletteSwatchArea::paintEvent(QPaintEvent*)
{
	ImageWindow *currentImageWindow = ImageArea::getCurrentImageWindow();

	if (!currentImageWindow)
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

	QImage *image = currentImageWindow->getImage();
	assert(image);

	const int numColorSwatchesXY = sqrt(image->colorCount());

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

			QColor color = image->color(index);
			painter.setPen(QPen(color));
			painter.setBrush(QBrush(color));
			painter.drawRect(x * w, y * h, w, h);

			if (index == currentImageWindow->getSelectedColorIndex())
			{
				painter.setBrush(QBrush(Qt::transparent));

				painter.setPen(QPen(Qt::white));
				painter.drawRect(x * w, y * h, w - 1, h - 1);

				painter.setPen(QPen(Qt::black));
				painter.drawRect(x * w + 1, y * h + 1, w - 3, h - 3);
			}

			short hotkeyGroupForColorIndex = currentImageWindow->getHotkeyGroupForColorIndex(index);

			if (hotkeyGroupForColorIndex >= 0)
			{
				const unsigned int numberX = x * w + 2;
				const unsigned int numberY = (y + 1) * h - 2;

				if (color.redF() + color.greenF() + color.blueF() > 1.5f)
				// bright color
					// so write text in black
					painter.setPen(QPen(Qt::black));
				else
				// dark color
					// write text in white
					painter.setPen(QPen(Qt::white));

				painter.drawText(QPoint(numberX, numberY), QString::number(hotkeyGroupForColorIndex));
			}
		}
	}
}

void ColorPaletteSwatchArea::mousePressEvent(QMouseEvent *event)
{
	assert(event);

	//if (event->button() != Qt::LeftButton)
		//return;

	const int x = event->x();
	const int y = event->y();
	const int w = width();
	const int h = height();

	if (x < 0 || x >= w ||y < 0 || y >= h)
		return;

	ImageWindow *currentImageWindow = ImageArea::getCurrentImageWindow();

	if (!currentImageWindow)
		return;

	QImage *image = currentImageWindow->getImage();
	assert(image);

	const int numColorSwatchesXY = sqrt(image->colorCount());

	assert(w > 0);
	const int clickColumn = (int)(x * ((float)numColorSwatchesXY / w));

	assert(h > 0);
	const int clickRow = (int)(y * ((float)numColorSwatchesXY / h));

	currentImageWindow->setSelectedColorIndex(clickRow * numColorSwatchesXY + clickColumn);

	repaint();
}

void ColorPaletteSwatchArea::mouseMoveEvent(QMouseEvent *event)
{
	mousePressEvent(event);
}

void ColorPaletteSwatchArea::mouseReleaseEvent(QMouseEvent *event)
{
	mousePressEvent(event);
}

void ColorPaletteSwatchArea::mouseDoubleClickEvent(QMouseEvent *event)
{
	assert(event);

	if (event->button() != Qt::LeftButton)
		return;

	ImageWindow *currentImageWindow = ImageArea::getCurrentImageWindow();

	if (!currentImageWindow)
		return;

	emit onDoubleClick();
}
