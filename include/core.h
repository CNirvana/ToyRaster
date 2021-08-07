#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>

#include "SDL.h"

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p) = nullptr; } }

typedef std::int16_t int16;

typedef std::int32_t int32;
typedef std::uint32_t uint32;

typedef std::int64_t int64;