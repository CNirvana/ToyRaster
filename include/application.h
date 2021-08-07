#pragma once

#include "mesh.h"
#include "util.h"
#include "loader.h"
#include "renderer.h"

class Application
{
public:
	Application(const std::string& title, int screenWidth, int screenHeight)
		: mSDLWindow(nullptr), mSDLRenderer(nullptr), mSDLTexture(nullptr), mBackBuffer(nullptr),
		mTitle(title), mScreenWidth(screenWidth), mScreenHeight(screenHeight)
	{
	}
	virtual ~Application()
	{
		SAFE_DELETE_ARRAY(mBackBuffer);
	}

	Scene* GetScene() const { return mScene.get(); }
	float GetTime() const { return mCurrentTime; }

	bool Initialize();
	void Run();

	void Shutdown()
	{
		SDL_Quit();
	}

protected:
	void Render();
	void SwapBuffer();

	virtual void Setup() {}
	virtual void Update(float dt) {}
	virtual void Destroy() {}

private:
	SDL_Window* mSDLWindow;
	SDL_Renderer* mSDLRenderer;
	SDL_Texture* mSDLTexture;
	Uint32* mBackBuffer;

	int32 mScreenWidth;
	int32 mScreenHeight;
	std::string mTitle;
	float mCurrentTime = 0;

	std::unique_ptr<Scene> mScene;
	std::unique_ptr<Renderer> mRenderer;
};