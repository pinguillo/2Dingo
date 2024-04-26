#pragma once
#include "../Engine/Engine.h"
#include "../Engine/Includes.h"

enum GameState
{
	STARTING,
	PLAYING,
	PAUSE,
	EXITING
};

class Game
{
public:
	GameState State;

	Game();
	~Game();

	void Run();

private:
	void Startup();
	void Step(float dt);
	void Draw();

private:
	ShaderProgram mShader;
	Camera mCamera;
	Sprite mSprite;

	RenderBatch mRenderBatch;


private:
	Engine e;
	int mScreenWidth = 1280;
	int mScreenHeight = 720;
};