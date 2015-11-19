#pragma once

#include <QtWidgets>

//#include "ColorPaletteSwatchArea.hpp"
//#include "ColorPaletteModel.hpp"

class DrawingToolsRollOut : public QWidget
{
	Q_OBJECT

public:
	DrawingToolsRollOut(/*ColorPaletteModel *colorPaletteModel*/);

private:
	static const int TOOL_BUTTON_SIZE = 45;

	//ColorPaletteModel *colorPaletteModel;
	//ColorPaletteSwatchArea *colorPaletteSwatchArea;
};
