#include <assert.h>

#include "Editor.hpp"

Editor::Editor()
{
	sideBar = new SideBar();

	//QScrollArea *toolBoxScrollArea = new QScrollArea();
	//toolBoxScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//toolBoxScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	//toolBoxScrollArea->setWidget(toolBoxView);
	//toolBoxScrollArea->setFixedWidth(256);

	imageArea = new ImageArea(sideBar->getColorPaletteModel());

	splitter = new QSplitter();
	splitter->addWidget(sideBar);
	splitter->addWidget(imageArea);
	setCentralWidget(splitter);

	createFileMenu();
	createColorPaletteMenu();
	createViewMenu();
}

Editor::~Editor()
{
	assert(sideBar);
	delete sideBar;

	assert(imageArea);
	delete imageArea;

	assert(splitter);
	delete splitter;
}

void Editor::createFileMenu()
{
	assert(menuBar());
	assert(imageArea);

	fileMenu = menuBar()->addMenu(tr("&File"));

	newAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/new.png"), tr("&New..."), this);
	newAction->setShortcut(Qt::CTRL + Qt::Key_N);
	connect(newAction, SIGNAL(triggered()), imageArea, SLOT(newImage()));
	fileMenu->addAction(newAction);

	openAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("&Open..."), this);
	openAction->setShortcut(Qt::CTRL + Qt::Key_O);
	connect(openAction, SIGNAL(triggered()), imageArea, SLOT(openImage()));
	fileMenu->addAction(openAction);

	saveAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/save.png"), tr("&Save"), this);
	saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
	//connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	fileMenu->addAction(saveAction);

	saveAsAction = new QAction(tr("Save &As..."), this);
	saveAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
	connect(saveAsAction, SIGNAL(triggered()), imageArea, SLOT(saveImageAs()));
	fileMenu->addAction(saveAsAction);

	fileMenu->addSeparator();

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(Qt::CTRL + Qt::Key_X);
	connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
	fileMenu->addAction(exitAction);
}

void Editor::createColorPaletteMenu()
{
	assert(menuBar());
	assert(sideBar);

	colorPaletteMenu = menuBar()->addMenu(tr("Color &Palette"));

	loadColorPaletteAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("&Import..."), this);
	loadColorPaletteAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
	connect(loadColorPaletteAction, SIGNAL(triggered()), sideBar->getColorPaletteRollOut(), SLOT(importColorPalette()));
	colorPaletteMenu->addAction(loadColorPaletteAction);
}

void Editor::createViewMenu()
{
	assert(menuBar());
	assert(imageArea);

	viewMenu = menuBar()->addMenu(tr("&View"));

	zoomInAction = new QAction(tr("Zoom &In"), this);
	zoomInAction->setShortcut(Qt::CTRL + Qt::Key_Plus);
	connect(zoomInAction, SIGNAL(triggered()), imageArea, SLOT(zoomInCurrentImage()));
	viewMenu->addAction(zoomInAction);

	zoomOutAction = new QAction(tr("Zoom &Out"), this);
	zoomOutAction->setShortcut(Qt::CTRL + Qt::Key_Minus);
	connect(zoomOutAction, SIGNAL(triggered()), imageArea, SLOT(zoomOutCurrentImage()));
	viewMenu->addAction(zoomOutAction);
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	Editor editor;
	editor.showMaximized();

	return application.exec();
}
