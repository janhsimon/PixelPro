#pragma once

#include <QWidget>

#include "Model/ColorPaletteModel.hpp"

class ColorPaletteSwatchesDelegate : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteSwatchesDelegate(ColorPaletteModel *colorPaletteModel);

	void paintEvent(QPaintEvent*);

protected:
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	ColorPaletteModel *colorPaletteModel;

	unsigned short selectedColorSwatchIndex;

public slots:
	void importColorPalette();
};
