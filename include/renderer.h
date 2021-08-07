#pragma once

#include "scene.h"
#include "frameBuffer.h"
#include "rasterizer.h"

struct RenderContext
{
	std::vector<Entity*> opaqueEntities;
	std::vector<Entity*> transparentEntities;
};

class Renderer
{
public:
	Renderer(int32 width, int32 height) : mWidth(width), mHeight(height)
	{
		mFrameBuffer = std::make_unique<FrameBuffer>(width, height);
	}

	virtual void Resize(int32 width, int32 height) = 0;
	virtual void Render(const Scene& scene) = 0;
	virtual void BuildContex(RenderContext* renderContext, const std::vector<Entity*>& visibleEntities);

	FrameBuffer* GetFrameBuffer() const { return mFrameBuffer.get(); }

protected:
	int32 mWidth;
	int32 mHeight;
	std::unique_ptr<FrameBuffer> mFrameBuffer;
};

class DefaultRenderer : public Renderer
{
public:
	using Renderer::Renderer;

	virtual void Resize(int32 width, int32 height) override { }
	virtual void Render(const Scene& scene) override;

private:
	void DrawOpaque(const RenderContext& context);

};