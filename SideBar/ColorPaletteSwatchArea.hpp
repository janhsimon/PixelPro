#pragma once

#include "ColorPaletteModel.hpp"

class ColorPaletteSwatchArea : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteSwatchArea(ColorPaletteModel *colorPaletteModel);

	void paintEvent(QPaintEvent*);

protected:
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	ColorPaletteModel *colorPaletteModel;
};
