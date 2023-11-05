#pragma once

#include <math.h>

class Vec3 {
	double _squaredLength;

	static double calcSquaredLength(double x, double y, double z) {
		return x * x + y * y + z * z;
	}

public:
	static const Vec3 o;
	double x;
	double y;
	double z;

#pragma warning(push)
#pragma warning(disable : 26495)
	Vec3() {}
#pragma warning(pop)
	Vec3(const Vec3& a) : Vec3(a.x, a.y, a.z) {}
	Vec3(double x, double y, double z)
		: x(x), y(y), z(z), _squaredLength(calcSquaredLength(x, y, z)) {}

	inline double squaredLength() const { return _squaredLength; }
	double length() const { return sqrt(_squaredLength); }
	Vec3 unit() const { return *this / length(); }	// 長さを1にしたベクトル
	inline Vec3 operator -() const { return Vec3(-x, -y, -z); }
	inline Vec3 operator +(const Vec3& a) const { return Vec3(x + a.x, y + a.y, z + a.z); }
	inline Vec3 operator -(const Vec3& a) const { return *this + (-a); }
	inline Vec3 operator *(double a) const { return Vec3(x * a, y * a, z * a); }
	inline Vec3 operator /(double a) const { return Vec3(x / a, y / a, z / a); }
	inline Vec3 operator =(const Vec3& a) {
		x = a.x;
		y = a.y;
		z = a.z;
		_squaredLength = a._squaredLength;
		return *this;
	}

	/// 内積
	inline double dot(const Vec3& a) const {
		return
			x * a.x
			+ y * a.y
			+ z * a.z;
	}

	/// 外積
	inline Vec3 cross(const Vec3& a) const {
		return Vec3(
			y * a.z - z * a.y,
			z * a.x - x * a.z,
			x * a.y - y * a.x);
	}

	//public override string ToString()
	//{
	//	return $"({X:0.000}, {Y:0.000}, {Z:0.000})";
	//}

	bool nearZero() const {
		// Return true if the vector is close to zero in all dimensions.
		auto s = 1e-8;
		return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
	}

};

inline Vec3 operator *(double a, const Vec3& b) { return b * a; }
