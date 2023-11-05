#include "ImageTexture.h"
#include "loadBmp.h"

ImageTexture::Image ImageTexture::loadBmpAsImage(std::string filePath) {
	unsigned char* data;
	int width;
	int height;
	loadBmp(filePath, &data, &width, &height);
	return Image{ width, height,data };
}

static inline double clamp01(double value) {
	if (value < 0)
		return 0;
	if (value > 1)
		return 1;
	return value;
}

Color ImageTexture::value(double u, double v, const Vec3& p) const {
	// If we have no texture data, then return solid cyan as a debugging aid.
	if (_data == 0)
		return Color::cyan;

	// Clamp input texture coordinates to [0,1] x [1,0]
	u = clamp01(u);
	v = 1 - clamp01(v);  // Flip V to image coordinates

	auto i = (int)(u * _width);
	auto j = (int)(v * _height);

	// Clamp integer mapping, since actual coordinates should be less than 1.0
	if (i >= _width) i = _width - 1;
	if (j >= _height) j = _height - 1;

	auto colorScale = 1.0 / 255;
	auto pixelIndex = (j * _width + i) * 3;

	return Color(colorScale * _data[pixelIndex + 2], colorScale * _data[pixelIndex + 1], colorScale * _data[pixelIndex]);
}

