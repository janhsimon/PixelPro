#pragma once

#include <QtWidgets>

#include "Image.hpp"
#include "../PreviewWindow/PreviewWindow.hpp"
#include "../SideBar/ColorPalette/ColorPaletteSwatchArea.hpp"
#include "../SideBar/DrawingTools/DrawingToolsModel.hpp"

class ImageArea : public QMdiArea
{
	Q_OBJECT

public:
	ImageArea(ColorPaletteSwatchArea *colorPaletteSwatchArea, DrawingToolsModel *drawingToolsModel, PreviewWindow *previewWindow);

	static Image *getCurrentImage();

private:
	DrawingToolsModel *drawingToolsModel;
	ColorPaletteSwatchArea *colorPaletteSwatchArea;
	PreviewWindow *previewWindow;
	static Image *currentImage;

public slots:
	void newProject();
	void openProject();
	void saveProject();
	void saveProjectAs();
	void importImage();
	void exportImage();
	void zoomInCurrentImage();
	void zoomOutCurrentImage();

private slots:
	void setCurrentImage(QMdiSubWindow *currentImage);
};
