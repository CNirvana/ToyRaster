#pragma once

#include "mesh.h"
#include "shader.h"
#include "transform.h"

class Entity
{
public:
	Entity(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader)
		: mMesh(mesh), mShader(shader)
	{
	}

	std::shared_ptr<Shader> GetShader() const { return mShader; }
	void SetShader(const std::shared_ptr<Shader>& shader) { mShader = shader; }
	std::shared_ptr<Mesh> GetMesh() const { return mMesh; }
	void SetMesh(Mesh* mesh) { mMesh.reset(mesh); }

	const Transform& GetTransform() const { return mTransform; }
	Transform& GetTransform() { return mTransform; }

private:
	Transform mTransform;

	std::shared_ptr<Shader> mShader;
	std::shared_ptr<Mesh> mMesh;
};