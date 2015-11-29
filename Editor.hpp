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
	QAction *newProjectAction;
	QAction *openProjectAction;
	QAction *saveProjectAction;
	QAction *saveProjectAsAction;
	QAction *importImageAction;
	QAction *exportImageAction;
	QAction *exitAction;

	QMenu *colorPaletteMenu;
	QAction *importColorPaletteAction;
	QAction *exportColorPaletteAction;

	QMenu *viewMenu;
	QAction *zoomInAction;
	QAction *zoomOutAction;

	void createFileMenu();
	void createColorPaletteMenu();
	void createViewMenu();

private slots:
	void repaintColorPaletteSwatchArea();
	void updateCurrentColorPaletteColor(const QColor &color);
};
