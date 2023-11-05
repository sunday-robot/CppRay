#pragma once

#include "Color.h"
#include "Vec3.h"

class Texture abstract {
public:
	virtual Color value(double u, double v, const Vec3& p) const = 0;
};
