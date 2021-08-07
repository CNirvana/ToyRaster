#pragma once

#include "core.h"
#include "vertex.h"

class Mesh
{
public:
	Mesh() {}
	Mesh(const std::vector<Vertex> vertices, const std::vector<uint32>& indices)
		: mVertices(vertices), mIndices(indices)
	{
	}

	std::vector<Vertex>& GetVertices() { return mVertices; }
	const std::vector<Vertex>& GetVertices() const { return mVertices; }
	std::vector<uint32>& GetIndices() { return mIndices; }
	const std::vector<uint32>& GetIndices() const { return mIndices; }

private:
	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;
};