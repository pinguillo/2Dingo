#pragma once
#include "../Math/Vector2.h"
#include <glm\mat4x4.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Init(int screenWidth, int screenHeight);

	void Update();

	void SendProjection(const glm::mat4& proj, int uniform);

	void SetPosition(const Vector2 newPosition);
	void SetScale(float newScale);

	Vector2 screenToWorld(Vector2 screenCoord);
	bool isBoxInView(const Vector2& position, const Vector2& dimentions);

	Vector2 getPosition() { return mPosition; }
	float getScale() { return mScale; }
	glm::mat4 getCameraMatrix() { return mCameraMatrix; }

private:
	int mScreenWidth, mScreenHeight;

	bool mNeedsUpdate;

	float mScale;
	Vector2 mPosition;
	glm::mat4 mCameraMatrix;

	glm::mat4 mOrthoMatrix;
};