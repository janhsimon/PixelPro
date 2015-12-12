#pragma once

#include <QtWidgets>

#include "Image.hpp"

class ImageScrollBarFilter : public QObject
{
public:
	ImageScrollBarFilter(Image *image);

protected:
	virtual bool eventFilter(QObject *object, QEvent *event);

private:
	Image *image;
};
