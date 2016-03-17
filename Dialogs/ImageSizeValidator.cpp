#include "ImageSizeValidator.hpp"

ImageSizeValidator::ImageSizeValidator(int minimum, int maximum, QObject * parent)
	: QIntValidator(minimum, maximum, parent)
{

}

QValidator::State ImageSizeValidator::validate(QString &input, int &pos) const
{
	QIntValidator::State result(QIntValidator::validate(input, pos));

	if (result == QValidator::Intermediate)
		result = QValidator::Invalid;

	return result;
}
