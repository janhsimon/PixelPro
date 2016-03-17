#pragma once

#include <QtWidgets>

#include "ImageWindow.hpp"
#include "../PreviewWindow/PreviewWindow.hpp"
#include "../SideBar/SideBar.hpp"

class ImageArea : public QMdiArea
{
	Q_OBJECT

public:
	ImageArea(SideBar *sideBar, PreviewWindow *previewWindow);

	static ImageWindow *getCurrentImageWindow();
	static Image *getCurrentImage();

private:
	SideBar *sideBar;
	PreviewWindow *previewWindow;
	static ImageWindow *currentImageWindow;

public slots:
	void newProject(unsigned int width, unsigned int height);
	void openProject();
	void saveProject();
	void saveProjectAs();
	void importImage();
	void exportImage();
	void zoomIn();
	void zoomOut();
	void toggleGrid();

private slots:
	void setCurrentImageWindow(QMdiSubWindow *currentImageWindow);
};
