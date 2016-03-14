#include <assert.h>

#include "PreviewWindow.hpp"
#include "../ImageArea/ImageArea.hpp"

PreviewWindow::PreviewWindow(QWidget *parent) : QWidget(parent)
{
	setMinimumSize(320, 200);
	setWindowTitle("Preview Window");
	setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
	show();

	//zoomFactor = 1;

	scrollArea = new QScrollArea();
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setBackgroundRole(QPalette::Dark);
}

/*
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
*/

void PreviewWindow::paintEvent(QPaintEvent*)
{
    /*
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

    QRect rect(0, 0, image->width(), image->height());
	painter.drawImage(rect, *image);

	setMinimumSize(image->width(), image->height());
	setMaximumSize(minimumSize());
    */
}

/*
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
*/

void PreviewWindow::updatePreview()
{
	repaint();
}
