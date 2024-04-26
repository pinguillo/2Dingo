#pragma once
#include <vector>
#include <glm/vec4.hpp>

#include "Texture.h"
#include "Vertex.h"

enum class GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph
{
public:
	Glyph() {}
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color);
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color, float angle);

	unsigned int Texture;
	float Depth;

	Vertex TopLeft;
	Vertex BottomLeft;
	Vertex TopRight;
	Vertex BottomRight;

private:
	Vector2 rotatePoint(Vector2 pos, float angle);
};

class Batch
{
public:
	Batch(unsigned int offset, unsigned int numVertices, unsigned int texture) :
		mOffset(offset), mNumVertices(numVertices), mTexture(texture) {}
	unsigned int mOffset;
	unsigned int mNumVertices;
	unsigned int mTexture;
};

class RenderBatch
{
public:
	RenderBatch();
	~RenderBatch();

	void Init();

	void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void End();

	void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color);
	void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color, float angle);
	void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, unsigned int texture, float depth, const ColorRGBA8& color, const Vector2& dir);

	void Render();

private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

private:
	unsigned int mVBO = 0;
	unsigned int mVAO = 0;

	GlyphSortType mSortType;

	std::vector<Glyph*> mGlyphsPtr;
	std::vector<Glyph> mGlyphs;
	std::vector<Batch> mBatches;
};