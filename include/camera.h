#pragma once

#include "vec3.h"
#include "color.h"

struct Camera
{
	Vec3 position { 0.f, 0.f, 10.f };
	Vec3 target { 0.f, 0.f, 0.f };
	Vec3 up { 0.f, 1.f, 0.f };
	Color backgroundColor { 0.f, 0.f, 0.f, 0.f };

	float fov = 60.f;
	float near = 1.f;
	float far = 100.f;
};