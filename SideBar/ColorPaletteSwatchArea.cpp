#include <assert.h>

#include "ColorPaletteSwatchArea.hpp"

ColorPaletteSwatchArea::ColorPaletteSwatchArea(ColorPaletteModel *colorPaletteModel)
{
	assert(colorPaletteModel);
	this->colorPaletteModel = colorPaletteModel;

	setFixedSize(225, 225);

	selectedColorSwatchIndex = 0;
}

void ColorPaletteSwatchArea::paintEvent(QPaintEvent*)
{
	const int numColorSwatchesXY = sqrt(colorPaletteModel->MAX_COLORS);

	const float w = width() / numColorSwatchesXY;
	const float h = height() / numColorSwatchesXY;

	QPainter painter(this);

	painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(0, 0, width(), height());

	assert(colorPaletteModel);

	for (int y = 0; y < numColorSwatchesXY; ++y)
	{
		for (int x = 0; x < numColorSwatchesXY; ++x)
		{
			const unsigned int index = x + numColorSwatchesXY * y;

			QColor color = colorPaletteModel->getColor(index);
			painter.setPen(QPen(color));
			painter.setBrush(QBrush(color));
			painter.drawRect(x * w, y * h, w, h);

			if (index == selectedColorSwatchIndex)
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

	assert(colorPaletteModel);

	const int numColorSwatchesXY = sqrt(colorPaletteModel->MAX_COLORS);

	assert(w > 0);
	const int clickColumn = (int)(x * ((float)numColorSwatchesXY / w));

	assert(h > 0);
	const int clickRow = (int)(y * ((float)numColorSwatchesXY / h));

	selectedColorSwatchIndex = clickRow * numColorSwatchesXY + clickColumn;
	assert(selectedColorSwatchIndex >= 0 && selectedColorSwatchIndex < colorPaletteModel->MAX_COLORS);

	repaint();
}
