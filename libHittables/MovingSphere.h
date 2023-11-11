#pragma once
#include "Hittable.h"
#include "Material.h"

// ���������^�����Ă��鋅
// Sphere�Ƃ̈Ⴂ�́A�ȉ��̂Q�_�̂݁B
// (1) MovingShere�ɂ͑��x���v���p�e�B�Ƃ��đ��݂���B
// (2) MovingShere�́Ahit()�ł̋��̒��S���W���v�Z�ŋ��߂�B
// �����炭(2)�ɂ��hit()�̑��x�ቺ�͂قƂ�ǖ����ł�����x�Ǝv����̂ŁA
// Shere�͔p�~���Ă��悢�����B
class MovingSphere : public Hittable {
	// t = 0�̎��̒��S�̈ʒu
	const Vec3 _centerT0;

	// ���a
	const double _radius;

	// �f��
	const Material* const _material;

	// ���x
	const Vec3 _velocity;

public:
	MovingSphere(Vec3 centerT0, double radius, const Material* material, Vec3 velocity)
		: _centerT0(centerT0),
		_radius(radius),
		_material(material),
		_velocity(velocity) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const;
	Aabb boundingBox(double exposureTime) const;

	//public override string ToString()
	//{
	//	return $"MovigSphere(c:{_center}, r:{_radius}, m:{_material}, v:{_velocity})";
	//}
};
