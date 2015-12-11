#pragma once

#include <QtWidgets>

#include "../PreviewWindow/PreviewWindow.hpp"
#include "../SideBar/ColorPalette/ColorPaletteSwatchArea.hpp"
#include "../SideBar/DrawingTools/DrawingToolsModel.hpp"

class ImageWindow : public QWidget
{
	Q_OBJECT

public:
	ImageWindow(ColorPaletteSwatchArea *colorPaletteSwatchArea, DrawingToolsModel *drawingToolsModel, PreviewWindow *previewWindow);
	~ImageWindow();

	void newEmpty(unsigned int width, unsigned int height);
	bool importFromImageFile(const QString &fileName);
	void exportToImageFile(const QString &fileName);

	void importColorPalette(const QString &fileName);

	void zoomIn();
	void zoomOut();

	QImage *getImage();
	QColor getSelectedColor();
	void setSelectedColor(const QColor &color);
	unsigned char getSelectedColorIndex();
	void setSelectedColorIndex(unsigned char index);

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void closeEvent(QCloseEvent *event);

private:
	const unsigned int MAX_ZOOM_FACTOR = 16;
	const unsigned int MAX_COLORS_IN_PALETTE = 256;

	QImage *image;
	ColorPaletteSwatchArea *colorPaletteSwatchArea;
	DrawingToolsModel *drawingToolsModel;
	PreviewWindow *previewWindow;
	unsigned short zoomFactor;
	unsigned char selectedColorIndex;

	void updateTitle();
	void clipColorPaletteToNearestPowerOfTwo();
	void makeDefaultColorPalette();
};
