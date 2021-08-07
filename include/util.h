#pragma once

#include "tgaimage.h"
#include "texture.h"

static void saveImage(const Texture* texture, std::string fileName)
{
	TGAImage image(texture->GetWidth(), texture->GetHeight(), TGAImage::RGBA);
	for (int j = 0; j < texture->GetHeight(); j++)
	{
		for (int i = 0; i < texture->GetWidth(); i++)
		{
			auto color = texture->GetPixel(i, texture->GetHeight() - j - 1);
			image.set(i, j, TGAColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
		}
	}
	image.write_tga_file(fileName.c_str());
}