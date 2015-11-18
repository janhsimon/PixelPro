#include <assert.h>

#include "ColorPaletteRollOut.hpp"

ColorPaletteRollOut::ColorPaletteRollOut(ColorPaletteModel *colorPaletteModel)
{
	assert(colorPaletteModel);
	this->colorPaletteModel = colorPaletteModel;

	colorPaletteSwatchArea = new ColorPaletteSwatchArea(colorPaletteModel);

	QPushButton *editButton = new QPushButton(tr("Edit"));
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *sortButton = new QPushButton(tr("Sort"));
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *swapValuesButton = new QPushButton(tr("Swap Values"));
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *swapIndexButton = new QPushButton(tr("Swap Index"));
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *importButton = new QPushButton(tr("Import"));
	connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *exportButton = new QPushButton(tr("Export"));
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QHBoxLayout *firstButtonRow = new QHBoxLayout();
	firstButtonRow->setMargin(0);
	firstButtonRow->addWidget(editButton);
	firstButtonRow->addWidget(sortButton);

	QHBoxLayout *secondButtonRow = new QHBoxLayout();
	secondButtonRow->setMargin(0);
	secondButtonRow->addWidget(swapValuesButton);
	secondButtonRow->addWidget(swapIndexButton);

	QHBoxLayout *thirdButtonRow = new QHBoxLayout();
	thirdButtonRow->setMargin(0);
	thirdButtonRow->addWidget(importButton);
	thirdButtonRow->addWidget(exportButton);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->addWidget(colorPaletteSwatchArea);
	layout->addLayout(firstButtonRow);
	layout->addLayout(secondButtonRow);
	layout->addLayout(thirdButtonRow);
	setLayout(layout);
}

void ColorPaletteRollOut::importColorPalette()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Import Color Palette"), "", tr("Palette Definition Files (*.pal)"));

	if (fileName.isNull() || fileName.isEmpty())
		return;

	assert(colorPaletteModel);
	colorPaletteModel->import(fileName);
}
