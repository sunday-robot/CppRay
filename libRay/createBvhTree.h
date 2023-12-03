#pragma once

#include <vector>
#include "Bvh.h"
#include "Hittable.h"

Bvh* createBvhTree(std::vector<const Hittable*> objects, double exposureTime);
