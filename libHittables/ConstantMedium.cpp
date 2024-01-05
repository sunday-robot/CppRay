#include "ConstantMedium.h"

#include <cfloat>
#include "util.h"

const Vec3 ConstantMedium::_dummyNormal(0, 0, 0);

bool ConstantMedium::hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
	double t1;
	double t2;
	{
		// レイの後方も含めて交点があるかチェックする。
		HitRecord rec1;
		if (!_boundary->hit(ray, -DBL_MAX, DBL_MAX, &rec1))	// DBL_MINは最小値ではなく、0よりも大きいが最小の値である…
			return false;

		// レイの前方に交点があるかチェックする
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
	// u,v,frontFaceは参照されないので、何も設定しない。

	return true;
}
