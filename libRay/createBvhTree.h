#pragma once

#include <memory>
#include <vector>
#include "Bvh.h"
#include "Hittable.h"

std::shared_ptr<Bvh> createBvhTree(const std::vector<std::shared_ptr<const Hittable>> &objects, double exposureTime);
