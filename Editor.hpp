#pragma once

#include "ImageArea/ImageArea.hpp"
#include "PreviewWindow/PreviewWindow.hpp"
#include "SideBar/SideBar.hpp"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor();
	~Editor();

	PreviewWindow *getPreviewWindow();

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	SideBar *sideBar;
	ImageArea *imageArea;
	QSplitter *splitter;

	PreviewWindow *previewWindow;

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

	void createSideBar();
	void createImageArea(SideBar *sideBar, PreviewWindow *previewWindow);
	void createFileMenu();
	void createColorPaletteMenu();
	void createViewMenu();


private slots:
	void repaintColorPaletteSwatchArea();
	void updateCurrentColorPaletteColor(const QColor &color);
};
