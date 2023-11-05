#pragma once

#include "Hittable.h"
#include "DebugMaterial.h"

// Bounding Volume Hierarchy
class Bvh abstract : public Hittable {
	// デバッグモードかどうか。デバッグモードの場合、Bvhが内包するオブジェクトは描画せず、Bvhそのものを描画する。
	static  bool _debugMode;// = false;

protected:
	static bool isDebugMode() {
		return _debugMode;
	}
	static bool setDebugMode(bool value) { _debugMode = value; }

	const Aabb _aabb;
	const DebugMaterial _debugMaterial;

public:
	Bvh(const Aabb& aabb) : _aabb(aabb) {}

	Aabb boundingBox(double exposureTime) const { return _aabb; }

	virtual bool isLeaf() const = 0;

	// public abstract void Print(string indent = "");
};
