#pragma once
#include "Math\Vector2.h"
#include <unordered_map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	// Updates the virtual "keyboards"
	void Update();

	// Sets the virtual key state to pressed
	void PressKey(unsigned int keyID);
	// Sets the virtual key state to released
	void ReleaseKey(unsigned int keyID);
	// Sets the virtual mouse position
	void SetMouseCoords(float x, float y);

	// Returns if the specified key is down
	bool isKeyDown(unsigned int keyID);
	// Returns if the specified key was just pressed in this frame
	bool isKeyPressed(unsigned int keyID);
	// Returns the virtual mouse position
	Vector2 getMouseCoords() const { return mMouseCoords; }

private:
	bool wasKeyDown(unsigned int keyID);
private:
	std::unordered_map<unsigned int, bool> mKeyMap;
	std::unordered_map<unsigned int, bool> mPrevKeyMap;
	Vector2 mMouseCoords;
};