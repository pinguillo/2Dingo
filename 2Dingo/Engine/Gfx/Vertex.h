#pragma once
#include "../Math/Vector2.h"
#include "ColorRGBA8.h"

struct Vertex
{
	Vector2 Position;
	ColorRGBA8 Color;
	Vector2 UV;

	void setPosition(float x, float y)
	{
		Position = { x,y };
	}
	void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		Color = { r,g,b,a };
	}
	void setUV(float u, float v)
	{
		UV = { u,v };
	}
};