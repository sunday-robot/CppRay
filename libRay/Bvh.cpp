#include "Bvh.h"

bool Bvh::_debugMode = false;
const HitRecord Bvh::_debugModeHitRecord{
	Vec3::o,
	Vec3::o,
	(const Material*)0,
	0.0,
	0.0,
	0.0,
	false
};
