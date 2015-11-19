#include <assert.h>

#include "SideBar.hpp"
#include "ColorPaletteModel.hpp"

SideBar::SideBar()
{
	drawingToolsRollOutButton = new QPushButton(QIcon("E:/Qt Projects/PixelPro/images/new.png"), tr("Drawing Tools"));
	drawingToolsRollOutButton->setStyleSheet("Text-align:left");
	drawingToolsRollOut = new DrawingToolsRollOut();
	connect(drawingToolsRollOutButton, SIGNAL(clicked()), this, SLOT(toggleDrawingToolsRollOut()));

	colorPaletteModel = new ColorPaletteModel();
	colorPaletteRollOutButton = new QPushButton(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("Color Palette"));
	colorPaletteRollOutButton->setStyleSheet("Text-align:left");
	colorPaletteRollOut = new ColorPaletteRollOut(colorPaletteModel);
	connect(colorPaletteRollOutButton, SIGNAL(clicked()), this, SLOT(toggleColorPaletteRollOut()));

	tileGridRollOutButton = new QPushButton(QIcon("E:/Qt Projects/PixelPro/images/save.png"), tr("Tile Grid"));
	tileGridRollOutButton->setStyleSheet("Text-align:left");

	animationRollOutButton = new QPushButton(QIcon("E:/Qt Projects/PixelPro/images/new.png"), tr("Animation"));
	animationRollOutButton->setStyleSheet("Text-align:left");

	layout = new QVBoxLayout();
	layout->addWidget(drawingToolsRollOutButton);
	layout->addWidget(drawingToolsRollOut);
	layout->addWidget(colorPaletteRollOutButton);
	layout->addWidget(colorPaletteRollOut);
	layout->addWidget(tileGridRollOutButton);
	layout->addWidget(animationRollOutButton);
	layout->addStretch(1);
	setLayout(layout);

	setFixedWidth(244);
}

SideBar::~SideBar()
{
	assert(drawingToolsRollOut);
	delete drawingToolsRollOut;

	assert(drawingToolsRollOutButton);
	delete drawingToolsRollOutButton;

	assert(colorPaletteModel);
	delete colorPaletteModel;

	assert(colorPaletteRollOut);
	delete colorPaletteRollOut;

	assert(colorPaletteRollOutButton);
	delete colorPaletteRollOutButton;

	assert(tileGridRollOutButton);
	delete tileGridRollOutButton;

	assert(animationRollOutButton);
	delete animationRollOutButton;

	assert(layout);
	delete layout;
}

DrawingToolsRollOut *SideBar::getDrawingToolsRollOut()
{
	assert(drawingToolsRollOut);
	return drawingToolsRollOut;
}

ColorPaletteRollOut *SideBar::getColorPaletteRollOut()
{
	assert(colorPaletteRollOut);
	return colorPaletteRollOut;
}

void SideBar::toggleDrawingToolsRollOut()
{
	assert(layout);
	assert(drawingToolsRollOut);
	drawingToolsRollOut->setVisible(!drawingToolsRollOut->isVisible());
}

void SideBar::toggleColorPaletteRollOut()
{
	assert(layout);
	assert(colorPaletteRollOut);
	colorPaletteRollOut->setVisible(!colorPaletteRollOut->isVisible());
}
