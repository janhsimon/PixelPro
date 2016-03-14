#include <assert.h>

#include "ImageScrollBarFilter.hpp"

ImageScrollBarFilter::ImageScrollBarFilter(Image *image)
{
	assert(image);
	this->image = image;
}

bool ImageScrollBarFilter::eventFilter(QObject *object, QEvent *event)
{
	assert(object);
	assert(event);

	if (event->type() == QEvent::Wheel)
	{
		QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
		assert(wheelEvent);

		//Qt::KeyboardModifiers keyboardModifiers = QApplication::keyboardModifiers();

		//if (keyboardModifiers.testFlag(Qt::ControlModifier))
		{
			assert(image);

			if (wheelEvent->delta() > 0)
				image->zoomIn();
			else if (wheelEvent->delta() < 0)
				image->zoomOut();

			event->accept();
		}

		return true;
	}

	return false;
}
