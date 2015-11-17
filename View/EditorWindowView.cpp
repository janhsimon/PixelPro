#include <QApplication>
#include <QMenuBar>

#include <assert.h>

#include "EditorWindowView.hpp"

EditorWindowView::EditorWindowView()
{
	colorPaletteWindowView = new ColorPaletteWindowView(this);
	colorPaletteWindowView->show();

	createFileMenu();
	createColorPaletteMenu();
	createMDIArea();
}

EditorWindowView::~EditorWindowView()
{
	assert(colorPaletteWindowView);
	delete colorPaletteWindowView;
}

void EditorWindowView::createFileMenu()
{
	assert(menuBar());

	fileMenu = menuBar()->addMenu(tr("&File"));

	newAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/new.png"), tr("&New"), this);
	newAction->setShortcut(Qt::CTRL + Qt::Key_N);
	//connect(newAction, SIGNAL(triggered()), this, SLOT(newImage()));
	fileMenu->addAction(newAction);

	openAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("&Open..."), this);
	openAction->setShortcut(Qt::CTRL + Qt::Key_O);
	//connect(openAction, SIGNAL(triggered()), this, SLOT(openImage()));
	fileMenu->addAction(openAction);

	saveAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/save.png"), tr("&Save"), this);
	saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
	//connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	fileMenu->addAction(saveAction);

	saveAsAction = new QAction(tr("Save &As..."), this);
	saveAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
	//connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
	fileMenu->addAction(saveAsAction);

	fileMenu->addSeparator();

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(Qt::CTRL + Qt::Key_X);
	connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
	fileMenu->addAction(exitAction);
}

void EditorWindowView::createColorPaletteMenu()
{
	assert(menuBar());

	colorPaletteMenu = menuBar()->addMenu(tr("Color &Palette"));

	loadColorPaletteAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("&Import..."), this);
	loadColorPaletteAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
	connect(loadColorPaletteAction, SIGNAL(triggered()), colorPaletteWindowView->getColorPaletteSwatchesDelegate(), SLOT(importColorPalette()));
	colorPaletteMenu->addAction(loadColorPaletteAction);
}

void EditorWindowView::createMDIArea()
{
	mdiArea = new QMdiArea;
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdiArea);
}
