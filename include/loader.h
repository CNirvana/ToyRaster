#pragma once

#include "mesh.h"
#include "texture.h"

struct Loader
{
	template<typename T>
	static std::shared_ptr<T> Load(const std::string& path)
	{

	}

	static std::shared_ptr<Mesh> LoadMesh(const std::string& path);

	template<>
	static std::shared_ptr<Mesh> Load<Mesh>(const std::string& path)
	{
		return LoadMesh(path);
	}

	static std::shared_ptr<Texture> LoadTexture(const std::string& path);

	template<>
	static std::shared_ptr<Texture> Load<Texture>(const std::string& path)
	{
		return LoadTexture(path);
	}
};
