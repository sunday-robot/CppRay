#pragma once

#include "Color.h"
#include "Vec3.h"

Vec3 randomInUnitDisk();
Vec3 randomInUnitSphere();
double getRandomDouble();
double getRandomDouble(double min, double max);
unsigned int getRandomInt();
int getRandomInt(int min, int max);

// HSV��S(�ʓx)�AV(���x)���w�肳�ꂽ���̂ŁAH(�F��)�������_���ȐF��Ԃ��B
Color randomHueColor(double s, double v);
