#pragma once
#include "Gfx\Texture.h"

#include <map>
#include <string>

// class for loading images into a texture
class ImageLoader
{
public:
	static Texture loadPNG(std::string filepath);
};

// class for the texture cache
class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	// gets a texture from the map or loads a new one if it doesn't exist
	Texture getTexture(std::string texturePath);

private:
	std::map<std::string, Texture> mTextureMap;
};

// class that encapsulates all the resource caches
class ResourceManager
{
public:
	static Texture getTexture(std::string texturePath);
private:
	static TextureCache mTextureCache;
};