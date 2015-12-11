#include <assert.h>

#include "Editor.hpp"

Editor::Editor()
{
	previewWindow = new PreviewWindow(this);
	previewWindow->setInitialPosition(QPoint(1920, 0));

	createSideBar();

	assert(sideBar);
	assert(previewWindow);
	createImageArea(sideBar, previewWindow);

	splitter = new QSplitter();
	splitter->addWidget(sideBar);
	splitter->addWidget(imageArea);
	setCentralWidget(splitter);

	createFileMenu();
	createColorPaletteMenu();
	createViewMenu();
	createWindowMenu();
}

Editor::~Editor()
{
	assert(sideBar);
	delete sideBar;

	assert(imageArea);
	delete imageArea;

	assert(previewWindow);
	delete previewWindow;

	assert(splitter);
	delete splitter;
}

void Editor::createSideBar()
{
	sideBar = new SideBar();

	ColorPaletteRollOut *colorPaletteRollOut = sideBar->getColorPaletteRollOut();
	assert(colorPaletteRollOut);
	QColorDialog *colorDialog = colorPaletteRollOut->getColorDialog();
	assert(colorDialog);
	connect(colorDialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(updateCurrentColorPaletteColor(QColor)));

	ColorPaletteSwatchArea *colorPaletteSwatchArea = colorPaletteRollOut->getColorPaletteSwatchArea();
	assert(colorPaletteSwatchArea);
	connect(colorPaletteSwatchArea, SIGNAL(onDoubleClick()), colorPaletteRollOut, SLOT(editColor()));
}

void Editor::createImageArea(SideBar *sideBar, PreviewWindow *previewWindow)
{
	ColorPaletteRollOut *colorPaletteRollOut = sideBar->getColorPaletteRollOut();
	assert(colorPaletteRollOut);
	ColorPaletteSwatchArea *colorPaletteSwatchArea = colorPaletteRollOut->getColorPaletteSwatchArea();
	assert(colorPaletteSwatchArea);

	DrawingToolsRollOut *drawingToolsRollOut = sideBar->getDrawingToolsRollOut();
	assert(drawingToolsRollOut);
	DrawingToolsModel *drawingToolsModel = drawingToolsRollOut->getDrawingToolsModel();
	assert(drawingToolsModel);

	assert(previewWindow);
	imageArea = new ImageArea(colorPaletteSwatchArea, drawingToolsModel, previewWindow);
	connect(imageArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(repaintColorPaletteSwatchArea()));
	connect(imageArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), previewWindow, SLOT(updatePreview()));
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
	importImageAction->setShortcut(Qt::CTRL + Qt::Key_I);
	connect(importImageAction, SIGNAL(triggered()), imageArea, SLOT(importImage()));
	fileMenu->addAction(importImageAction);

	exportImageAction = new QAction(QIcon("E:/Qt Projects/PixelPro/images/save.png"), tr("&Export Image..."), this);
	exportImageAction->setShortcut(Qt::CTRL + Qt::Key_E);
	connect(exportImageAction, SIGNAL(triggered()), imageArea, SLOT(exportImage()));
	fileMenu->addAction(exportImageAction);

	fileMenu->addSeparator();

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
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

void Editor::createWindowMenu()
{
	assert(menuBar());
	assert(imageArea);

	windowMenu = menuBar()->addMenu(tr("&Window"));

	closeWindowAction = new QAction(tr("&Close Window"), this);
	closeWindowAction->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_C);
	connect(closeWindowAction, SIGNAL(triggered()), imageArea, SLOT(closeActiveSubWindow()));
	windowMenu->addAction(closeWindowAction);
}

void Editor::keyPressEvent(QKeyEvent *event)
{
	assert(event);

	assert(sideBar);
	DrawingToolsRollOut *drawingToolsRollOut = sideBar->getDrawingToolsRollOut();
	assert(drawingToolsRollOut);

	if (event->key() == Qt::Key_Control)
	{
		QPushButton *colorPickerButton = drawingToolsRollOut->getColorPickerButton();
		assert(colorPickerButton);
		colorPickerButton->click();
	}
}

void Editor::keyReleaseEvent(QKeyEvent *event)
{
	assert(event);

	assert(sideBar);
	DrawingToolsRollOut *drawingToolsRollOut = sideBar->getDrawingToolsRollOut();
	assert(drawingToolsRollOut);

	if (event->key() == Qt::Key_Q)
	{
		QPushButton *selectButton = drawingToolsRollOut->getSelectButton();
		assert(selectButton);
		selectButton->click();
	}
	else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Control)
	{
		QPushButton *brushButton = drawingToolsRollOut->getBrushButton();
		assert(brushButton);
		brushButton->click();
	}
	else if (event->key() == Qt::Key_E)
	{
		QPushButton *colorPickerButton = drawingToolsRollOut->getColorPickerButton();
		assert(colorPickerButton);
		colorPickerButton->click();
	}
	else if (event->key() == Qt::Key_R)
	{
		QPushButton *rectangleButton = drawingToolsRollOut->getRectangleButton();
		assert(rectangleButton);
		rectangleButton->click();
	}
	else if (event->key() == Qt::Key_T)
	{
		QPushButton *circleButton = drawingToolsRollOut->getCircleButton();
		assert(circleButton);
		circleButton->click();
	}

	ImageWindow *currentImageWindow = ImageArea::getCurrentImageWindow();

	if (currentImageWindow)
	{
		if (event->key() == Qt::Key_0)
		{
			currentImageWindow->setSelectedColorIndex(9);
			repaintColorPaletteSwatchArea();
		}
		else if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9)
		{
			currentImageWindow->setSelectedColorIndex(event->key() - Qt::Key_1);
			repaintColorPaletteSwatchArea();
		}
	}
}

void Editor::closeEvent(QCloseEvent *event)
{
	if (QMessageBox::question(nullptr, "Close the editor?", "Are you sure want to close the editor?") == QMessageBox::No)
		event->ignore();
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
	ImageWindow *imageWindow = imageArea->getCurrentImageWindow();
	assert(imageWindow);

	imageWindow->setSelectedColor(color);
	imageWindow->repaint();

	repaintColorPaletteSwatchArea();

	assert(previewWindow);
	previewWindow->repaint();
}

PreviewWindow *Editor::getPreviewWindow()
{
	assert(previewWindow);
	return previewWindow;
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	Editor editor;
	editor.showMaximized();

	return application.exec();
}
