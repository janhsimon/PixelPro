#pragma once

#include <QtWidgets>

#include "../../ImageArea/ImageArea.hpp"

class ColorPaletteSwatchArea : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteSwatchArea(ImageArea *imageArea);

	void paintEvent(QPaintEvent*);

protected:
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
	ImageArea *imageArea;

signals:
	void onDoubleClick();
};
