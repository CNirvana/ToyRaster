#pragma once

#include "frameBuffer.h"
#include "mesh.h"
#include "shader.h"

class Rasterizer
{
public:
	Rasterizer(FrameBuffer* frameBuffer, std::shared_ptr<Shader>& shader) : mFrameBuffer(frameBuffer), mShader(shader) { }

	void Draw(const std::shared_ptr<Mesh>& mesh);

private:
	void DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	inline bool Clipping(const Vec4& v) const;
	void HomogeneousToViewport(Vec4* v) const;
	void Rasterize(const Varyings& v0, const Varyings& v1, const Varyings& v2);
	inline float EdgeFunction(float ax, float ay, float bx, float by, float px, float py) const;
	bool InTriangle(float ax, float ay, float bx, float by, float cx, float cy, float px, float py) const;
	void Interpolate(const Varyings& v0, const Varyings& v1, const Varyings& v2, float w0, float w1, float w2, Varyings& out) const;

	void DrawWireframe(const Varyings& v0, const Varyings& v1, const Varyings& v2);
	void DrawLine(Vec2 p0, Vec2 p1, const Color& color);

	FrameBuffer* mFrameBuffer;
	std::shared_ptr<Shader> mShader;

};