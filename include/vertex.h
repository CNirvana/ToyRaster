#pragma once

#include "vec2.h"
#include "vec3.h"
#include "color.h"

struct Vertex
{
	Vec3 position {0.0f, 0.0f, 0.0f};
	Vec2 uv {0.0f, 0.0f};
	Vec3 normal {0.0f, 1.0f, 0.0f};
	Color color {1.0f, 1.0f, 1.0f, 1.0f};
};
