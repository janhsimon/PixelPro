#include <assert.h>

#include "SideBar.hpp"
#include "ColorPaletteModel.hpp"

SideBar::SideBar()
{
	drawingToolsRollOutButton = new QPushButton(QIcon("E:/Qt Projects/PixelPro/images/new.png"), tr("Drawing Tools"));
	drawingToolsRollOutButton->setStyleSheet("Text-align:left");

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

ColorPaletteRollOut *SideBar::getColorPaletteRollOut()
{
	assert(colorPaletteRollOut);
	return colorPaletteRollOut;
}

void SideBar::toggleColorPaletteRollOut()
{
	assert(layout);
	assert(colorPaletteRollOut);
	colorPaletteRollOut->setVisible(!colorPaletteRollOut->isVisible());
}
