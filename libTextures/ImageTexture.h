#pragma once

#include <memory>
#include <string>
#include "Texture.h"

class ImageTexture : public Texture {
	const int _width;
	const int _height;
	std::shared_ptr<const unsigned char> _data;

	struct Image {
		int width;
		int height;
		unsigned char* data;
	};

	static Image loadBmpAsImage(std::string filePath);
	ImageTexture(Image image) : _width(image.width), _height(image.height), _data(image.data) {}

public:
	ImageTexture(std::string filePath) : ImageTexture(loadBmpAsImage(filePath)) {}
	Color value(double u, double v, const Vec3& p) const;
};
