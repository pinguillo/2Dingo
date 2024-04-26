#include "Game.h"

Game::Game()
{
	e.Init("Yes", mScreenWidth, mScreenHeight);
	e.SetFunctions([this]() {Startup(); }, [this](float dt) {Step(dt); }, [this]() {Draw(); });
}

Game::~Game()
{
}

void Game::Run()
{
	e.Start();
}

void Game::Startup()
{
	Logger::Debug("Game startup");

	mShader.CompileShaders("Game/Shaders/colorShading.vert", "Game/Shaders/colorShading.frag");
	mShader.AddAttribute("vertexPosition");
	mShader.AddAttribute("vertexColor");
	mShader.AddAttribute("vertexUV");
	mShader.LinkShaders();

	// Testing batch rendering for level
	mRenderBatch.Init();
	mRenderBatch.Begin();

	const int TILE_SIZE = 10;
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			glm::vec4 destRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			mRenderBatch.Draw
			(
				destRect, { 0,0,1,1 },
				ResourceManager::getTexture("Game/Textures/brick.png").id,
				0.0f, 
				{ 255,255,255,255 }
			);
		}
	}
	mRenderBatch.End();

	mSprite.init(0, 0, 10, 10, "Game/Textures/brick.png");

	mCamera.Init(mScreenWidth, mScreenHeight);
	mCamera.SetScale(10);
}

void Game::Step(float dt)
{
	Vector2 p = mCamera.getPosition();
	float scale = mCamera.getScale();

	if (e.isKeyDown(SDLK_w)) { p = Vector2(p.X, p.Y + 1.0f * dt); }
	if (e.isKeyDown(SDLK_s)) { p = Vector2(p.X, p.Y - 1.0f * dt); }
	if (e.isKeyDown(SDLK_d)) { p = Vector2(p.X + 1.0f * dt, p.Y); }
	if (e.isKeyDown(SDLK_a)) { p = Vector2(p.X - 1.0f * dt, p.Y); }

	if (e.isKeyDown(SDLK_q)) { scale -= 0.1f; }
	if (e.isKeyDown(SDLK_e)) { scale += 0.1f; }

	//Test vsync
	if (e.isKeyDown(SDLK_0)) { e.SetVSYNC(0); }
	if (e.isKeyDown(SDLK_1)) { e.SetVSYNC(1); }
	if (e.isKeyDown(SDLK_2)) { e.SetVSYNC(-1); }

	mCamera.SetScale(scale);
	mCamera.SetPosition(p);
	mCamera.Update();

	//Logger::Info("FPS: %i", e.getTime()->getFPS());
}

void Game::Draw()
{
	mShader.BindShader();

	mCamera.SendProjection(mCamera.getCameraMatrix(), mShader.getUniformLocation("projection"));

	mRenderBatch.Render();

	//mSprite.Draw(mShader.getUniformLocation("textureSampler"));

	mShader.UnbindShader();
}
