#pragma once

#include <QtWidgets>

class ColorPaletteSwatchArea : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteSwatchArea();

	void paintEvent(QPaintEvent*);

protected:
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
	void onDoubleClick();
};
