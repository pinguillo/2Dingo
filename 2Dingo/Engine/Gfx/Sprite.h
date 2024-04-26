#pragma once
#include "Texture.h"
#include <string>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string texturePath);

	void Draw(int textureUniform);

private:
	float mX = 0.0f;
	float mY = 0.0f;
	float mWidth;
	float mHeight;

	unsigned int mVBOID = 0;

	Texture mTexture;
};