#include "createBvhTree.h"

#include <functional>
#include <algorithm>
#include "BvhLeaf.h"
#include "BvhNode.h"

static double compareExposureTime;

static bool compareX(const Hittable* a, const Hittable* b) {
	auto aa = a->boundingBox(compareExposureTime);
	auto bb = b->boundingBox(compareExposureTime);
	return aa.min().x < bb.min().x;
}

static bool compareY(const Hittable* a, const Hittable* b) {
	auto aa = a->boundingBox(compareExposureTime);
	auto bb = b->boundingBox(compareExposureTime);
	return aa.min().y < bb.min().y;
}

static bool compareZ(const Hittable* a, const Hittable* b) {
	auto aa = a->boundingBox(compareExposureTime);
	auto bb = b->boundingBox(compareExposureTime);
	return aa.min().z < bb.min().z;
}

static std::function<bool(const Hittable*, const Hittable*)> getComparerRandomly() {
	switch (getRandomInt() % 3) {
	case 0: return compareX;
	case 1: return compareY;
	default:return compareZ;
	}
}

static Bvh* create(std::vector<const Hittable*> objects, double exposureTime, int start, int end) {
	if (end - start == 1) {
		auto o = objects[start];
		return new BvhLeaf(o->boundingBox(exposureTime), o);
	} else {
		auto comparator = getComparerRandomly();
		compareExposureTime = exposureTime;
		std::sort(objects.begin() + start, objects.begin() + end, comparator);
		auto mid = (start + end) / 2;
		auto left = create(objects, exposureTime, start, mid);
		auto right = create(objects, exposureTime, mid, end);
		auto aabb = Aabb::surroundingAabb(left->boundingBox(exposureTime), right->boundingBox(exposureTime));
		return new BvhNode(aabb, left, right);
	}
}

Bvh* createBvhTree(std::vector<const Hittable*> objects, double exposureTime) {
	if (objects.size() == 0) {
		return new BvhLeaf(Aabb(Vec3(0, 0, 0), Vec3(0, 0, 0)), 0);
	}
	return create(objects, exposureTime, 0, (int)objects.size());
}
