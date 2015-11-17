#pragma once

#include <QWidget>

#include "Model/ColorPaletteModel.hpp"

class ColorPaletteWindowView : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteWindowView(QWidget *parent = 0);
	~ColorPaletteWindowView();

private:
	ColorPaletteModel *colorPaletteModel;
};
