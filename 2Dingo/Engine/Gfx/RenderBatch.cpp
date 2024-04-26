#include "RenderBatch.h"

#include <algorithm>
#include <GLEW/glew.h>

RenderBatch::RenderBatch()
{
}

RenderBatch::~RenderBatch()
{
}

void RenderBatch::Init()
{
	createVertexArray();
}

void RenderBatch::Begin(GlyphSortType sortType)
{
	mSortType = sortType;
	mBatches.clear();
	mGlyphs.clear();
}

void RenderBatch::End()
{
	mGlyphsPtr.resize(mGlyphs.size());
	for (int i = 0; i < mGlyphs.size(); i++)
	{
		mGlyphsPtr[i] = &mGlyphs[i];
	}
	sortGlyphs();
	createRenderBatches();
}

void RenderBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color)
{
	mGlyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void RenderBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color, float angle)
{
	mGlyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void RenderBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color, const Vector2& dir)
{
	const Vector2 right(1.0f, 0.0f);
	float angle = acos(Vector2::Dot(right, dir));
	if (dir.Y < 0.0f) { angle = -angle; }
	mGlyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void RenderBatch::Render()
{
	glBindVertexArray(mVAO);
	for (int i = 0; i < mBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, mBatches[i].mTexture);
		glDrawArrays(GL_TRIANGLES, mBatches[i].mOffset, mBatches[i].mNumVertices);
	}
	glBindVertexArray(0);
}

void RenderBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(mGlyphs.size() * 6);

	if (mGlyphs.empty()) { return; }

	int offset = 0;
	int currentVertex = 0;

	mBatches.emplace_back(offset, 6, mGlyphsPtr[0]->Texture);
	vertices[currentVertex++] = mGlyphsPtr[0]->TopLeft;
	vertices[currentVertex++] = mGlyphsPtr[0]->BottomLeft;
	vertices[currentVertex++] = mGlyphsPtr[0]->BottomRight;
	vertices[currentVertex++] = mGlyphsPtr[0]->BottomRight;
	vertices[currentVertex++] = mGlyphsPtr[0]->TopRight;
	vertices[currentVertex++] = mGlyphsPtr[0]->TopLeft;
	offset += 6;

	for (int currentGlyph = 1; currentGlyph < mGlyphsPtr.size(); currentGlyph++)
	{
		if (mGlyphsPtr[currentGlyph]->Texture != mGlyphsPtr[currentGlyph - 1]->Texture)
		{
			mBatches.emplace_back(offset, 6, mGlyphsPtr[currentGlyph]->Texture);
		}
		else
		{
			mBatches.back().mNumVertices += 6;
		}
		vertices[currentVertex++] = mGlyphsPtr[currentGlyph]->TopLeft;
		vertices[currentVertex++] = mGlyphsPtr[currentGlyph]->BottomLeft;
		vertices[currentVertex++] = mGlyphsPtr[currentGlyph]->BottomRight;
		vertices[currentVertex++] = mGlyphsPtr[currentGlyph]->BottomRight;
		vertices[currentVertex++] = mGlyphsPtr[currentGlyph]->TopRight;
		vertices[currentVertex++] = mGlyphsPtr[currentGlyph]->TopLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderBatch::createVertexArray()
{
	if (mVAO == 0) { glGenVertexArrays(1, &mVAO); }
	glBindVertexArray(mVAO);

	if (mVBO == 0) { glGenBuffers(1, &mVBO); }
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));		//Position attrib
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, Color)); //Color attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));			//UV attrib

	glBindVertexArray(0);
}

void RenderBatch::sortGlyphs()
{
	switch (mSortType)
	{
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(mGlyphsPtr.begin(), mGlyphsPtr.end(), compareFrontToBack);
		break;
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(mGlyphsPtr.begin(), mGlyphsPtr.end(), compareBackToFront);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(mGlyphsPtr.begin(), mGlyphsPtr.end(), compareTexture);
		break;
	}
}

bool RenderBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return (a->Depth < b->Depth);
}

bool RenderBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return (a->Depth > b->Depth);
}

bool RenderBatch::compareTexture(Glyph* a, Glyph* b)
{
	return (a->Texture < b->Texture);
}

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color) : Texture(texture)
{
	TopLeft.Color = color;
	TopLeft.setPosition(destRect.x, destRect.y + destRect.w);
	TopLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	BottomLeft.Color = color;
	BottomLeft.setPosition(destRect.x, destRect.y);
	BottomLeft.setUV(uvRect.x, uvRect.y);

	TopRight.Color = color;
	TopRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	TopRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	BottomRight.Color = color;
	BottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	BottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
}

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color, float angle) : Texture(texture)
{
	Vector2 half(destRect.z / 2.0f, destRect.w / 2.0f);
	Vector2 tl(-half.X, half.Y);
	Vector2 bl(-half.X, -half.Y);
	Vector2 br(half.X, -half.Y);
	Vector2 tr(half.X, half.Y);

	tl = rotatePoint(tl, angle) + half;
	bl = rotatePoint(bl, angle) + half;
	br = rotatePoint(br, angle) + half;
	tr = rotatePoint(tr, angle) + half;

	TopLeft.Color = color;
	TopLeft.setPosition(destRect.x + tl.X, destRect.y + tl.Y);
	TopLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	BottomLeft.Color = color;
	BottomLeft.setPosition(destRect.x + bl.X, destRect.y + bl.Y);
	BottomLeft.setUV(uvRect.x, uvRect.y);

	TopRight.Color = color;
	TopRight.setPosition(destRect.x + tr.X, destRect.y + tr.Y);
	TopRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	BottomRight.Color = color;
	BottomRight.setPosition(destRect.x + br.X, destRect.y + br.Y);
	BottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
}

Vector2 Glyph::rotatePoint(Vector2 pos, float angle)
{
	Vector2 newv =
	{
		pos.X * cos(angle) - pos.Y * sin(angle),
		pos.X * sin(angle) + pos.Y * cos(angle)
	};
	return newv;
}
