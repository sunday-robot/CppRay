#pragma once

#include <memory>
#include "Color.h"
#include "Vec3.h"

Vec3 randomInUnitDisk();
Vec3 randomInUnitSphere();

/// <returns>0.0�ȏ�A1.0�����̗���</returns>
double getRandomDouble();

/// <returns>min�ȏ�Amax�����̗���</returns>
double getRandomDouble(double min, double max);

unsigned int getRandomInt();

/// <returns>min�ȏ�Amax�����̗���</returns>
int getRandomInt(int min, int max);

// HSV��S(�ʓx)�AV(���x)���w�肳�ꂽ���̂ŁAH(�F��)�������_���ȐF��Ԃ��B
Color randomHueColor(double s, double v);

template<class T> std::shared_ptr<const T> sp(const T* p) {
	return std::shared_ptr<const T>(p);
}
