#pragma once

#include "entity.h"
#include "camera.h"
#include "light.h"

class Scene
{
public:
	Scene()
	{
		mCamera = std::make_unique<Camera>();
	}

	const std::vector<std::unique_ptr<Entity>>& GetEntities() const { return mEntities; }
	Camera* GetCamera() const { return mCamera.get(); }
	const std::vector<std::unique_ptr<Light>>& GetLights() const { return mLights; }

	Entity* CreateEntity(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader> shader)
	{
		auto entity = std::make_unique<Entity>(mesh, shader);
		mEntities.push_back(std::move(entity));
		return mEntities.back().get();
	}

private:
	std::vector<std::unique_ptr<Entity>> mEntities;
	std::unique_ptr<Camera> mCamera;
	std::vector<std::unique_ptr<Light>> mLights;
};