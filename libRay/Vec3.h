#pragma once

#include <math.h>

class Vec3 {
	double _x;
	double _y;
	double _z;
	bool _squaredLengthValid;
	double _squaredLength;
	bool _lengthValid;
	double _length;

	static double calcSquaredLength(double x, double y, double z) {
		return x * x + y * y + z * z;
	}

public:
	// 原点
	static const Vec3 o;

	Vec3(const Vec3& a) : Vec3(a._x, a._y, a._z) {}
#pragma warning(push)
#pragma warning(disable : 26495)
	inline Vec3() {}
	inline Vec3(double x, double y, double z)
		: _x(x), _y(y), _z(z), _squaredLengthValid(false), _lengthValid(false) {}
#pragma warning(pop)
	inline double x() const { return _x; }
	inline double y() const { return _y; }
	inline double z() const { return _z; }

	// 長さの二乗
	inline double squaredLength() {
		if (!_squaredLengthValid) {
			_squaredLength = calcSquaredLength(_x, _y, _z);
			_squaredLengthValid = true;
		}
		return _squaredLength;
	}

	inline double length() {
		if (!_lengthValid) {
			_length = sqrt(squaredLength());
			_lengthValid = true;
		}
		return _length;
	}
	Vec3 unit() { return *this / length(); }	// 長さを1にしたベクトル
	inline Vec3 operator -() const { return Vec3(-_x, -_y, -_z); }
	inline Vec3 operator +(const Vec3& a) const { return Vec3(_x + a._x, _y + a._y, _z + a._z); }
	inline Vec3 operator -(const Vec3& a) const { return *this + (-a); }
	inline Vec3 operator *(double a) const { return Vec3(_x * a, _y * a, _z * a); }
	inline Vec3 operator /(double a) const { return Vec3(_x / a, _y / a, _z / a); }
	inline Vec3 operator =(const Vec3& a) {
		_x = a._x;
		_y = a._y;
		_z = a._z;
		_squaredLengthValid = a._squaredLengthValid;
		if (_squaredLengthValid) {
			_squaredLength = a._squaredLength;
		}
		_lengthValid = a._lengthValid;
		if (_lengthValid) {
			_length = a._length;
		}
		return *this;
	}
	inline Vec3 operator +=(const Vec3& a) {
		_x += a._x;
		_y += a._y;
		_z += a._z;
		_squaredLengthValid = false;
		_lengthValid = false;
		return *this;
	}

	// 内積
	inline double dot(const Vec3& a) const {
		return
			_x * a._x
			+ _y * a._y
			+ _z * a._z;
	}

	// 外積
	inline Vec3 cross(const Vec3& a) const {
		return Vec3(
			_y * a._z - _z * a._y,
			_z * a._x - _x * a._z,
			_x * a._y - _y * a._x);
	}

	void print() const;
};

inline Vec3 operator *(double a, const Vec3& b) { return b * a; }
