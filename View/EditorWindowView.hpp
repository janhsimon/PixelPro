#pragma once

#include <QMainWindow>
#include <QMdiArea>

#include "ColorPaletteWindowView.hpp"

class EditorWindowView : public QMainWindow
{
	Q_OBJECT

public:
	EditorWindowView();
	~EditorWindowView();

private:
	QMdiArea *mdiArea;
	ColorPaletteWindowView *colorPaletteWindowView;

	QMenu *fileMenu;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;
	QAction *exitAction;

	QMenu *colorPaletteMenu;
	QAction *loadColorPaletteAction;

	void createFileMenu();
	void createColorPaletteMenu();
	void createMDIArea();
};
