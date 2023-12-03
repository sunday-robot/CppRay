#include "HittableList.h"

bool HittableList::hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
	auto somethingHit = false;
	auto closestSoFar = tMax;
	HitRecord tmpRec;
	for (auto o : _objects) {
		if (o->hit(ray, tMin, closestSoFar, &tmpRec)) {
			somethingHit = true;
			closestSoFar = tmpRec.t;
			*rec = tmpRec;
		}
	}
	return somethingHit;
}

Aabb HittableList::boundingBox(double exposureTime) const {
	// �I�u�W�F�N�g�������Ȃ��ꍇ�͑傫��0��AABB��Ԃ��B
	if (_objects.size() == 0) {
		return Aabb(Vec3::o, Vec3::o);
	}

	Aabb aabb(_objects[0]->boundingBox(exposureTime));
	for (auto i = 1; i < _objects.size(); i++) {
		aabb = Aabb::surroundingAabb(aabb, _objects[i]->boundingBox(exposureTime));
	}
	return aabb;
}
