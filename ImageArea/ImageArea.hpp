#pragma once

#include <QtWidgets>

#include "Image.hpp"

class ImageArea : public QMdiArea
{
	Q_OBJECT

public:
	ImageArea();

private:
	Image *getCurrentImage();

public slots:
	void newImage();
	void openImage();
	void zoomInCurrentImage();
	void zoomOutCurrentImage();
};
