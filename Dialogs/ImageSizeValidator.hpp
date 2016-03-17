#pragma once

#include <QtWidgets>

class ImageSizeValidator : public QIntValidator
{
Q_OBJECT

public:
	ImageSizeValidator(int, int, QObject *);
	QValidator::State validate(QString &, int &) const;
};
