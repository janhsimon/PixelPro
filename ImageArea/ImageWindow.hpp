#pragma once

#include <QtWidgets>

#include "Image.hpp"
#include "ImageScrollBarFilter.hpp"
#include "../PreviewWindow/PreviewWindow.hpp"
#include "../SideBar/SideBar.hpp"

class ImageWindow : public QWidget
{
	Q_OBJECT

public:
	ImageWindow(unsigned int width, unsigned int height, SideBar *sideBar, PreviewWindow *previewWindow);
	~ImageWindow();

	Image *getImage();

protected:
	virtual void closeEvent(QCloseEvent *event);

private:
	QScrollArea *scrollArea;
	Image *image;
	ImageScrollBarFilter *imageScrollBarFilter;
	SideBar *sideBar;
	PreviewWindow *previewWindow;

	void updateTitle();
};
