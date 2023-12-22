#pragma once
#include "Ray.h"
#include "Color.h"

struct ScatterResult {
	Ray ray;
	Color color;
};
