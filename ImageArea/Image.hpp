#pragma once

#include <QtWidgets>

class Image : public QWidget
{
	Q_OBJECT

public:
	Image();

	void newEmpty();
	bool open(const QString &fileName);

	void zoomIn();
	void zoomOut();

	void paintEvent(QPaintEvent *event);

private:
	const int MAX_ZOOM_FACTOR = 16;

	QPixmap *pixmap;
	int zoomFactor;

	void updateTitle();
};
