#pragma once

#include <QtWidgets>

#include "../PreviewWindow/PreviewWindow.hpp"
#include "../SideBar/SideBar.hpp"

class Image : public QWidget
{
	Q_OBJECT

public:
	Image(unsigned int width, unsigned int height, SideBar *sideBar, PreviewWindow *previewWindow);
	~Image();

	bool importFromImageFile(const QString &fileName);
	void exportToImageFile(const QString &fileName);

	void importColorPalette(const QString &fileName);

	void zoomIn();
	void zoomOut();
	unsigned short getZoomFactor() { return zoomFactor; }

	QImage *getImage();
	QColor getSelectedColor();
	void setSelectedColor(const QColor &color);
	unsigned char getSelectedColorIndex();
	void setSelectedColorIndex(unsigned char index);
	void hotkeySelectedColor(short hotkeyGroup);
	void recallHotkeyedColor(short hotkeyGroup);
	short getHotkeyGroupForColorIndex(unsigned char index);

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

private:
	const static unsigned int MAX_ZOOM_FACTOR = 16;
	const static unsigned int MAX_COLORS_IN_PALETTE = 256;
	const static unsigned char MAX_COLOR_HOTKEYS = 10;

	QImage *image;
	SideBar *sideBar;
	PreviewWindow *previewWindow;
	unsigned short zoomFactor;
	unsigned char selectedColorIndex;
	short hotkeyedColors[MAX_COLOR_HOTKEYS];

	void clipColorPaletteToNearestPowerOfTwo();
	void makeDefaultColorPalette();
	void resetColorPaletteHotkeys();
	void updateWidgetSize();
};
