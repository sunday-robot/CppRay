#pragma once
#include <vector>
#include "Camera.h"
#include "Color.h"
#include "Hittable.h"

class Scene {
	const std::vector<const Hittable*> _hittables;
	const Camera _camera;
	const Color _backgroundColor;
public:
	Scene(const std::vector<const Hittable*>& objects, const Camera& camera, const Color& backgroundColor)
		: _hittables(objects), _camera(camera), _backgroundColor(backgroundColor) {}
	const std::vector<const Hittable*>& hittables() const { return _hittables; }
	const Camera& camera() const { return _camera; }
	const Color& backgroundColor() const { return _backgroundColor; }
};
