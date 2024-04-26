#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <GLEW\glew.h>

#include "../Util/Logger.h"

Camera::Camera() :
	mScreenWidth(500),
	mScreenHeight(500),
	mOrthoMatrix(1.0f),
	mScale(1.0f),
	mPosition(0.0f, 0.0f),
	mCameraMatrix(1.0f),
	mNeedsUpdate(true)
{
}

Camera::~Camera()
{
}

void Camera::Init(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	mOrthoMatrix = glm::ortho(0.0f, (float)mScreenWidth, 0.0f, (float)mScreenHeight);
}

void Camera::Update()
{
	if (mNeedsUpdate)
	{
		glm::vec3 translate(-mPosition.X + mScreenWidth / 2.0f, -mPosition.Y + mScreenHeight / 2.0f, 0.0f);
		mCameraMatrix = glm::translate(mOrthoMatrix, translate);

		glm::vec3 scale(mScale, mScale, 0.0f);
		mCameraMatrix = glm::scale(glm::mat4(1.0f), scale) * mCameraMatrix;

		mNeedsUpdate = false;
	}
}

void Camera::SendProjection(const glm::mat4& proj, int uniform)
{
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &proj[0][0]);
}

void Camera::SetPosition(const Vector2 newPosition)
{
	mPosition = newPosition;
	mNeedsUpdate = true;
}

void Camera::SetScale(float newScale)
{
	mScale = newScale;
	mNeedsUpdate = true;
}

Vector2 Camera::screenToWorld(Vector2 screenCoord)
{
	screenCoord.Y = mScreenHeight - screenCoord.Y;
	screenCoord -= Vector2(mScreenWidth * 0.5, mScreenHeight * 0.5);
	screenCoord /= mScale;
	screenCoord += mPosition;
	return screenCoord;
}

bool Camera::isBoxInView(const Vector2& position, const Vector2& dimentions)
{
	Vector2 scaledScreenDim = Vector2(mScreenWidth, mScreenHeight) / mScale;

	const float MIN_DISTANCE_X = dimentions.X / 2.0f + scaledScreenDim.X / 2.0f;
	const float MIN_DISTANCE_Y = dimentions.Y / 2.0f + scaledScreenDim.Y / 2.0f;

	Vector2 centerPos = position + dimentions / 2.0f;
	Vector2 distVec = centerPos - mPosition;

	float xDepth = MIN_DISTANCE_X - abs(distVec.X);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.Y);

	if (xDepth > 0 && yDepth > 0)
	{
		return true;
	}
	return false;
}
