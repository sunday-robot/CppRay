#pragma once

#include "Aabb.h"
#include "HitRecord.h"
#include "Ray.h"

class Hittable abstract {
public:
	virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord *rec) const = 0;

	// レンダリング前のBVHツリー構築時に一度呼ばれるだけなので、速度についてあまり考慮する必要はない。
	virtual Aabb boundingBox(double exposureTime) const = 0;
};
