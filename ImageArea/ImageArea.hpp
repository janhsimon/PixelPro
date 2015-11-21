#pragma once

#include <QtWidgets>

#include "Image.hpp"
#include "../SideBar/ColorPaletteModel.hpp"

class ImageArea : public QMdiArea
{
	Q_OBJECT

public:
	ImageArea(ColorPaletteModel *colorPaletteModel);

private:
	ColorPaletteModel *colorPaletteModel;

	Image *getCurrentImage();

public slots:
	void newImage();
	void openImage();
	void saveImageAs();
	void zoomInCurrentImage();
	void zoomOutCurrentImage();
};
