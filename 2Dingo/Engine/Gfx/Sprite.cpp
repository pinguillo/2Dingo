#include "Sprite.h"
#include "Vertex.h"
#include "../ResourceManager.h"
#include <GLEW\glew.h>

//#include <cstddef>

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	if (mVBOID != 0)
	{
		glDeleteBuffers(1, &mVBOID);
	}
}

void Sprite::init(float x, float y, float width, float height, std::string texturePath)
{
	mX = x;
	mY = y;
	mWidth = width;
	mHeight = height;
	mTexture = ResourceManager::getTexture(texturePath);


	if (mVBOID == 0)
	{
		glGenBuffers(1, &mVBOID);
	}

	Vertex vertexData[6] = {};
	vertexData[0].setPosition(x + width, y + width);
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 255, 255, 255);
	}

	//vertexData[1].setColor(0, 0, 255, 255);
	//vertexData[4].setColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, mVBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw(int textureUniform)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Temp, for debugging

	glActiveTexture(GL_TEXTURE0);
    glUniform1i(textureUniform, 0);

	glBindTexture(GL_TEXTURE_2D, mTexture.id);

	glBindBuffer(GL_ARRAY_BUFFER, mVBOID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));		//Position attrib
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Color)); //Color attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));			//UV attrib

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
