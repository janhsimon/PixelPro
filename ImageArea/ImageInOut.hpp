#pragma once

#include "Image.hpp"

class ImageInOut
{
	public:
		static bool importFromImageFile(Image *image, const QString &fileName);
		static void exportToImageFile(Image *image, const QString &fileName);
		static void importColorPalette(Image *image, const QString &fileName);
};
