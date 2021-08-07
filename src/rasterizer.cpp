#include "rasterizer.h"

void Rasterizer::Draw(const std::shared_ptr<Mesh>& mesh)
{
	auto vertices = mesh->GetVertices();
	auto indices = mesh->GetIndices();
	for (int32 i = 0; i < indices.size(); i += 3)
	{
		DrawTriangle(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
	}
}

void Rasterizer::DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	Attributes attributes0{ v0.position, v0.uv, v0.normal, v0.color };
	Varyings varyings0 = mShader->Vert(attributes0);

	Attributes attributes1{ v1.position, v1.uv, v1.normal, v1.color };
	Varyings varyings1 = mShader->Vert(attributes1);

	Attributes attributes2{ v2.position, v2.uv, v2.normal, v2.color };
	Varyings varyings2 = mShader->Vert(attributes2);;

	// simple clipping
	if (Clipping(varyings0.position) || Clipping(varyings1.position) || Clipping(varyings2.position))
	{
		return;
	}

	HomogeneousToViewport(&varyings0.position);
	HomogeneousToViewport(&varyings1.position);
	HomogeneousToViewport(&varyings2.position);

	Rasterize(varyings0, varyings1, varyings2);
	//DrawWireframe(varyings0, varyings1, varyings2);
}

bool Rasterizer::Clipping(const Vec4& v) const
{
	return (v.x < -v.w || v.x > v.w)
		|| (v.y < -v.w || v.y > v.w)
		|| (v.z < -v.w || v.z > v.w)
		|| (v.w <= 0);
}

void Rasterizer::HomogeneousToViewport(Vec4* v) const
{
	// NDC
	float invZ = 1 / v->w;
	v->x *= invZ;
	v->y *= invZ;
	v->z *= invZ;

	// Viewport
	int32 width = mFrameBuffer->GetWidth() - 1;
	int32 height = mFrameBuffer->GetHeight() - 1;
	v->x = (v->x + 1) * 0.5 * width;
	v->y = (v->y + 1) * 0.5 * height;

	v->w = invZ;
}

void Rasterizer::Rasterize(const Varyings& v0, const Varyings& v1, const Varyings& v2)
{
	Vec4 p0 = v0.position;
	Vec4 p1 = v1.position;
	Vec4 p2 = v2.position;

	int width = mFrameBuffer->GetWidth();
	int height = mFrameBuffer->GetHeight();

	float xMin = std::numeric_limits<float>::max();
	float yMin = std::numeric_limits<float>::max();
	float xMax = -std::numeric_limits<float>::max();
	float yMax = -std::numeric_limits<float>::max();

	xMin = Math::Max(0.0f, Math::Min(xMin, p0.x));
	yMin = Math::Max(0.0f, Math::Min(yMin, p0.y));
	xMax = Math::Min(width - 1.0f, Math::Max(xMax, p0.x));
	yMax = Math::Min(height - 1.0f, Math::Max(yMax, p0.y));

	xMin = Math::Max(0.0f, Math::Min(xMin, p1.x));
	yMin = Math::Max(0.0f, Math::Min(yMin, p1.y));
	xMax = Math::Min(width - 1.0f, Math::Max(xMax, p1.x));
	yMax = Math::Min(height - 1.0f, Math::Max(yMax, p1.y));

	xMin = Math::Max(0.0f, Math::Min(xMin, p2.x));
	yMin = Math::Max(0.0f, Math::Min(yMin, p2.y));
	xMax = Math::Min(width - 1.0f, Math::Max(xMax, p2.x));
	yMax = Math::Min(height - 1.0f, Math::Max(yMax, p2.y));

	float area = EdgeFunction(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
	float invArea = 1.0f / area;
	for (int j = yMin; j < yMax; j++)
	{
		for (int i = xMin; i < xMax; i++)
		{
			Vec3 p(i + 0.5f, j + 0.5f, 0);
			float w0 = EdgeFunction(p1.x, p1.y, p2.x, p2.y, p.x, p.y);
			float w1 = EdgeFunction(p2.x, p2.y, p0.x, p0.y, p.x, p.y);
			float w2 = EdgeFunction(p0.x, p0.y, p1.x, p1.y, p.x, p.y);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 *= invArea;
				w1 *= invArea;
				w2 *= invArea;

				float invZ = v0.position.w * w0 + v1.position.w * w1 + v2.position.w * w2;
				float z = 1 / invZ;
				if (z < mFrameBuffer->GetDepth(i, j))
				{
					mFrameBuffer->SetDepth(i, j, z);

					Varyings varyings;
					Interpolate(v0, v1, v2, w0 * z * v0.position.w, w1 * z * v1.position.w, w2 * z * v2.position.w, varyings);

					Color color = mShader->Frag(varyings);
					mFrameBuffer->SetPixel(i, j, color);
				}
			}
		}
	}
}

float Rasterizer::EdgeFunction(float ax, float ay, float bx, float by, float px, float py) const // CCW
{
	//return (px - ax) * (by - ay) - (py - ay) * (bx - ax); // CW to right
	return (bx - ax) * (py - ay) - (by - ay) * (px - ax); // CCW to left
}

bool Rasterizer::InTriangle(float ax, float ay, float bx, float by, float cx, float cy, float px, float py) const
{
	bool inside = true;
	inside &= (EdgeFunction(ax, ay, bx, by, px, py) >= 0);
	inside &= (EdgeFunction(bx, by, cx, cy, px, py) >= 0);
	inside &= (EdgeFunction(cx, cy, ax, ay, px, py) >= 0);

	return inside;
}

void Rasterizer::Interpolate(const Varyings& v0, const Varyings& v1, const Varyings& v2, float w0, float w1, float w2, Varyings& out) const
{
	out.position = v0.position * w0 + v1.position * w1 + v2.position * w2;
	out.color = v0.color * w0 + v1.color * w1 + v2.color * w2;
	out.uv = v0.uv * w0 + v1.uv * w1 + v2.uv * w2;
	out.normal = v0.normal * w0 + v1.normal * w1 + v2.normal * w2;
	out.worldPos = v0.worldPos * w0 + v1.worldPos * w1 + v2.worldPos * w2;
}

void Rasterizer::DrawWireframe(const Varyings& v0, const Varyings& v1, const Varyings& v2)
{
	Vec2 p0 = Vec2(v0.position.x, v0.position.y);
	Vec2 p1 = Vec2(v1.position.x, v1.position.y);
	Vec2 p2 = Vec2(v2.position.x, v2.position.y);

	DrawLine(p0, p1, Color::White());
	DrawLine(p1, p2, Color::White());
	DrawLine(p2, p0, Color::White());
}

void Rasterizer::DrawLine(Vec2 p0, Vec2 p1, const Color& color)
{
	bool steep = false;
	if (std::abs(p0.x - p1.x) < std::abs(p0.y - p1.y))
	{
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
		steep = true;
	}

	if (p0.x > p1.x)
	{
		std::swap(p0, p1);
	}

	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	float derror = std::abs(dy) * 2;
	float error = 0;
	int y = p0.y;

	for (int x = p0.x; x <= p1.x; x++)
	{
		if (steep)
		{
			mFrameBuffer->SetPixel(x, y, color);
		}
		else
		{
			mFrameBuffer->SetPixel(x, y, color);
		}

		error += derror;
		if (error > dx)
		{
			y += (p1.y > p0.y ? 1 : -1);
			error -= dx * 2;
		}
	}
}