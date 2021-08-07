#include "application.h"

class Sandbox : public Application
{
public:
	Sandbox(const std::string& title, int screenWidth, int screenHeight)
		: Application(title, screenWidth, screenHeight) {}

	virtual void Setup() override
	{
		auto mesh = Loader::Load<Mesh>("resources/head.obj");
		auto texture = Loader::Load<Texture>("resources/african_head_diffuse.tga");
		auto shader = std::make_shared<DefaultShader>();
		shader->SetTexture("BaseMap", texture);

		GetScene()->CreateEntity(mesh, shader);

		std::vector<Vertex> vertices = {
			{ {-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
			{ {1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
			{ {-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} },
			{ {1.0f, 1.0f, 0.0f}, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }
		};
		std::vector<uint32> indices = { 0, 1, 2, 1, 3, 2 };
		auto quadMesh = std::make_shared<Mesh>(vertices, indices);
		auto colorShader = std::make_shared<ColorShader>();
		colorShader->mColor = Color::Blue();

		auto quad = GetScene()->CreateEntity(quadMesh, colorShader);
		quad->GetTransform().position = { 0, -1.f, 0 };
		quad->GetTransform().rotation = Quat::CreateFromEuler(Math::ToRadians(-90.0f), 0, 0);

		auto camera = GetScene()->GetCamera();
		camera->position = { 0, 0, 5 };
	}
	
	virtual void Update(float dt) override
	{
		auto camera = GetScene()->GetCamera();
		float x = 5 * Math::Cos(GetTime());
		float y = 3;
		float z = 5 * Math::Sin(GetTime());
		camera->position = { x, y, z };
	}

	virtual void Destroy() override
	{
	}
};

int main(int argc, char** argv)
{
	Sandbox sandbox("Toy Rasterizer", 800, 600);
	sandbox.Initialize();
	sandbox.Run();
	sandbox.Shutdown();

	return 0;
}