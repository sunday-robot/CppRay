#pragma once

#include "Vec3.h"

class Ray {
	// ‹N“_
	Vec3 _origin;

	// •ûŒü
	Vec3 _direction;

	double _time;

public:
#pragma warning(push)
#pragma warning(disable:26495)
	Ray() {};
#pragma warning(pop)
	Ray(const Vec3& origin, const Vec3& direction, double time) :
		_origin(origin), _direction(direction), _time(time) {}

	Ray operator =(const Ray& a) {
		_origin = a._origin;
		_direction = a._direction;
		_time = a._time;
		return *this;
	}

	Vec3 origin() const { return _origin; }
	Vec3 direction() const { return _direction; }
	double time() const { return _time; }
	Vec3 positionAt(double t) const { return _origin + _direction * t; }
};
