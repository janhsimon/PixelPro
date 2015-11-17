#include <assert.h>

#include "ColorPaletteWindowView.hpp"

ColorPaletteWindowView::ColorPaletteWindowView(QWidget *parent) : QWidget(parent)
{
	colorPaletteModel = new ColorPaletteModel();

	move(parent->pos() + QPoint(-2.f, 50.f));
	setFixedSize(256, 64);
	setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

ColorPaletteWindowView::~ColorPaletteWindowView()
{
	assert(colorPaletteModel);
	delete colorPaletteModel;
}
