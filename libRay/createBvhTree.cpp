#include "createBvhTree.h"

#include <functional>
#include <algorithm>
#include "BvhLeaf.h"
#include "BvhNode.h"

static std::function<bool(const Hittable*, const Hittable*)> getComparerRandomly(double exposureTime) {
	switch (getRandomInt() % 3) {
	case 0:
		return [exposureTime](const Hittable* a, const Hittable* b) {
			auto aa = a->boundingBox(exposureTime);
			auto bb = b->boundingBox(exposureTime);
			return aa.min().x() < bb.min().x();
			};
	case 1:
		return [exposureTime](const Hittable* a, const Hittable* b) {
			auto aa = a->boundingBox(exposureTime);
			auto bb = b->boundingBox(exposureTime);
			return aa.min().y() < bb.min().y();
			};
	default:
		return [exposureTime](const Hittable* a, const Hittable* b) {
			auto aa = a->boundingBox(exposureTime);
			auto bb = b->boundingBox(exposureTime);
			return aa.min().z() < bb.min().z();
			};
	}
}

static Bvh* create(std::vector<const Hittable*> *objects, double exposureTime, int start, int end) {
	if (end - start == 1) {
		auto o = (*objects)[start];
		return new BvhLeaf(o->boundingBox(exposureTime), o);
	} else {
		auto comparator = getComparerRandomly(exposureTime);
		std::sort(objects->begin() + start, objects->begin() + end, comparator);
		auto mid = (start + end) / 2;
		auto left = create(objects, exposureTime, start, mid);
		auto right = create(objects, exposureTime, mid, end);
		auto aabb = Aabb::surroundingAabb(left->boundingBox(exposureTime), right->boundingBox(exposureTime));
		return new BvhNode(aabb, left, right);
	}
}

Bvh* createBvhTree(const std::vector<const Hittable*> &objects, double exposureTime) {
	if (objects.size() == 0) {
		return new BvhLeaf(Aabb(Vec3(0, 0, 0), Vec3(0, 0, 0)), 0);
	}
	std::vector<const Hittable*> tmp = objects;	// std::vectorのコピーを作成する(浅いコピーなので、Hittableのコピーは作られない。)
	return create(&tmp, exposureTime, 0, (int)objects.size());
}
