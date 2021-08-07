#pragma once

#include <cmath>

const float PI = 3.14159265359f;
const float TWO_PI = PI * 2;
const float DEG_TO_RAD = PI / 180.0f;
const float RAD_TO_DEG = 180.0f / PI;
const float EPSILON = 1e-6;

struct Math
{
	inline static float ToRadians(float degree)
	{
		return degree * DEG_TO_RAD;
	}

	inline static float ToDegree(float radians)
	{
		return radians * RAD_TO_DEG;
	}

	inline static float Cos(float radians)
	{
		return std::cosf(radians);
	}

	inline static float ACos(float value)
	{
		return std::acosf(value);
	}

	inline static float Sin(float radians)
	{
		return std::sinf(radians);
	}

	inline static float ASin(float value)
	{
		return std::asinf(value);
	}

	inline static float Tan(float radians)
	{
		return std::tanf(radians);
	}

	inline static float Atan2(float y, float x)
	{
		return std::atan2f(y, x);
	}

	inline static float Pow(float base, float exponent)
	{
		return std::powf(base, exponent);
	}

	template<typename T>
	inline static T Sqrt(T value)
	{
		return std::sqrt(value);
	}

	template<typename T>
	inline static T Square(T value)
	{
		return value * value;
	}

	template<typename T>
	inline static float Abs(T value)
	{
		return std::abs(value);
	}

	inline static bool Approximately(float a, float b)
	{
		return Abs(a - b) <= EPSILON;
	}

	inline static float Lerp(float a, float b, float t)
	{
		return (1 - t) * a + t * b;
	}

	inline static float Floor(float value)
	{
		return std::floor(value);
	}

	inline static float Ceil(float value)
	{
		return std::ceil(value);
	}

	template<typename T>
	inline static T Min(T a, T b)
	{
		return a <= b ? a : b;
	}

	template<typename T>
	inline static T Max(T a, T b)
	{
		return a >= b ? a : b;
	}

	template<typename T>
	inline static T Clamp(T v, T minValue, T maxValue)
	{
		v = Max(v, minValue);
		v = Min(v, maxValue);
		return v;
	}
};