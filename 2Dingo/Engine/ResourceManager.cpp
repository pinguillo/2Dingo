#include "ResourceManager.h"

#include "Util\IOManager.h"
#include "External\picoPNG.h"

#include <vector>
#include <GLEW\glew.h>

#include "Util\Logger.h"

TextureCache ResourceManager::mTextureCache;

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

Texture TextureCache::getTexture(std::string texturePath)
{
	auto mit = mTextureMap.find(texturePath);

	//If doesn't exist, load it
	if (mit == mTextureMap.end())
	{
		Texture tex = ImageLoader::loadPNG(texturePath);
		mTextureMap.insert(std::make_pair(texturePath, tex));
		Logger::Info("Cached new texture");
		return tex;
	}
	//LogInfo("Used cached texture");
	return mit->second;
}

Texture ResourceManager::getTexture(std::string texturePath)
{
	return mTextureCache.getTexture(texturePath);
}

Texture ImageLoader::loadPNG(std::string filepath)
{
	Texture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;

	if (!IOManager::ReadFileToBuffer(filepath, in))
	{
		Logger::Fatal("Failed to load PNG to buffer");
	}

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0)
	{
		Logger::Fatal("DecodePNG failed with error: %n", errorCode);
	}

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}
