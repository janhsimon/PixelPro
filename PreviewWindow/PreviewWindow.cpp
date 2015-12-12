#include <assert.h>

#include "PreviewWindow.hpp"
#include "../ImageArea/ImageArea.hpp"

PreviewWindow::PreviewWindow(QWidget *parent) : QWidget(parent)
{
	setMinimumSize(320, 200);
	setWindowTitle("Preview Window");
	setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	show();

	zoomFactor = 1;
}

void PreviewWindow::setInitialPosition(const QPoint &position)
{
	move((position.x() - width()) - 80, position.y() + 53);
}

void PreviewWindow::zoomIn()
{
	if (zoomFactor >= MAX_ZOOM_FACTOR)
	{
		zoomFactor = MAX_ZOOM_FACTOR;
		return;
	}

	zoomFactor++;

	repaint();
}

void PreviewWindow::zoomOut()
{
	if (zoomFactor <= 1)
	{
		zoomFactor = 1;
		return;
	}

	zoomFactor--;

	repaint();
}

void PreviewWindow::paintEvent(QPaintEvent*)
{
	assert(zoomFactor > 0);

	Image *currentImage = ImageArea::getCurrentImage();

	QPainter painter(this);

	if (!currentImage)
	{
		painter.setPen(QPen(Qt::lightGray));
		painter.setBrush(QBrush(Qt::lightGray));
		painter.drawRect(0, 0, width(), height());

		painter.setPen(QPen(Qt::black));
		painter.setBrush(QBrush(Qt::black));
		painter.drawLine(0, 0, width(), height());
		painter.drawLine(width(), 0, 0, height());

		return;
	}

	QImage *image = currentImage->getImage();
	assert(image);

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

void PreviewWindow::wheelEvent(QWheelEvent *event)
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

void PreviewWindow::updatePreview()
{
	repaint();
}
