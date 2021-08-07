#pragma once

struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	Vec4() : x(0), y(0), z(0), w(0) {}
	Vec4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) {}

	friend Vec4 operator * (const Vec4& v, float scalar)
	{
		return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar };
	}

	friend Vec4& operator *= (Vec4& v, float scalar)
	{
		v.x *= scalar;
		v.y *= scalar;
		v.z *= scalar;
		v.w *= scalar;
		return v;
	}

	friend Vec4 operator + (const Vec4& left, const Vec4& right)
	{
		return { left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
	}
};
