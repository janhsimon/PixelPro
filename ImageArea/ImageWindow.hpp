#pragma once

#include <QtWidgets>

#include "Image.hpp"
#include "../PreviewWindow/PreviewWindow.hpp"
#include "../SideBar/SideBar.hpp"

class ImageWindow : public QWidget
{
	Q_OBJECT

public:
	ImageWindow(SideBar *sideBar, PreviewWindow *previewWindow);
	~ImageWindow();

	Image *getImage();

protected:
	virtual void wheelEvent(QWheelEvent *event);
	virtual void closeEvent(QCloseEvent *event);

private:
	Image *image;
	SideBar *sideBar;
	PreviewWindow *previewWindow;

	void updateTitle();
};
