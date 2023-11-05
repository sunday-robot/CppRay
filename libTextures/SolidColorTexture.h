#pragma once

#include "Color.h"
#include "Texture.h"

class SolidColorTexture : public Texture {
	const Color _value;
public:
	SolidColorTexture(const Color& c) : _value(c) {}

	SolidColorTexture(double red, double green, double blue) : SolidColorTexture(Color(red, green, blue)) { }

	virtual Color value(double u, double v, const Vec3& p) const { return _value; }

	/*
	public override string ToString()
	{
		return $"SolidColor({_value})";
	}
	*/
};
