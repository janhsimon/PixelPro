#pragma once

#include <QtWidgets>

#include "ImageModel.hpp"
#include "../PreviewWindow/PreviewWindow.hpp"
#include "../SideBar/ColorPalette/ColorPaletteSwatchArea.hpp"
#include "../SideBar/DrawingTools/DrawingToolsModel.hpp"

class Image : public QWidget
{
	Q_OBJECT

public:
	Image(ColorPaletteSwatchArea *colorPaletteSwatchArea, DrawingToolsModel *drawingToolsModel, PreviewWindow *previewWindow);
	~Image();

	void newEmpty(unsigned int width, unsigned int height);
	bool importFromImageFile(const QString &fileName);
	void exportToImageFile(const QString &fileName);

	void zoomIn();
	void zoomOut();

	ImageModel *getImageModel();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	const unsigned int MAX_ZOOM_FACTOR = 16;
	const unsigned int MIN_WINDOW_WIDTH = 256;
	const unsigned int MIN_WINDOW_HEIGHT = 256;

	ImageModel *imageModel;
	ColorPaletteSwatchArea *colorPaletteSwatchArea;
	DrawingToolsModel *drawingToolsModel;
	PreviewWindow *previewWindow;
	unsigned int zoomFactor;

	void updateTitle();
};
