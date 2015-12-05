#include "DrawingToolsModel.hpp"

DrawingToolsModel::DrawingToolsModel()
{
	activeDrawingTool = DrawingTool::BRUSH;
}

DrawingTool DrawingToolsModel::getActiveDrawingTool()
{
	return activeDrawingTool;
}

void DrawingToolsModel::setActiveDrawingTool(DrawingTool activeDrawingTool)
{
	this->activeDrawingTool = activeDrawingTool;
}
