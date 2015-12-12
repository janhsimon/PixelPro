#include <assert.h>

#include "ImageWindow.hpp"

ImageWindow::ImageWindow(SideBar *sideBar, PreviewWindow *previewWindow)
{
	assert(sideBar);
	this->sideBar = sideBar;

	assert(previewWindow);
	this->previewWindow = previewWindow;

	scrollArea = new QScrollArea();
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setBackgroundRole(QPalette::Dark);

	image = new Image(64, 64, sideBar, previewWindow, scrollArea);
	assert(image);
	scrollArea->setWidget(image);

	imageScrollBarFilter = new ImageScrollBarFilter(image);
	scrollArea->viewport()->installEventFilter(imageScrollBarFilter);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(scrollArea);
	setLayout(layout);
}

ImageWindow::~ImageWindow()
{
	if (image)
		delete image;

	if (imageScrollBarFilter)
		delete imageScrollBarFilter;
}

Image *ImageWindow::getImage()
{
	assert(image);
	return image;
}

void ImageWindow::closeEvent(QCloseEvent *event)
{
	if (QMessageBox::question(nullptr, "Save before closing?", "Are you sure want to close without saving?") == QMessageBox::No)
		event->ignore();
}

void ImageWindow::updateTitle()
{
	assert(image);
	QString title = windowTitle().left(windowTitle().lastIndexOf("@") + 1);
	title.append(QString::number(image->getZoomFactor()) + "x");
	setWindowTitle(title);
}
