#pragma once

enum DrawingTool
{
	BRUSH,
	COLOR_PICKER
};

class DrawingToolsModel
{
public:
	DrawingToolsModel();

	DrawingTool getActiveDrawingTool();
	void setActiveDrawingTool(DrawingTool activeDrawingTool);

private:
	DrawingTool activeDrawingTool;
};
