#pragma once

#include <string>
#include "Color.h"

void saveBmp(const std::string &filePath, const Color *data, int width, int height);
