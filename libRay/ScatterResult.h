#pragma once
#include "Ray.h"
#include "Color.h"

struct ScatterResult {
	Ray ray;
	Color color;
//public:
////	ScatterResult(const Ray& ray, const Color& color) : _ray(ray), _color(color) {}
//	Ray ray() const { return _ray; }
//	Color color() const { return _color; }
};
