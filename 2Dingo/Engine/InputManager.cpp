#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	for (auto& it : mKeyMap)
	{
		mPrevKeyMap[it.first] = it.second;
	}
}

void InputManager::PressKey(unsigned int keyID)
{
	mKeyMap[keyID] = true;
}

void InputManager::ReleaseKey(unsigned int keyID)
{
	mKeyMap[keyID] = false;
}

void InputManager::SetMouseCoords(float x, float y)
{
	mMouseCoords = { x,y };
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = mKeyMap.find(keyID);
	if (it != mKeyMap.end())
	{
		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	if (isKeyDown(keyID) && !wasKeyDown(keyID))
	{
		return true;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = mPrevKeyMap.find(keyID);
	if (it != mPrevKeyMap.end())
	{
		return it->second;
	}
	return false;
}
