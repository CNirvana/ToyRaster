#pragma once

#include "vec3.h"
#include "quat.h"
#include "mat4.h"

struct Transform
{
	Vec3 position;
	Quat rotation;
	Vec3 scale;

	Transform() : position({ 0.f, 0.f, 0.f }), rotation({ 0.f, 0.f, 0.f, 1.f }), scale({ 1.f, 1.f, 1.f }) { }

	Transform(const Vec3& position, const Quat& rotation, const Vec3& scale)
		: position(position), rotation(rotation), scale(scale) {}

	Mat4 LocalToWorld()
	{
		return Mat4::Scale(scale) * Quat::ToRotationMatrix(rotation) * Mat4::Translate(position);
	}
};