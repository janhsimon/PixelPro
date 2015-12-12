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
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void closeEvent(QCloseEvent *event);

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

	QMenu *windowMenu;
	QAction *closeWindowAction;
	QAction *showPreviewWindowAction;

	void createSideBar();
	void createImageArea(SideBar *sideBar, PreviewWindow *previewWindow);
	void createFileMenu();
	void createColorPaletteMenu();
	void createViewMenu();
	void createWindowMenu();


private slots:
	void repaintColorPaletteSwatchArea();
	void updateCurrentColorPaletteColor(const QColor &color);
};
