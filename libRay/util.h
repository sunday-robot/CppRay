#pragma once

#include "Color.h"
#include "Vec3.h"

Vec3 randomInUnitDisk();
Vec3 randomInUnitSphere();
double getRandomDouble();
double getRandomDouble(double min, double max);
unsigned int getRandomInt();
int getRandomInt(int min, int max);

// HSVのS(彩度)、V(明度)が指定されたもので、H(色相)がランダムな色を返す。
Color randomHueColor(double s, double v);
