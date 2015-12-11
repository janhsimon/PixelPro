#pragma once

#include <QtWidgets>

#include "DrawingToolsModel.hpp"

class DrawingToolsRollOut : public QWidget
{
	Q_OBJECT

public:
	DrawingToolsRollOut();

	DrawingToolsModel *getDrawingToolsModel();

	QPushButton *getSelectButton();
	QPushButton *getBrushButton();
	QPushButton *getColorPickerButton();
	QPushButton *getRectangleButton();
	QPushButton *getCircleButton();

private:
	static const int TOOL_BUTTON_SIZE = 45;

	DrawingToolsModel *drawingToolsModel;

	QPushButton *selectButton;
	QPushButton *brushButton;
	QPushButton *colorPickerButton;
	QPushButton *rectangleButton;
	QPushButton *circleButton;

private slots:
	void selectButtonClicked();
	void brushButtonClicked();
	void colorPickerButtonClicked();
	void rectangleButtonClicked();
	void circleButtonClicked();
};
