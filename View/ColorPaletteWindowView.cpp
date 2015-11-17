#include <assert.h>

#include "ColorPaletteWindowView.hpp"

ColorPaletteWindowView::ColorPaletteWindowView(QWidget *parent) : QWidget(parent)
{
	move(parent->pos() + QPoint(-2.f, 50.f));
	setFixedSize(256, 256);
	setWindowTitle("Color Palette");
	setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	layout = new QVBoxLayout();
	layout->setMargin(0);
	setLayout(layout);

	colorPaletteModel = new ColorPaletteModel();

	colorPaletteSwatchesDelegate = new ColorPaletteSwatchesDelegate(colorPaletteModel);
	layout->addWidget(colorPaletteSwatchesDelegate);
}

ColorPaletteWindowView::~ColorPaletteWindowView()
{
	assert(colorPaletteSwatchesDelegate);
	delete colorPaletteSwatchesDelegate;

	assert(colorPaletteModel);
	delete colorPaletteModel;

	assert(layout);
	delete layout;
}

ColorPaletteSwatchesDelegate *ColorPaletteWindowView::getColorPaletteSwatchesDelegate()
{
	assert(colorPaletteSwatchesDelegate);
	return colorPaletteSwatchesDelegate;
}
