#pragma once

#include "maths.h"

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color() : r(0), g(0), b(0), a(0) { }
	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }

	static const Color White()
	{
		return { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	static const Color Black()
	{
		return { 0.0f, 0.0f, 0.0f, 1.0f };
	}

	static const Color Clear()
	{
		return { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	static const Color Red()
	{
		return { 1.0f, 0.0f, 0.0f, 1.0f };
	}

	static const Color Green()
	{
		return { 0.0f, 1.0f, 0.0f, 1.0f };
	}

	static const Color Blue()
	{
		return { 0.0f, 0.0f, 1.0f, 1.0f };
	}

	static const Color Yellow()
	{
		return { 1.0f, 0.92f, 0.016f, 1.0f };
	}

	static const Color Gray()
	{
		return { 0.5f, 0.5f, 0.5f, 1.0f };
	}

	friend Color operator*(const Color& color, float scalar)
	{
		return Color(color.r * scalar, color.g * scalar, color.b * scalar, color.a * scalar);
	}

	friend Color& operator *=(Color& color, float scalar)
	{
		color.r *= scalar;
		color.g *= scalar;
		color.b *= scalar;
		color.a *= scalar;
		return color;
	}

	friend Color operator*(float scalar, const Color& color)
	{
		return Color(color.r * scalar, color.g * scalar, color.b * scalar, color.a * scalar);
	}

	friend Color operator/(const Color& color, float scalar)
	{
		return Color(color.r / scalar, color.g / scalar, color.b / scalar, color.a / scalar);
	}

	friend Color operator+(const Color& a, const Color& b)
	{
		return Color(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);
	}

	friend Color operator-(const Color& a, const Color& b)
	{
		return Color(a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a);
	}

	friend Color operator*(const Color& a, const Color& b)
	{
		return Color(a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a);
	}
};
