#pragma once

#include "Texture.h"
#include "perlinNoise.h"
#include <math.h>

class NoiseTexture : public Texture {
	//const Perlin _noise = Perlin();
	const double _scale;

public:
	NoiseTexture(double scale) : _scale(scale) {        }

	Color value(double u, double v, const Vec3& p) const
	{
		// return color(1,1,1)*0.5*(1 + noise.turb(scale * p));
		// return color(1,1,1)*noise.turb(scale * p);
		return Color(1, 1, 1) * 0.5 * (1 + sin(_scale * p.z + 10 * perlinNoise(p.x, p.y, p.z)));
		// _noise.turb(p)));
	}
};
