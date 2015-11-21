#pragma once

#include <QtWidgets>

#include "../SideBar/ColorPaletteModel.hpp"

class Image : public QWidget
{
	Q_OBJECT

public:
	Image(ColorPaletteModel *colorPaletteModel);

	void newEmpty();
	bool open(const QString &fileName);
	void saveAs(const QString &fileName);

	void zoomIn();
	void zoomOut();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	const int MAX_ZOOM_FACTOR = 16;

	ColorPaletteModel *colorPaletteModel;
	QPixmap *pixmap;
	int zoomFactor;

	void updateTitle();
};
