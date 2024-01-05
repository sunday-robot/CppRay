#include "createBvhTree.h"

#include <functional>
#include <algorithm>
#include "BvhLeaf.h"
#include "BvhNode.h"

static std::function<bool(std::shared_ptr<const Hittable>, std::shared_ptr<const Hittable>)> getComparerRandomly(double exposureTime) {
	switch (getRandomInt() % 3) {
	case 0:
		return [exposureTime](std::shared_ptr<const Hittable> a, std::shared_ptr<const Hittable> b) {
			auto aa = a->boundingBox(exposureTime);
			auto bb = b->boundingBox(exposureTime);
			return aa.min().x() < bb.min().x();
			};
	case 1:
		return [exposureTime](std::shared_ptr<const Hittable> a, std::shared_ptr<const Hittable> b) {
			auto aa = a->boundingBox(exposureTime);
			auto bb = b->boundingBox(exposureTime);
			return aa.min().y() < bb.min().y();
			};
	default:
		return [exposureTime](std::shared_ptr<const Hittable> a, std::shared_ptr<const Hittable> b) {
			auto aa = a->boundingBox(exposureTime);
			auto bb = b->boundingBox(exposureTime);
			return aa.min().z() < bb.min().z();
			};
	}
}

static std::shared_ptr<Bvh> create(std::vector<std::shared_ptr<const Hittable>>* objects, double exposureTime, int start, int end) {
	if (end - start == 1) {
		auto o = (*objects)[start];
		return std::shared_ptr<Bvh>(new BvhLeaf(o.get()->boundingBox(exposureTime), o));
	} else {
		auto comparator = getComparerRandomly(exposureTime);
		std::sort(objects->begin() + start, objects->begin() + end, comparator);
		auto mid = (start + end) / 2;
		std::shared_ptr<Bvh> left = create(objects, exposureTime, start, mid);
		std::shared_ptr<Bvh> right = create(objects, exposureTime, mid, end);
		auto aabb = Aabb::surroundingAabb(left->boundingBox(exposureTime), right->boundingBox(exposureTime));
		return std::shared_ptr<Bvh>(new BvhNode(aabb, left, right));
	}
}

std::shared_ptr<Bvh> createBvhTree(const std::vector<std::shared_ptr<const Hittable>>& objects, double exposureTime) {
	if (objects.size() == 0) {
		return std::shared_ptr<Bvh>(new BvhLeaf(Aabb(Vec3(0, 0, 0), Vec3(0, 0, 0)), 0));
	}
	std::vector<std::shared_ptr<const Hittable>> tmp = objects;	// std::vectorのコピーを作成する(浅いコピーなので、Hittableのコピーは作られない。)
	return create(&tmp, exposureTime, 0, (int)objects.size());
}
