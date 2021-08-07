#pragma once

#include "texture.h"

class FrameBuffer
{
public:
	FrameBuffer(int32 width, int32 height) : mWidth(width), mHeight(height)
	{
		mColorBuffer = new Texture(width, height);
		mDepthBuffer = new float[width * height];
	}

	virtual ~FrameBuffer()
	{
		SAFE_DELETE(mColorBuffer);
		SAFE_DELETE_ARRAY(mDepthBuffer);
	}

	void Resize(int32 width, int32 height)
	{
		SAFE_DELETE(mColorBuffer);
		SAFE_DELETE_ARRAY(mDepthBuffer);

		mWidth = width;
		mHeight = height;
		mColorBuffer = new Texture(width, height);
		mDepthBuffer = new float[width * height];
	}

	int32 GetWidth() const { return mWidth; }
	int32 GetHeight() const { return mHeight; }
	
	void SetPixel(int32 x, int32 y, const Color& color)
	{
		mColorBuffer->SetPixel(x, y, color);
	}

	float GetDepth(int32 x, int32 y) const
	{
		return mDepthBuffer[x + y * mWidth];
	}

	void SetDepth(int32 x, int32 y, float depth)
	{
		mDepthBuffer[x + y * mWidth] = depth;
	}

	void ClearDepthBuffer()
	{
		for (int32 i = 0; i < mWidth * mHeight; i++)
		{
			mDepthBuffer[i] = std::numeric_limits<float>::max();
		}
	}

	void ClearColorBuffer(const Color& clearColor)
	{
		mColorBuffer->Clear(clearColor);
	}

	const Texture* GetColorBuffer() const { return mColorBuffer; }
	const float* GetDepthBuffer() const { return mDepthBuffer; }

private:
	Texture* mColorBuffer;
	float* mDepthBuffer;

	int32 mWidth;
	int32 mHeight;
};