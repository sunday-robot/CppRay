#pragma once

#include <random>
#define _USE_MATH_DEFINES	// M_PI���g�p����ɂ͂��̒�`���K�v�Ƃ̂���
#include <math.h>
#include "Ray.h"
#include "Vec3.h"
#include "util.h"

class Camera {
	const Vec3 lowerLeftCorner;
	const Vec3 horizontal;
	const Vec3 vertical;

	// �J�����̈ʒu
	const Vec3 origin;

	// �J������X������(�P�ʃx�N�g��)
	const Vec3 u;

	// �J������Y������(�P�ʃx�N�g��)
	const Vec3 v;

	// �����Y�̃T�C�Y(�{�P�����߂���̂ŁA�������قǃ{�P�Ȃ��B0�Ȃ�S���{�P�Ȃ��B)
	const double lensRadius;

	const double _exposureTime;

public:
	Camera(const Vec3& lowerLeftCorner,
		const Vec3& horizontal,
		const Vec3& vertical,
		const Vec3& origin,
		const Vec3& u,	// �J������X������(�P�ʃx�N�g���ł��邱��)
		const Vec3& v,	// �J������Y������(�P�ʃx�N�g���ł��邱��)
		double lensRadious,
		double exposureTime)	// �I������
		: lowerLeftCorner(lowerLeftCorner),
		vertical(vertical), horizontal(horizontal),
		origin(origin),
		u(u), v(v),
		lensRadius(lensRadious),
		_exposureTime(exposureTime) {}

	Ray ray(
		double s,	// �������̈ʒu(0�`1)
		double t) const;	// �c�����̈ʒu(0�`1)

	double exposureTime() const { return _exposureTime; }

	static Camera createCamera(
		Vec3 lookFrom,			// ���_
		Vec3 lookAt,			// �����_(�����̕��������߂邽�߂����̂��̂ŁA�s���g�������ꏊ�ł͂Ȃ��B�s���g�ʒu�́AfocusDist�Ŏw�肷��B)
		Vec3 vup,				// ������������x�N�g��(���_�A�����_�̃x�N�g���Ɠ��������łȂ���΂悢�B�������Ă���K�v���Ȃ����A�������K���ł悢)
		double verticalFov,		// �c�����̎���(�p�x[��]]
		double aspect,			// �c����(��/����)
		double aperture,		// �i��(�{�P��̂����߂���́B0�Ȃ�S���{�P�Ȃ��B)
		double exposureTime);	// �I������
};
