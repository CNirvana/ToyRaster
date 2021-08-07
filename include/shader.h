#pragma once

#include "vertex.h"
#include "mat4.h"
#include "texture.h"

struct Attributes
{
	Vec3 position;
	Vec2 uv;
	Vec3 normal;
	Color color;
};

struct Varyings
{
	Vec4 position;
	Vec3 worldPos;
	Vec2 uv;
	Vec3 normal;
	Color color;
};

enum class SurfaceType
{
	Opaque,
	Translucency
};

enum class BlendMode
{
	Zero,
	One,
	SrcAlpha,
	OneMinusSrcAlpha
};

struct Blend
{
	BlendMode srcBlend = BlendMode::One;
	BlendMode dstBlend = BlendMode::Zero;
};

class Shader
{
public:
	// Per draw
	static Mat4 view;
	static Mat4 projection;
	static Mat4 viewProjection;

	// Per object
	Mat4 model{ 1 };

	void SetTexture(const std::string& name, const std::shared_ptr<Texture>& value) { mTextures.insert(std::make_pair(name, value)); }
	std::shared_ptr<Texture> GetTexture(const std::string& name) const
	{
		auto iter = mTextures.find(name);
		if (iter != mTextures.end())
		{
			return iter->second;
		}

		return nullptr;
	}

	virtual Varyings Vert(const Attributes& input) const = 0;
	virtual Color Frag(const Varyings& input) const = 0;

protected:
	std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;
	SurfaceType surfaceType{ SurfaceType::Opaque };
	Blend blend{ BlendMode::One, BlendMode::Zero };
};

class DefaultShader : public Shader
{
public:
	Varyings Vert(const Attributes& input) const override
	{
		Varyings output;
		auto worldPos = Mat4::MultiplyPoint(model, input.position);
		output.worldPos = {worldPos.x, worldPos.y, worldPos.z};
		output.position = Mat4::MultiplyPoint(viewProjection, output.worldPos);
		output.uv = input.uv;
		output.normal = input.normal;
		output.color = input.color;

		return output;
	}

	Color Frag(const Varyings& input) const override
	{
		const Vec3 lightDir(1.0f, 1.0f, 1.0f);
		float NdotL = Math::Max(0.0f, Vec3::Dot(Vec3::Normalize(input.normal), Vec3::Normalize(lightDir)));
		Color col = GetTexture("BaseMap")->Sample(input.uv);
		col *= NdotL;
		col.a = 1.0f;
		return col;
	}
};

class ColorShader : public Shader
{
public:
	Varyings Vert(const Attributes& input) const override
	{
		Varyings output;
		auto worldPos = Mat4::MultiplyPoint(model, input.position);
		output.worldPos = { worldPos.x, worldPos.y, worldPos.z };
		output.position = Mat4::MultiplyPoint(viewProjection, output.worldPos);
		output.uv = input.uv;
		output.normal = input.normal;
		output.color = input.color;

		return output;
	}

	Color Frag(const Varyings& input) const override
	{
		return mColor;
	}

	Color mColor;
};