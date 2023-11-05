#pragma once

#include <vector>
#include "Bvh.h"
#include "Hittable.h"

Bvh* createBvhTree(std::vector<Hittable*> objects, double exposureTime);
