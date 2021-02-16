#pragma once
#include <sstream>
#include "Scene/Config.h"

bool readvals(std::stringstream& s, const int numvals, float* values);
Config readfile(const char* filename);