#pragma once

#include <iostream>
#include <ostream>

#include "maths.h"

struct Vec2
{
	float x;
	float y;

	Vec2() : x(0), y(0) { }
	Vec2(float x, float y) : x(x), y(y) { }

	float Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	float LengthSquared() const
	{
		return x * x + y * y;
	}

	static float Dot(const Vec2& left, const Vec2& right)
	{
		return left.x * right.x + left.y * right.y;
	}

	static float Distance(const Vec2& left, const Vec2& right)
	{
		return Math::Sqrt(Math::Square(left.x - right.x) + Math::Square(left.y - right.y));
	}

	static Vec2 Normalize(const Vec2& value)
	{
		float len = value.Length();
		if (Math::Approximately(len, 0))
		{
			return Vec2(0, 0);
		}
		return Vec2(value.x / len, value.y / len);
	}

	friend std::ostream& operator << (std::ostream& os, const Vec2& value)
	{
		os << "x: " << value.x << ", y: " << value.y;
		return os;
	}

	friend Vec2 operator - (const Vec2& value)
	{
		return Vec2(-value.x, -value.y);
	}

	friend Vec2 operator + (const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x + right.x, left.y + right.y);
	}

	friend Vec2& operator += (Vec2& left, const Vec2& right)
	{
		left.x += right.x;
		left.y += right.y;
		return left;
	}

	friend Vec2 operator - (const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x - right.x, left.y - right.y);
	}

	friend Vec2& operator -= (Vec2& left, const Vec2& right)
	{
		left.x -= right.x;
		left.y -= right.y;
		return left;
	}

	friend Vec2 operator * (const Vec2& value, float scalar)
	{
		return Vec2(value.x * scalar, value.y * scalar);
	}

	friend Vec2 operator * (float scalar, const Vec2& left)
	{
		return Vec2(left.x * scalar, left.y * scalar);
	}

	friend Vec2& operator *= (Vec2& value, float scalar)
	{
		value.x *= scalar;
		value.y *= scalar;
		return value;
	}

	friend Vec2 operator / (const Vec2& value, float scalar)
	{
		return Vec2(value.x / scalar, value.y / scalar);
	}

	friend Vec2& operator /= (Vec2& value, float scalar)
	{
		value.x /= scalar;
		value.y /= scalar;
		return value;
	}
};