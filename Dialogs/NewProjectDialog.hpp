#pragma once

#include <QtWidgets>

#include "../ImageArea/ImageArea.hpp"

class NewProjectDialog : public QDialog
{
	Q_OBJECT

public:
	NewProjectDialog(ImageArea *imageArea, QWidget *parent = 0);

private:
	QLineEdit *widthTextEdit, *heightTextEdit;
	ImageArea *imageArea;

private slots:
	void createNewProject();
};
