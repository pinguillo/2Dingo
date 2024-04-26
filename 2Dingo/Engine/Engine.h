#pragma once
#include <functional>
#include "Math\Vector2.h"

enum class EngineState
{
	NOT_INITIALIZED,
	INITIALIZED,
	STARTING,
	RUNNING,
	STOPPING
};

// Default functions
void defStartup();
void defStep(float delta);
void defDraw();

class Window;
class InputManager;
class Time;
class Engine
{
public:
	Engine();
	~Engine();
	
	// Inits the full engine, should always be called first
	int Init(const char* windowTitle, int width, int height);
	// Starts the engine loop
	void Start();
	// Stops the engine
	void Stop();

	Time* getTime();

//////////////////////////////////////////////////////////////
/////////////////////////Functionals//////////////////////////
//////////////////////////////////////////////////////////////
public: //Functionals -- function callbacks for the game
	void SetFunctions(std::function<void()> startupFunc = defStartup, std::function<void(float)> stepFunc = defStep, std::function<void()> drawFunc = defDraw);
	void SetStartupFunction(std::function<void()> startupFunc = defStartup);
	void SetStepFunction(std::function<void(float)> stepFunc = defStep);
	void SetDrawFunction(std::function<void()> drawFunc = defDraw);

private:
	std::function<void()> mStartupFunction;
	std::function<void(float)> mStepFunction;
	std::function<void()> mDrawFunction;
//////////////////////////////////////////////////////////////
////////////////////////////Window////////////////////////////
//////////////////////////////////////////////////////////////
public: //Window stuff
	void SetTitle(const char* title);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetSize(int width, int height);
	//0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync
	void SetVSYNC(int mode);

	int getWidth() { return mWindowWidth; }
	int getHeight() { return mWindowHeight; }
private:
	const char* mWindowTitle = "Title";
	int mWindowWidth = 640;
	int mWindowHeight = 480;
//////////////////////////////////////////////////////////////
////////////////////////////Input/////////////////////////////
//////////////////////////////////////////////////////////////
public:	//Input
	bool isKeyDown(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
	Vector2 getMouseCoords() const;

private: //Engine
	void processSDLEvent();

private:
	EngineState mState = EngineState::NOT_INITIALIZED;
	Window* mWindow;
	InputManager* mInputManager;
	Time* mTime;
};