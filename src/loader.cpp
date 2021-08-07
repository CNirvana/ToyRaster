#include "loader.h"

#include "objLoader.h"
#include "tgaimage.h"

std::shared_ptr<Mesh> Loader::LoadMesh(const std::string& path)
{
	objl::Loader loader;
	loader.LoadFile(path);

	if (loader.LoadedMeshes.size() == 0)
	{
		return nullptr;
	}

	std::vector<Vertex> vertices;
	std::vector<uint32> indices;
	auto m = loader.LoadedMeshes[0];
	for (int i = 0; i < m.Vertices.size(); i++)
	{
		auto mV = m.Vertices[i];
		Vertex v;
		v.position = Vec3(mV.Position.X, mV.Position.Y, mV.Position.Z);
		v.uv = Vec2(mV.TextureCoordinate.X, mV.TextureCoordinate.Y);
		v.normal = Vec3(mV.Normal.X, mV.Normal.Y, mV.Normal.Z);
		vertices.push_back(v);
	}
	for (int i = 0; i < m.Indices.size(); i++)
	{
		indices.push_back(m.Indices[i]);
	}
	return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Texture> Loader::LoadTexture(const std::string& path)
{
	TGAImage img;
	img.read_tga_file(path.c_str());
	int width = img.get_width();
	int height = img.get_height();

	Color* pixels = new Color[width * height];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			TGAColor c = img.get(i, j);
			pixels[i + j * width] = Color(c.bgra[2] / 255.0f, c.bgra[1] / 255.0f, c.bgra[0] / 255.0f, 1);
		}
	}

	return std::make_shared<Texture>(pixels, width, height);
}