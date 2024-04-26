#include "Engine.h"

#include "Util\Logger.h"
#include "Window.h"
#include "InputManager.h"
#include "Time.h"

#include <SDL2\SDL.h>
#include <GLEW\glew.h>

Engine::Engine()
{
	Logger::Info("Engine created");
	mWindow = new Window();
	mInputManager = new InputManager();
	mTime = new Time();
}

Engine::~Engine()
{
	SDL_Quit();
	
	//TODO: something fishy in here
	if (mWindow != nullptr)
	{
		mWindow = nullptr; // delete mWindow;
	}

	if (mInputManager != nullptr){ delete mInputManager; }
	if (mTime != nullptr) { delete mTime; }
	
	
	Logger::Info("Engine destroyed");
}

int Engine::Init(const char* windowTitle, int width, int height)
{
	if (mState != EngineState::NOT_INITIALIZED)
	{
		Logger::Fatal("Tried to call Engine::Init twice");
	}
	Logger::Info("Engine init");

	mWindowWidth = width;
	mWindowHeight = height;
	mWindow->Create(mWindowTitle, mWindowWidth, mWindowHeight, 0);

	mState = EngineState::INITIALIZED;
	Logger::Info("Engine init success");
	return 0;
}

void Engine::Start()
{
	if (mState == EngineState::NOT_INITIALIZED)
	{
		Logger::Fatal("Called Start without initializing engine");
	}
	if (mState == EngineState::RUNNING)
	{
		Logger::Fatal("Called Start twice");
	}
	Logger::Info("Engine starting");


	mStartupFunction();
	/// <summary>
	/// LOOP
	/// </summary>
	mState = EngineState::RUNNING;
	Logger::Info("Engine running");
	while (mState == EngineState::RUNNING)
	{
		mTime->FrameStart();
		processSDLEvent();
		mStepFunction(mTime->getDeltaTime());

		/// <summary>
		/// DRAW
		/// </summary>
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mDrawFunction();
		mWindow->Swap();
		mTime->frameLimit(true);
		mTime->FrameEnd();
	}
	mState = EngineState::STOPPING;
	Logger::Info("Engine stopping");
}

void Engine::Stop()
{
	mState = EngineState::STOPPING;
}

Time* Engine::getTime()
{
	return mTime;
}

void Engine::SetFunctions(std::function<void()> startupFunc, std::function<void(float)> stepFunc, std::function<void()> drawFunc)
{
	mStartupFunction = startupFunc;
	mStepFunction = stepFunc;
	mDrawFunction = drawFunc;
}

void Engine::SetStartupFunction(std::function<void()> startupFunc)
{
	mStartupFunction = startupFunc;
}

void Engine::SetStepFunction(std::function<void(float)> stepFunc)
{
	mStepFunction = stepFunc;
}

void Engine::SetDrawFunction(std::function<void()> drawFunc)
{
	mDrawFunction = drawFunc;
}

void Engine::SetTitle(const char* title)
{
	mWindow->SetTitle(title);
	Logger::Info("Seted window title to: %s", title);
}

void Engine::SetWidth(int width)
{
	mWindow->SetWidth(width);
}

void Engine::SetHeight(int height)
{
	mWindow->SetHeight(height);
}

void Engine::SetSize(int width, int height)
{
	mWindow->SetSize(width, height);
}

void Engine::SetVSYNC(int mode)
{
	mWindow->SetSwapInterval(mode);
}

bool Engine::isKeyDown(unsigned int keyID)
{
	return mInputManager->isKeyDown(keyID);
}

bool Engine::isKeyPressed(unsigned int keyID)
{
	return mInputManager->isKeyPressed(keyID);
}

Vector2 Engine::getMouseCoords() const
{
	return mInputManager->getMouseCoords();
}

void Engine::processSDLEvent()
{
	SDL_Event eve;
	while (SDL_PollEvent(&eve))
	{
		switch (eve.type)
		{
		case SDL_QUIT:
			Stop();
			break;
		case SDL_MOUSEMOTION:
			//LogDebug(std::to_string((int)eve.motion.x));
			mInputManager->SetMouseCoords(eve.motion.x, eve.motion.y);
			break;
		case SDL_KEYDOWN:
			mInputManager->PressKey(eve.key.keysym.sym);
			break;
		case SDL_KEYUP:
			mInputManager->ReleaseKey(eve.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mInputManager->PressKey(eve.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			mInputManager->ReleaseKey(eve.button.button);
			break;
		default:
			break;
		}
	}
}

void defStartup()
{
}

void defStep(float delta)
{
}

void defDraw()
{
}
