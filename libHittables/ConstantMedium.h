#pragma once
#include <Hittable.h>
#include <Texture.h>
#include <Isotropic.h>
#include <SolidColorTexture.h>

// ���̂悤�ȕ���
// ����Hittable�Ɣ�ׂ�Ɠ���Ȃ��̂ŁA���ڌ`�������킷���̂ł͂Ȃ��A
// �����o�ϐ��Ƃ��Č`���\��Hittable��ێ�����B
// 
class ConstantMedium : public Hittable {
	static const Vec3 _dummyNormal; // (0, 0, 0);
	const Hittable* const _boundary;
	const Material* const _phaseFunction;
	const double _negInvDensity;

public:
	ConstantMedium(const Hittable* b, double d, const Texture* a)
		: _boundary(b), _negInvDensity(-1 / d), _phaseFunction(new Isotropic(a)) {}

	ConstantMedium(const Hittable* b, double d, Color c)
		: ConstantMedium(b, d, new SolidColorTexture(c)) { }

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const;

	Aabb boundingBox(double exposureTime) const {
		return _boundary->boundingBox(exposureTime);
	}
};
