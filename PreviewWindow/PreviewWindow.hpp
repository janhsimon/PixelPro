#pragma once

#include <QtWidgets>

class PreviewWindow : public QWidget
{
	Q_OBJECT

public:
	PreviewWindow(QWidget *parent);

	void setInitialPosition(const QPoint &position);

	void zoomIn();
	void zoomOut();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	const unsigned int MAX_ZOOM_FACTOR = 4;

	unsigned int zoomFactor;

public slots:
	void updatePreview();
};
