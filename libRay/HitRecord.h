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
};
