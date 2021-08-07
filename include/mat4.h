#pragma once

#include "core.h"

#include "vec3.h"
#include "vec4.h"

struct Mat4
{
	float data[4][4];

	Mat4()
	{
		memset(data, 0, 16 * sizeof(float));
	}
	Mat4(float diagonal)
	{
		memset(data, 0, 16 * sizeof(float));
		data[0][0] = data[1][1] = data[2][2] = data[3][3] = diagonal;
	}

	float* operator[](size_t index) { return data[index]; }
	const float* operator[](size_t index) const { return data[index]; }

	void SetRow(int row, float v1, float v2, float v3, float v4)
	{
		data[row][0] = v1;
		data[row][1] = v2;
		data[row][2] = v3;
		data[row][3] = v4;
	}

	void SetRow(int row, const Vec4& value)
	{
		SetRow(row, value.x, value.y, value.z, value.w);
	}

	void SetColumn(int column, float v1, float v2, float v3, float v4)
	{
		data[0][column] = v1;
		data[1][column] = v2;
		data[2][column] = v3;
		data[3][column] = v4;
	}

	void SetColumn(int column, const Vec4& value)
	{
		SetColumn(column, value.x, value.y, value.z, value.w);
	}

	Mat4 Transpose()
	{
		Mat4 m;
		m.SetRow(0, data[0][0], data[1][0], data[2][0], data[3][0]);
		m.SetRow(1, data[0][1], data[1][1], data[2][1], data[3][1]);
		m.SetRow(2, data[0][2], data[1][2], data[2][2], data[3][2]);
		m.SetRow(3, data[0][3], data[1][3], data[2][3], data[3][3]);
		return m;
	}

	Mat4& Multiply(const Mat4& other)
	{
		Mat4 m;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				m.data[row][col] = data[row][0] * other.data[0][col]
					+ data[row][1] * other.data[1][col]
					+ data[row][2] * other.data[2][col]
					+ data[row][3] * other.data[3][col];
			}
		}
		memcpy(data, m.data, 4 * 4 * sizeof(float));

		return *this;
	}

	static Vec4 MultiplyPoint(const Mat4& m, const Vec3& point)
	{
		float x = m.data[0][0] * point.x + m.data[0][1] * point.y + m.data[0][2] * point.z + m.data[0][3];
		float y = m.data[1][0] * point.x + m.data[1][1] * point.y + m.data[1][2] * point.z + m.data[1][3];
		float z = m.data[2][0] * point.x + m.data[2][1] * point.y + m.data[2][2] * point.z + m.data[2][3];
		float w = m.data[3][0] * point.x + m.data[3][1] * point.y + m.data[3][2] * point.z + m.data[3][3];
		return Vec4(x, y, z, w);
	}

	static Vec3 MultiplyVector(const Mat4& m, const Vec3& v)
	{
		float x = m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z;
		float y = m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z;
		float z = m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z;
		return Vec3(x, y, z);
	}

	static Mat4 Identity()
	{
		return Mat4(1.0f);
	}

	static Mat4 Translate(const Vec3& translation)
	{
		Mat4 m(1.0f);
		m.data[0][3] = translation.x;
		m.data[1][3] = translation.y;
		m.data[2][3] = translation.z;
		return m;
	}

	static Mat4 Scale(const Vec3& scale)
	{
		Mat4 m;
		m.data[0][0] = scale.x;
		m.data[1][1] = scale.y;
		m.data[2][2] = scale.z;
		m.data[3][3] = 1.0f;
		return m;
	}

	static Mat4 Scale(float scale)
	{
		Mat4 m;
		m.data[0][0] = m.data[1][1] = m.data[2][2] = scale;
		m.data[3][3] = 1.0f;
		return m;
	}
	// static Mat4 Rotate(float radians, const Vec3& axis);

	static Mat4 RotateX(float radians)
	{
		float s = Math::Sin(radians);
		float c = Math::Cos(radians);

		Mat4 m(1.0f);
		m.data[1][1] = c;
		m.data[1][2] = -s;
		m.data[2][1] = s;
		m.data[2][2] = c;

		return m;
	}

	static Mat4 RotateY(float radians)
	{
		float s = Math::Sin(radians);
		float c = Math::Cos(radians);

		Mat4 m(1.0f);
		m.data[0][0] = c;
		m.data[0][2] = s;
		m.data[2][0] = -s;
		m.data[2][2] = c;

		return m;
	}

	static Mat4 RotateZ(float radians)
	{
		float s = Math::Sin(radians);
		float c = Math::Cos(radians);

		Mat4 m(1.0f);
		m.data[0][0] = c;
		m.data[0][1] = -s;
		m.data[1][0] = s;
		m.data[1][1] = c;

		return m;
	}

	static Mat4 Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		Mat4 m(1.0f);

		m.data[0][0] = 2 / (right - left);
		m.data[1][1] = 2 / (top - bottom);
		m.data[2][2] = 2 / (nearPlane - farPlane);

		m.data[0][3] = (right + left) / (left - right);
		m.data[1][3] = (top + bottom) / (bottom - top);
		m.data[2][3] = (farPlane + nearPlane) / (nearPlane - farPlane);

		return m;
	}

	static Mat4 Perspective(float fov, float aspect, float nearPlane, float farPlane)
	{
		float tanInv = 1.f / Math::Tan(fov * 0.5f);

		Mat4 m;
		m.data[0][0] = tanInv / aspect;
		m.data[1][1] = tanInv;
		m.data[2][2] = (nearPlane + farPlane) / (nearPlane - farPlane);
		m.data[2][3] = (2 * nearPlane * farPlane) / (nearPlane - farPlane);
		m.data[3][2] = -1;

		return m;
	}

	static Mat4 LookAt(const Vec3& from, const Vec3& to, const Vec3& up)
	{
		Vec3 f = Vec3::Normalize(to - from);
		Vec3 r = Vec3::Normalize(f ^ up);
		Vec3 u = r ^ f;

		Mat4 m(1.0f);
		m.data[0][0] = r.x;
		m.data[1][0] = u.x;
		m.data[2][0] = -f.x;

		m.data[0][1] = r.y;
		m.data[1][1] = u.y;
		m.data[2][1] = -f.y;

		m.data[0][2] = r.z;
		m.data[1][2] = u.z;
		m.data[2][2] = -f.z;

		m.data[0][3] = -(r | from);
		m.data[1][3] = -(u | from);
		m.data[2][3] = (f | from);

		return m;
	}

	Mat4& operator*=(const Mat4& other)
	{
		return Multiply(other);
	}

	friend Mat4 operator*(const Mat4& left, const Mat4& right)
	{
		Mat4 m;

		for(int row = 0; row < 4; row++)
		{
			for(int col = 0; col < 4; col++)
			{
				m.data[row][col] = left.data[row][0] * right.data[0][col]
					+ left.data[row][1] * right.data[1][col]
					+ left.data[row][2] * right.data[2][col]
					+ left.data[row][3] * right.data[3][col];
			}
		}

		return m;
	}
};
