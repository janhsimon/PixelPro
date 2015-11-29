#pragma once

#include <QtWidgets>

#include "Image.hpp"
#include "ImageColorPaletteModel.hpp"

class ImageArea : public QMdiArea
{
	Q_OBJECT

public:
	ImageArea();

	Image *getCurrentImage();

public slots:
	void newProject();
	void openProject();
	void saveProject();
	void saveProjectAs();
	void importImage();
	void exportImage();
	void zoomInCurrentImage();
	void zoomOutCurrentImage();
};
