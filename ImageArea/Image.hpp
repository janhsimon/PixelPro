#pragma once

#include <QtWidgets>

#include "ImageModel.hpp"

class Image : public QWidget
{
	Q_OBJECT

public:
	Image();
	~Image();

	void newEmpty(unsigned int width, unsigned int height);
	bool importFromImageFile(const QString &fileName);
	void exportToImageFile(const QString &fileName);

	void zoomIn();
	void zoomOut();

	ImageModel *getImageModel();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	const unsigned int MAX_ZOOM_FACTOR = 16;
	const unsigned int MIN_WINDOW_WIDTH = 256;
	const unsigned int MIN_WINDOW_HEIGHT = 256;

	ImageModel *imageModel;
	unsigned int zoomFactor;

	void updateTitle();
};
