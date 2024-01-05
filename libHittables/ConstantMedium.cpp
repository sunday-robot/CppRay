#include "ConstantMedium.h"

#include <cfloat>
#include "util.h"

const Vec3 ConstantMedium::_dummyNormal(0, 0, 0);

bool ConstantMedium::hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
	double t1;
	double t2;
	{
		// ���C�̌�����܂߂Č�_�����邩�`�F�b�N����B
		HitRecord rec1;
		if (!_boundary->hit(ray, -DBL_MAX, DBL_MAX, &rec1))	// DBL_MIN�͍ŏ��l�ł͂Ȃ��A0�����傫�����ŏ��̒l�ł���c
			return false;

		// ���C�̑O���Ɍ�_�����邩�`�F�b�N����
		HitRecord rec2;
		if (!_boundary->hit(ray, rec1.t + 0.0001, DBL_MAX, &rec2))
			return false;

		t1 = std::max(rec1.t, tMin);
		t2 = std::min(rec2.t, tMax);
	}

	if (t1 >= t2)
		return false;

	auto rayLength = ray.direction().length();
	auto distanceInsideBoundary = (t2 - t1) * rayLength;
	auto hitDistance = _negInvDensity * log(getRandomDouble(0, 1));

	if (hitDistance > distanceInsideBoundary)
		return false;

	auto t = t1 + hitDistance / rayLength;

	rec->position = ray.positionAt(t);
	rec->normal = _dummyNormal;
	rec->material = _phaseFunction.get();
	rec->t = t;
	// u,v,frontFace�͎Q�Ƃ���Ȃ��̂ŁA�����ݒ肵�Ȃ��B

	return true;
}
