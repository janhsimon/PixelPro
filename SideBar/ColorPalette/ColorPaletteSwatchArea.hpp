#pragma once

#include <QtWidgets>

class ColorPaletteSwatchArea : public QWidget
{
	Q_OBJECT

public:
	ColorPaletteSwatchArea();

	void paintEvent(QPaintEvent*);

	//void hotkeySelectedColor(short hotkeyGroup);
	//void recallHotkeyedColor(short hotkeyGroup);

protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

//private:
	//const static unsigned char MAX_COLOR_HOTKEYS = 10;
	//short hotkeyedColors[MAX_COLOR_HOTKEYS];

signals:
	void onDoubleClick();
};
