#pragma once

#include <QtWidgets>

class ImageColorPaletteModel : public QObject
{
	Q_OBJECT

public:
	const static unsigned short MAX_COLORS = 256;

	ImageColorPaletteModel();

	QColor getColor(unsigned short i);
	QColor getSelectedColor();
	void setSelectedColor(const QColor &color);
	unsigned short getSelectedColorIndex();
	void setSelectedColorIndex(unsigned short index);
	unsigned short getColorIndexClosestToColor(const QColor &color);
	void import(const QString &fileName);

private:
	QColor colors[MAX_COLORS];
	unsigned short selectedColor;

	QColor getColorFromByteArray(const QByteArray &bytes, unsigned short colorIndex);
	void loadDefaultColorPalette();
};
