#include <assert.h>

#include "DrawingToolsRollOut.hpp"

DrawingToolsRollOut::DrawingToolsRollOut(/*ColorPaletteModel *colorPaletteModel*/)
{
	//assert(colorPaletteModel);
	//this->colorPaletteModel = colorPaletteModel;

	QPushButton *selectButton = new QPushButton(tr("Select"));
	selectButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	selectButton->setCheckable(true);
	selectButton->setChecked(false);
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *brushButton = new QPushButton(tr("Brush"));
	brushButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	brushButton->setCheckable(true);
	brushButton->setChecked(true);
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *colorPickerButton = new QPushButton(tr("Color Picker"));
	colorPickerButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	colorPickerButton->setCheckable(true);
	colorPickerButton->setChecked(false);
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *rectangleButton = new QPushButton(tr("Rectangle"));
	rectangleButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	rectangleButton->setCheckable(true);
	rectangleButton->setChecked(false);
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *circleButton = new QPushButton(tr("Circle"));
	circleButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	circleButton->setCheckable(true);
	circleButton->setChecked(false);
	//connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QButtonGroup *toolButtonGroup = new QButtonGroup();
	toolButtonGroup->addButton(selectButton);
	toolButtonGroup->addButton(brushButton);
	toolButtonGroup->addButton(colorPickerButton);
	toolButtonGroup->addButton(rectangleButton);
	toolButtonGroup->addButton(circleButton);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(selectButton);
	layout->addWidget(brushButton);
	layout->addWidget(colorPickerButton);
	layout->addWidget(rectangleButton);
	layout->addWidget(circleButton);
	setLayout(layout);
}
