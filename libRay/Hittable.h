#pragma once

#include "Aabb.h"
#include "HitRecord.h"
#include "Ray.h"

class Hittable abstract {
public:
	virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord *rec) const = 0;

	// �����_�����O�O��BVH�c���[�\�z���Ɉ�x�Ă΂�邾���Ȃ̂ŁA���x�ɂ��Ă��܂�l������K�v�͂Ȃ��B
	virtual Aabb boundingBox(double exposureTime) const = 0;
};
