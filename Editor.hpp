#pragma once

#include "ImageArea/ImageArea.hpp"
#include "SideBar/SideBar.hpp"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor();
	~Editor();

private:
	SideBar *sideBar;
	ImageArea *imageArea;
	QSplitter *splitter;

	QMenu *fileMenu;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;
	QAction *exitAction;

	QMenu *colorPaletteMenu;
	QAction *loadColorPaletteAction;

	QMenu *viewMenu;
	QAction *zoomInAction;
	QAction *zoomOutAction;

	void createFileMenu();
	void createColorPaletteMenu();
	void createViewMenu();
};
