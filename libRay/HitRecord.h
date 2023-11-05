#pragma once

#include "Vec3.h"

class Material;

// Ray��Hittable�̏Փˏ��
struct HitRecord {
	// �Փ˓_
	Vec3 position;

	// �Փ˓_�̖@��
	Vec3 normal;

	// �Փ˓_�̕\�ʑf��
	const Material* material;

	// ���C����̈ʒu
	double t;

	double u;
	double v;

	// �\�ʂŃq�b�g�����̂��A���ʂŃq�b�g�����̂�(���ܗ������̂܂܎g�����A�t���ɂ��Ďg�����̔���ɕK�v)
	bool frontFace;

#pragma warning(push)
#pragma warning(disable : 26495)
	HitRecord() {};
#pragma warning(pop)

	HitRecord(double t, const Vec3& position, const Vec3& normal, const Material* material, bool frontFace = false, double u = 0, double v = 0) :
		t(t), position(position), normal(normal), material(material), frontFace(frontFace), u(u), v(v) {};
};
