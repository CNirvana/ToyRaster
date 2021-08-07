#pragma once

#include "mat4.h"

struct Quat
{
	// [pv(x, y, z), ps]
	// [axis * sin(theta / 2), cos(theta / 2)]
	float x;
	float y;
	float z;
	float w;

	Quat() : x(0), y(0), z(0), w(1) { }
	Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

	inline float LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	inline float Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	void Conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	void Inverse()
	{
		float lenSquared = LengthSquared();
		float scalar = 1.0f / lenSquared;
		x = -x * scalar;
		y = -y * scalar;
		z = -z * scalar;
		w = -w * scalar;
	}

	void Normalize()
	{
		float lenSquared = LengthSquared();
		if (Math::Approximately(lenSquared, 0.0f))
		{
			return;
		}

		float scalar = 1.0f / Math::Sqrt(lenSquared);
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
	}

	
	static Quat Identity()
	{
		return {0, 0, 0, 1};
	}

	static float Dot(const Quat& left, const Quat& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	static Quat Conjugate(const Quat& value)
	{
		return Quat(-value.x, -value.y, -value.z, value.w);
	}

	static Quat Inverse(const Quat& value)
	{
		Quat q;
		float lenSquared = value.LengthSquared();
		float scalar = 1.0f / lenSquared;
		q.x = -value.x * scalar;
		q.y = -value.y * scalar;
		q.z = -value.z * scalar;
		q.w = -value.w * scalar;
		return q;
	}

	static Quat Normalize(const Quat& value)
	{
		float lenSquared = value.LengthSquared();
		if (Math::Approximately(lenSquared, 0.0f))
		{
			return Quat();
		}

		Quat q;
		float scalar = 1.0f / Math::Sqrt(lenSquared);
		q.x = value.x * scalar;
		q.y = value.y * scalar;
		q.z = value.z * scalar;
		q.w = value.w * scalar;

		return q;
	}

	static Quat Concatenate(const Quat& left, const Quat& right)
	{
		Quat ret;

		float x1 = left.x;
		float y1 = left.y;
		float z1 = left.z;
		float w1 = left.w;

		float x2 = right.x;
		float y2 = right.y;
		float z2 = right.z;
		float w2 = right.w;

		ret.x = ((x2 * w1) + (x1 * w2)) + ((y2 * z1) - (z2 * y1));
		ret.y = ((y2 * w1) + (y1 * w2)) + ((z2 * x1) - (x2 * z1));
		ret.z = ((z2 * w1) + (z1 * w2)) + ((x2 * y1) - (y2 * x1));
		ret.w = (w2 * w1) - (((x2 * x1) + (y2 * y1)) + (z2 * z1));

		return ret;
	}

	static Vec3 Rotate(const Quat& q, const Vec3& v)
	{
		// v + 2 * qv x (qv x v + qs * v)
		Vec3 qv(q.x, q.y, q.z);
		Vec3 v1 = Vec3::Cross(qv, v);
		return v + Vec3::Cross(2.0f * qv, v1 + q.w * v);
	}

	static Quat Lerp(const Quat& p, const Quat& q, float t)
	{
		float num = t;
		float num2 = 1.0f - num;
		Quat quaternion;
		float num5 = (((p.x * q.x) + (p.y * q.y)) + (p.z * q.z)) + (p.w * q.w);
		if (num5 >= 0)
		{
			quaternion.x = (num2 * p.x) + (num * q.x);
			quaternion.y = (num2 * p.y) + (num * q.y);
			quaternion.z = (num2 * p.z) + (num * q.z);
			quaternion.w = (num2 * p.w) + (num * q.w);
		}
		else
		{
			quaternion.x = (num2 * p.x) - (num * q.x);
			quaternion.y = (num2 * p.y) - (num * q.y);
			quaternion.z = (num2 * p.z) - (num * q.z);
			quaternion.w = (num2 * p.w) - (num * q.w);
		}
		float num4 = (((quaternion.x * quaternion.x) + (quaternion.y * quaternion.y)) + (quaternion.z * quaternion.z)) + (quaternion.w * quaternion.w);
		float num3 = 1.0f / Math::Sqrt(num4);
		quaternion.x *= num3;
		quaternion.y *= num3;
		quaternion.z *= num3;
		quaternion.w *= num3;
		return quaternion;
	}

	static Quat Slerp(const Quat& p, const Quat& q, float t)
	{
		float num2;
		float num3;
		Quat quaternion;
		float num = t;
		float num4 = (((p.x * q.x) + (p.y * q.y)) + (p.z * q.z)) + (p.w * q.w);
		bool flag = false;
		if (num4 < 0.0f)
		{
			flag = true;
			num4 = -num4;
		}
		if (num4 > 0.999999f)
		{
			num3 = 1.0f - num;
			num2 = flag ? -num : num;
		}
		else
		{
			float num5 = Math::ACos(num4);
			float num6 = (1.0 / Math::Sin(num5));
			num3 = (Math::Sin(((1.0f - num) * num5))) * num6;
			num2 = flag ? ((-Math::Sin((num * num5))) * num6) : ((Math::Sin(num * num5)) * num6);
		}
		quaternion.x = (num3 * p.x) + (num2 * q.x);
		quaternion.y = (num3 * p.y) + (num2 * q.y);
		quaternion.z = (num3 * p.z) + (num2 * q.z);
		quaternion.w = (num3 * p.w) + (num2 * q.w);
		return quaternion;
	}

	static Quat CreateFromAxisAngle(Vec3 axis, float angle)
	{
		float half = angle * 0.5f;
		float sin = Math::Sin(half);
		float cos = Math::Cos(half);
		return Quat(axis.x * sin, axis.y * sin, axis.z * sin, cos);
	}

	static Quat CreateFromRotationMatrix(const Mat4& matrix)
	{
		Quat quaternion;
		float sqrt;
		float half;
		float scale = matrix[0][0] + matrix[1][1] + matrix[2][2];

		if (scale > 0.0f)
		{
			sqrt = Math::Sqrt(scale + 1.0f);
			quaternion.w = sqrt * 0.5f;
			sqrt = 0.5f / sqrt;

			quaternion.x = (matrix[2][1] - matrix[1][2]) * sqrt;
			quaternion.y = (matrix[0][2] - matrix[2][0]) * sqrt;
			quaternion.z = (matrix[1][0] - matrix[0][1]) * sqrt;

			return quaternion;
		}
		if ((matrix[0][0] >= matrix[1][1]) && (matrix[0][0] >= matrix[2][2]))
		{
			sqrt = Math::Sqrt(1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2]);
			half = 0.5f / sqrt;

			quaternion.x = 0.5f * sqrt;
			quaternion.y = (matrix[0][1] + matrix[1][0]) * half;
			quaternion.z = (matrix[0][2] + matrix[2][0]) * half;
			quaternion.w = (matrix[2][1] - matrix[1][2]) * half;

			return quaternion;
		}
		if (matrix[1][1] > matrix[2][2])
		{
			sqrt = Math::Sqrt(1.0f + matrix[1][1] - matrix[0][0] - matrix[2][2]);
			half = 0.5f / sqrt;

			quaternion.x = (matrix[1][0] + matrix[0][1]) * half;
			quaternion.y = 0.5f * sqrt;
			quaternion.z = (matrix[2][1] + matrix[1][2]) * half;
			quaternion.w = (matrix[0][2] - matrix[2][0]) * half;

			return quaternion;
		}
		sqrt = Math::Sqrt(1.0f + matrix[2][2] - matrix[0][0] - matrix[1][1]);
		half = 0.5f / sqrt;

		quaternion.x = (matrix[2][0] + matrix[0][2]) * half;
		quaternion.y = (matrix[2][1] + matrix[1][2]) * half;
		quaternion.z = 0.5f * sqrt;
		quaternion.w = (matrix[1][0] - matrix[0][1]) * half;

		return quaternion;
	}

	static Quat CreateFromEuler(const Vec3& eulerAngle)
	{
		return CreateFromEuler(eulerAngle.x, eulerAngle.y, eulerAngle.z);
	}

	static Quat CreateFromEuler(float x, float y, float z)
	{
		float halfRoll = z * 0.5f;
		float halfPitch = x * 0.5f;
		float halfYaw = y * 0.5f;

		float sinRoll = Math::Sin(halfRoll);
		float cosRoll = Math::Cos(halfRoll);
		float sinPitch = Math::Sin(halfPitch);
		float cosPitch = Math::Cos(halfPitch);
		float sinYaw = Math::Sin(halfYaw);
		float cosYaw = Math::Cos(halfYaw);

		return Quat((cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
			(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll),
			(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
			(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll));
	}

	static Mat4 ToRotationMatrix(const Quat& q)
	{
		Mat4 m;
		float num9 = q.x * q.x;
		float num8 = q.y * q.y;
		float num7 = q.z * q.z;
		float num6 = q.x * q.y;
		float num5 = q.z * q.w;
		float num4 = q.z * q.x;
		float num3 = q.y * q.w;
		float num2 = q.y * q.z;
		float num = q.x * q.w;
		m[0][0] = 1.0f - (2.0f * (num8 + num7));
		m[1][0] = 2.0f * (num6 + num5);
		m[2][0] = 2.0f * (num4 - num3);
		m[0][1] = 2.0f * (num6 - num5);
		m[1][1] = 1.0f - (2.0f * (num7 + num9));
		m[2][1] = 2.0f * (num2 + num);
		m[0][2] = 2.0f * (num4 + num3);
		m[1][2] = 2.0f * (num2 - num);
		m[2][2] = 1.0f - (2.0f * (num8 + num9));
		m[3][3] = 1.0f;

		return m;
	}

	friend Quat operator * (const Quat& left, const Quat& right)
	{
		Quat quaternion;
		float x = left.x;
		float y = left.y;
		float z = left.z;
		float w = left.w;
		float num4 = right.x;
		float num3 = right.y;
		float num2 = right.z;
		float num = right.w;
		float num12 = (y * num2) - (z * num3);
		float num11 = (z * num4) - (x * num2);
		float num10 = (x * num3) - (y * num4);
		float num9 = ((x * num4) + (y * num3)) + (z * num2);
		quaternion.x = ((x * num) + (num4 * w)) + num12;
		quaternion.y = ((y * num) + (num3 * w)) + num11;
		quaternion.z = ((z * num) + (num2 * w)) + num10;
		quaternion.w = (w * num) - num9;
		return quaternion;
	}
};
