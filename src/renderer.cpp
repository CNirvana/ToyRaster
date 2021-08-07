#include "renderer.h"

void Renderer::BuildContex(RenderContext* renderContext, const std::vector<Entity*>& visibleEntities)
{
	for (auto entity : visibleEntities)
	{
		renderContext->opaqueEntities.push_back(entity);
	}
}

void DefaultRenderer::Render(const Scene& scene)
{
	auto& entities = scene.GetEntities();
	std::vector<Entity*> visibleEntities;
	for (auto& entity : entities)
	{
		visibleEntities.push_back(entity.get());
	}

	Shader::view = Mat4::LookAt(scene.GetCamera()->position, scene.GetCamera()->target, scene.GetCamera()->up);
	Shader::projection = Mat4::Perspective(Math::ToRadians(scene.GetCamera()->fov), (float)mWidth / mHeight, scene.GetCamera()->near, scene.GetCamera()->far);
	Shader::viewProjection = Shader::projection * Shader::view;

	RenderContext context;
	BuildContex(&context, visibleEntities);

	GetFrameBuffer()->ClearColorBuffer(scene.GetCamera()->backgroundColor);
	GetFrameBuffer()->ClearDepthBuffer();

	DrawOpaque(context);
}

void DefaultRenderer::DrawOpaque(const RenderContext& context)
{
	for (auto& entity : context.opaqueEntities)
	{
		auto shader = entity->GetShader();
		shader->model = entity->GetTransform().LocalToWorld();

		Rasterizer rasterizer(GetFrameBuffer(), shader);
		rasterizer.Draw(entity->GetMesh());
	}
}