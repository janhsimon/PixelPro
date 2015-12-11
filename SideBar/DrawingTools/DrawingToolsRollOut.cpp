#include <assert.h>

#include "DrawingToolsRollOut.hpp"

DrawingToolsRollOut::DrawingToolsRollOut()
{
	drawingToolsModel = new DrawingToolsModel();

	selectButton = new QPushButton(tr("Select"));
	selectButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	selectButton->setCheckable(true);
	selectButton->setChecked(false);
	connect(selectButton, SIGNAL(clicked()), this, SLOT(selectButtonClicked()));

	brushButton = new QPushButton(tr("Brush"));
	brushButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	brushButton->setCheckable(true);
	brushButton->setChecked(true);
	connect(brushButton, SIGNAL(clicked()), this, SLOT(brushButtonClicked()));

	colorPickerButton = new QPushButton(tr("Color Picker"));
	colorPickerButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	colorPickerButton->setCheckable(true);
	colorPickerButton->setChecked(false);
	connect(colorPickerButton, SIGNAL(clicked()), this, SLOT(colorPickerButtonClicked()));

	rectangleButton = new QPushButton(tr("Rectangle"));
	rectangleButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	rectangleButton->setCheckable(true);
	rectangleButton->setChecked(false);
	connect(rectangleButton, SIGNAL(clicked()), this, SLOT(rectangleButtonClicked()));

	circleButton = new QPushButton(tr("Circle"));
	circleButton->setFixedSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE);
	circleButton->setCheckable(true);
	circleButton->setChecked(false);
	connect(circleButton, SIGNAL(clicked()), this, SLOT(circleButtonClicked()));

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

DrawingToolsModel *DrawingToolsRollOut::getDrawingToolsModel()
{
	assert(drawingToolsModel);
	return drawingToolsModel;
}

QPushButton *DrawingToolsRollOut::getSelectButton()
{
	assert(selectButton);
	return selectButton;
}

QPushButton *DrawingToolsRollOut::getBrushButton()
{
	assert(brushButton);
	return brushButton;
}

QPushButton *DrawingToolsRollOut::getColorPickerButton()
{
	assert(colorPickerButton);
	return colorPickerButton;
}

QPushButton *DrawingToolsRollOut::getRectangleButton()
{
	assert(rectangleButton);
	return rectangleButton;
}

QPushButton *DrawingToolsRollOut::getCircleButton()
{
	assert(circleButton);
	return circleButton;
}

void DrawingToolsRollOut::selectButtonClicked()
{
	QMessageBox::warning(nullptr, "Placeholder", "Select Button clicked");

	//assert(drawingToolsModel);
	//drawingToolsModel->setActiveDrawingTool(DrawingTool::SELECTION);
}

void DrawingToolsRollOut::brushButtonClicked()
{
	assert(drawingToolsModel);
	drawingToolsModel->setActiveDrawingTool(DrawingTool::BRUSH);
}

void DrawingToolsRollOut::colorPickerButtonClicked()
{
	assert(drawingToolsModel);
	drawingToolsModel->setActiveDrawingTool(DrawingTool::COLOR_PICKER);
}

void DrawingToolsRollOut::rectangleButtonClicked()
{
	QMessageBox::warning(nullptr, "Placeholder", "Rectangle Button clicked");

	//assert(drawingToolsModel);
	//drawingToolsModel->setActiveDrawingTool(DrawingTool::SELECTION);
}

void DrawingToolsRollOut::circleButtonClicked()
{
	QMessageBox::warning(nullptr, "Placeholder", "Circle Button clicked");

	//assert(drawingToolsModel);
	//drawingToolsModel->setActiveDrawingTool(DrawingTool::SELECTION);
}
