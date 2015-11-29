#pragma once

#include <QtWidgets>

#include "DrawingToolsModel.hpp"

class DrawingToolsRollOut : public QWidget
{
	Q_OBJECT

public:
	DrawingToolsRollOut();

	DrawingToolsModel *getDrawingToolsModel();

private:
	static const int TOOL_BUTTON_SIZE = 45;

	DrawingToolsModel *drawingToolsModel;

private slots:
	void selectButtonClicked();
	void brushButtonClicked();
	void colorPickerButtonClicked();
	void rectangleButtonClicked();
	void circleButtonClicked();
};
