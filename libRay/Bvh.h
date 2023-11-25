#pragma once

#include "Hittable.h"
#include "DebugMaterial.h"

// Bounding Volume Hierarchy
class Bvh abstract : public Hittable {
	// デバッグモードかどうか。デバッグモードの場合、Bvhが内包するオブジェクトは描画せず、Bvhそのものを描画する。
	static  bool _debugMode;
	static const HitRecord _debugModeHitRecord;
	const DebugMaterial _debugMaterial;

protected:
	static bool isDebugMode() {
		return _debugMode;
	}
	void setDebugModeHitRecord(HitRecord *rec) const {
		*rec = _debugModeHitRecord;
		rec->material = &_debugMaterial;
	}
	
	const Aabb _aabb;

public:
	static void setDebugMode(bool value) { _debugMode = value; }

	Bvh(const Aabb& aabb) : _aabb(aabb) {}

	Aabb boundingBox(double exposureTime) const { return _aabb; }

	virtual bool isLeaf() const = 0;

	// public abstract void Print(string indent = "");
};
