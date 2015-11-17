#pragma once

#include <QVBoxLayout>
#include <QWidget>

#include "Delegate/ColorPaletteSwatchesDelegate.hpp"
#include "Model/ColorPaletteModel.hpp"

class ColorPaletteWindowView : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteWindowView(QWidget *parent = 0);
	~ColorPaletteWindowView();

	ColorPaletteSwatchesDelegate *getColorPaletteSwatchesDelegate();

private:
	QVBoxLayout *layout;
	ColorPaletteModel *colorPaletteModel;
	ColorPaletteSwatchesDelegate *colorPaletteSwatchesDelegate;
};
