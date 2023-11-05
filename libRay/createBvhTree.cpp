#include "createBvhTree.h"

#include <functional>
#include <algorithm>
#include "BvhLeaf.h"
#include "BvhNode.h"
#include "util.h"

static std::tuple<Aabb, Aabb> boxCompareSub(const Hittable& a, const Hittable& b)
{
	return std::tuple<Aabb, Aabb>{ a.boundingBox(0), b.boundingBox(0)};
}

static std::function<bool(const Hittable&, const Hittable&)> getComparerRandomly()
{
	switch (getRandomInt() % 3) {
	case 0:
		return [](const Hittable& a, const Hittable& b) {
			auto r = boxCompareSub(a, b);
			return std::get<0>(r).min().x < std::get<1>(r).min().x;
			};
	case 1:
		return [](const Hittable& a, const Hittable& b) {
			auto r = boxCompareSub(a, b);
			return std::get<0>(r).min().y < std::get<1>(r).min().y;
			};
	default:
		return [](const Hittable& a, const Hittable& b) {
			auto r = boxCompareSub(a, b);
			return std::get<0>(r).min().z < std::get<1>(r).min().z;
			};
	}
}

static Bvh* create(std::vector<Hittable*> objects, double exposureTime, int start, int end)
{
	auto object_span = end - start;

	if (object_span == 1)
	{
		auto o = objects[start];
		return new BvhLeaf(o->boundingBox(exposureTime), o);
	} else
	{
		auto comparator = getComparerRandomly();
		//std::sort(&objects[start], &objects[end], comparator);
		auto mid = (start + end) / 2;
		auto left = create(objects, exposureTime, start, mid);
		auto right = create(objects, exposureTime, mid, end);
		auto aabb = Aabb::surroundingAabb(left->boundingBox(exposureTime), right->boundingBox(exposureTime));
		return new BvhNode(aabb, left, right);
	}
}

Bvh* createBvhTree(std::vector<Hittable*> objects, double exposureTime) {
	if (objects.size() == 0) {
		return new BvhLeaf(Aabb(Vec3(0, 0, 0), Vec3(0, 0, 0)), 0);
	}
	return create(objects, exposureTime, 0, (int)objects.size());
}
