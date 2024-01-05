#include "ImageTexture.h"

#include <algorithm>
#include "loadBmp.h"

ImageTexture::Image ImageTexture::loadBmpAsImage(std::string filePath) {
	unsigned char* data;
	int width;
	int height;
	loadBmp(filePath, &data, &width, &height);
	return Image{ width, height, data };
}

Color ImageTexture::value(double u, double v, const Vec3& p) const {
	auto d = _data.get();

	// If we have no texture data, then return solid cyan as a debugging aid.
	if (d == 0)
		return Color::cyan;

	// Clamp input texture coordinates to [0,1] x [1,0]
	u = std::clamp(u, 0.0, 1.0);
	v = 1 - std::clamp(v, 0.0, 1.0);  // Flip V to image coordinates

	auto x = std::min((int)(u * _width), _width - 1);
	auto y = std::min((int)(v * _height), _height - 1);

	const auto colorScale = 1.0 / 255;
	auto pixelIndex = (y * _width + x) * 3;

	return Color(colorScale * d[pixelIndex + 2], colorScale * d[pixelIndex + 1], colorScale * d[pixelIndex]);
}
