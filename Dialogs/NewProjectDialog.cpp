#include <assert.h>

#include "ImageSizeValidator.hpp"
#include "NewProjectDialog.hpp"

NewProjectDialog::NewProjectDialog(ImageArea *imageArea, QWidget *parent) : QDialog(parent)
{
	assert(imageArea);
	this->imageArea = imageArea;

	setWindowTitle(tr("New Project"));

	QGridLayout *layout = new QGridLayout();

	layout->addWidget(new QLabel("Template:"), 1, 1);

	QComboBox *templateComboBox = new QComboBox();
	templateComboBox->addItem("NES 256x240");
	templateComboBox->addItem("VGA 320x200");
	layout->addWidget(templateComboBox, 1, 2, 1, 3);

	layout->addWidget(new QLabel("Image Size:"), 2, 1);

	widthTextEdit = new QLineEdit("256");
	widthTextEdit->setValidator(new ImageSizeValidator(1, 1000, this));
	widthTextEdit->setMaximumWidth(100);
	layout->addWidget(widthTextEdit, 2, 2);

	layout->addWidget(new QLabel("x"), 2, 3);

	heightTextEdit = new QLineEdit("240");
	heightTextEdit->setValidator(new ImageSizeValidator(1, 1000, this));
	heightTextEdit->setMaximumWidth(100);
	layout->addWidget(heightTextEdit, 2, 4);

	QHBoxLayout *bottomStripLayout = new QHBoxLayout();
	bottomStripLayout->addStretch();

	QPushButton *okButton = new QPushButton(tr("&OK"));
	connect(okButton, SIGNAL(clicked()), this, SLOT(createNewProject()));
	bottomStripLayout->addWidget(okButton);

	QPushButton *cancelButton = new QPushButton(tr("&Cancel"));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	bottomStripLayout->addWidget(cancelButton);

	layout->addLayout(bottomStripLayout, 3, 1, 1, 4);

	setLayout(layout);

	setFixedSize(200, 100);
}

void NewProjectDialog::createNewProject()
{
	assert(imageArea);
	assert(widthTextEdit);
	assert(heightTextEdit);
	unsigned int width = widthTextEdit->text().toInt();
	unsigned int height = heightTextEdit->text().toInt();
	imageArea->newProject(width, height);
	close();
}
