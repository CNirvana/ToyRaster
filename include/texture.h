#pragma once

#include "core.h"
#include "color.h"
#include "vec2.h"

enum class TextureWrapMode
{
	Clamp,
	Repeat
};

enum class TextureFilterMode
{
	Point,
	Bilinear,
	Trilinear
};

class Texture
{
public:
	Texture() : mPixels(nullptr), mWidth(0), mHeight(0), mWrapMode(TextureWrapMode::Clamp), mFilterMode(TextureFilterMode::Point) {}
	Texture(int32 width, int32 height) : mWidth(width), mHeight(height), mWrapMode(TextureWrapMode::Clamp), mFilterMode(TextureFilterMode::Point)
	{
		mPixels = new Color[width * height];
		Clear(Color::Clear());
	}
	Texture(Color* pixels, int width, int height, TextureWrapMode wrapMode = TextureWrapMode::Clamp, TextureFilterMode filterMode = TextureFilterMode::Point)
		: mWidth(width), mHeight(height), mWrapMode(wrapMode), mFilterMode(filterMode)
	{
		mPixels = pixels;
	}
	~Texture()
	{
		if (mPixels != nullptr)
		{
			delete[] mPixels;
			mPixels = nullptr;
		}
	}

	Color GetPixel(int32 x, int32 y) const
	{
		return mPixels[x + y * mWidth];
	}

	void SetPixel(int32 x, int32 y, const Color& color)
	{
		mPixels[x + y * mWidth] = color;
	}

	const Color* GetPixels() const { return mPixels; }

	void SetPixels(Color* pixels, int width, int height)
	{
		mPixels = pixels;
		mWidth = width;
		mHeight = height;
	}

	void Clear(const Color& clearColor)
	{
		for (int i = 0; i < mWidth * mHeight; i++)
			mPixels[i] = clearColor;
	}

	Color Sample(const Vec2& texCoord) const
	{
		float u = texCoord.x;
		float v = texCoord.y;
		switch (mWrapMode)
		{
		case TextureWrapMode::Clamp:
			{
				u = Math::Clamp(u, 0.f, 1.f);
				v = Math::Clamp(v, 0.f, 1.f);
			}
			break;
		case TextureWrapMode::Repeat:
			{
				u = u - Math::Floor(u);
				v = v - Math::Floor(v);
			}
			break;
		default:
			break;
		}

		v = 1 - v;

		return GetPixel(u * (mWidth - 1), v * (mHeight - 1));
	}

	int32 GetWidth() const { return mWidth; }
	int32 GetHeight() const { return mHeight; }
	TextureWrapMode GetWrapMode() const { return mWrapMode; }
	void SetWrapMode(TextureWrapMode wrapMode) { mWrapMode = wrapMode; }
	TextureFilterMode GetFilterMode() const { return mFilterMode; }
	void SetFilterMode(TextureFilterMode filterMode) { mFilterMode = filterMode; }

private:
	Color* mPixels;
	int32 mWidth;
	int32 mHeight;

	TextureWrapMode mWrapMode;
	TextureFilterMode mFilterMode;
};