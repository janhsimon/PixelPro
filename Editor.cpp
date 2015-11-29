#include <assert.h>

#include "Editor.hpp"

Editor::Editor()
{
	imageArea = new ImageArea();
	sideBar = new SideBar(imageArea);

	connect(imageArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(repaintColorPaletteSwatchArea()));

	ColorPaletteRollOut *colorPaletteRollOut = sideBar->getColorPaletteRollOut();
	assert(colorPaletteRollOut);
	QColorDialog *colorDialog = colorPaletteRollOut->getColorDialog();
	assert(colorDialog);
	connect(colorDialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(updateCurrentColorPaletteColor(QColor)));

	ColorPaletteSwatchArea *colorPaletteSwatchArea = colorPaletteRollOut->getColorPaletteSwatchArea();
	assert(colorPaletteSwatchArea);
	connect(colorPaletteSwatchArea, SIGNAL(onDoubleClick()), colorPaletteRollOut, SLOT(editColor()));

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

	newProjectAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/new.png"), tr("&New Project..."), this);
	newProjectAction->setShortcut(Qt::CTRL + Qt::Key_N);
	connect(newProjectAction, SIGNAL(triggered()), imageArea, SLOT(newProject()));
	fileMenu->addAction(newProjectAction);

	openProjectAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("&Open Project..."), this);
	openProjectAction->setShortcut(Qt::CTRL + Qt::Key_O);
	connect(openProjectAction, SIGNAL(triggered()), imageArea, SLOT(openProject()));
	fileMenu->addAction(openProjectAction);

	saveProjectAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/save.png"), tr("&Save Project"), this);
	saveProjectAction->setShortcut(Qt::CTRL + Qt::Key_S);
	connect(saveProjectAction, SIGNAL(triggered()), imageArea, SLOT(saveProject()));
	fileMenu->addAction(saveProjectAction);

	saveProjectAsAction = new QAction(tr("Save Project &As..."), this);
	saveProjectAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
	connect(saveProjectAsAction, SIGNAL(triggered()), imageArea, SLOT(saveProjectAs()));
	fileMenu->addAction(saveProjectAsAction);

	fileMenu->addSeparator();

	importImageAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("&Import Image..."), this);
	//importImageAction->setShortcut(Qt::CTRL + Qt::Key_I);
	connect(importImageAction, SIGNAL(triggered()), imageArea, SLOT(importImage()));
	fileMenu->addAction(importImageAction);

	exportImageAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/save.png"), tr("&Export Image..."), this);
	//exportImageAction->setShortcut(Qt::CTRL + Qt::Key_E);
	connect(exportImageAction, SIGNAL(triggered()), imageArea, SLOT(exportImage()));
	fileMenu->addAction(exportImageAction);

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

	importColorPaletteAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/open.png"), tr("&Import Color Palette..."), this);
	//importColorPaletteAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
	connect(importColorPaletteAction, SIGNAL(triggered()), sideBar->getColorPaletteRollOut(), SLOT(importColorPalette()));
	colorPaletteMenu->addAction(importColorPaletteAction);

	exportColorPaletteAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/save.png"), tr("&Export Color Palette..."), this);
	//exportColorPaletteAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
	connect(exportColorPaletteAction, SIGNAL(triggered()), sideBar->getColorPaletteRollOut(), SLOT(exportColorPalette()));
	colorPaletteMenu->addAction(exportColorPaletteAction);
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

void Editor::repaintColorPaletteSwatchArea()
{
	assert(sideBar);
	ColorPaletteRollOut *colorPaletteRollOut = sideBar->getColorPaletteRollOut();
	assert(colorPaletteRollOut);
	ColorPaletteSwatchArea *colorPaletteSwatchArea = colorPaletteRollOut->getColorPaletteSwatchArea();
	assert(colorPaletteSwatchArea);
	colorPaletteSwatchArea->repaint();
}

void Editor::updateCurrentColorPaletteColor(const QColor &color)
{
	assert(imageArea);
	Image *image = imageArea->getCurrentImage();
	assert(image);
	ImageModel *imageModel = image->getImageModel();
	assert(imageModel);
	ImageColorPaletteModel *imageColorPaletteModel = imageModel->getImageColorPaletteModel();
	assert(imageColorPaletteModel);
	imageColorPaletteModel->setSelectedColor(color);
	image->repaint();
	repaintColorPaletteSwatchArea();
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	Editor editor;
	editor.showMaximized();

	return application.exec();
}
