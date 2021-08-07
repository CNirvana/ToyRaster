#pragma once

#include <iostream>

#include "maths.h"

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3() : x(0), y(0), z(0) { }
	Vec3(float value) : x(value), y(value), z(value) { }
	Vec3(float x, float y, float z) : x(x), y(y), z(z) { }

	float Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	float LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	void Normalize()
	{
		float len = Length();
		if (len <= EPSILON)
		{
			return;
		}

		x /= len;
		y /= len;
		z /= len;
	}

	static Vec3 Zero()
	{
		return {0.0f, 0.0f, 0.0f};
	}

	static Vec3 Unit()
	{
		return {1.0f, 1.0f, 1.0f};
	}

	static Vec3 Forward()
	{
		return {0.0f, 0.0f, -1.0f};
	}

	static Vec3 Back()
	{
		return {0.0f, 0.0f, 1.0f};
	}

	static Vec3 Left()
	{
		return {-1.0f, 0.0f, 0.0f};
	}

	static Vec3 Right()
	{
		return {1.0f, 0.0f, 0.0f};
	}

	static Vec3 Up()
	{
		return {0.0f, 1.0f, 0.0f};
	}

	static Vec3 Down()
	{
		return {0.0f, -1.0f, 0.0f};
	}

	static float Dot(const Vec3& left, const Vec3& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	static Vec3 Cross(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.z);
	}

	static float Distance(const Vec3& left, const Vec3& right)
	{
		return Math::Sqrt(Math::Square(left.x - right.x) + Math::Square(left.y - right.y) + Math::Square(left.z - right.z));
	}

	static Vec3 Normalize(const Vec3& value)
	{
		float len = value.Length();
		if (Math::Approximately(len, 0))
		{
			return Vec3(0, 0, 0);
		}
		return Vec3(value.x / len, value.y / len, value.z / len);
	}

	friend std::ostream& operator << (std::ostream& os, const Vec3& value)
	{
		os << "x: " << value.x << ", y: " << value.y << ", z: " << value.z;
		return os;
	}

	friend Vec3 operator - (const Vec3& value)
	{
		return Vec3(-value.x, -value.y, -value.z);
	}

	friend Vec3 operator + (const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	friend Vec3& operator += (Vec3& left, const Vec3& right)
	{
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		return left;
	}

	friend Vec3 operator - (const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	friend Vec3& operator -= (Vec3& left, const Vec3& right)
	{
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		return left;
	}

	friend Vec3 operator * (const Vec3& value, float scalar)
	{
		return Vec3(value.x * scalar, value.y * scalar, value.z * scalar);
	}

	friend Vec3 operator * (float scalar, const Vec3& value)
	{
		return Vec3(value.x * scalar, value.y * scalar, value.z * scalar);
	}

	friend Vec3& operator *= (Vec3& value, float scalar)
	{
		value.x *= scalar;
		value.y *= scalar;
		value.z *= scalar;
		return value;
	}

	friend Vec3 operator / (const Vec3& value, float scalar)
	{
		return Vec3(value.x / scalar, value.y / scalar, value.z / scalar);
	}

	friend Vec3& operator /= (Vec3& value, float scalar)
	{
		value.x /= scalar;
		value.y /= scalar;
		value.z /= scalar;
		return value;
	}

	friend float operator | (const Vec3& left, const Vec3& right)
	{
		return Vec3::Dot(left, right);
	}

	friend Vec3 operator ^ (const Vec3& left, const Vec3& right)
	{
		return Vec3::Cross(left, right);
	}
};
