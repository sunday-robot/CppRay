#pragma once

#include "Color.h"
#include "Hittable.h"
#include "Camera.h"

Color* render(Hittable* world, Color* background, const Camera& camera, int width, int height, int maxDepth, int sampleCount);
