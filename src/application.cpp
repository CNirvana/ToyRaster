#include "application.h"

bool Application::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_CreateWindowAndRenderer(mScreenWidth, mScreenHeight, 0, &mSDLWindow, &mSDLRenderer);
	mSDLTexture = SDL_CreateTexture(mSDLRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, mScreenWidth, mScreenHeight);
	mBackBuffer = new Uint32[mScreenWidth * mScreenHeight];

	mScene = std::make_unique<Scene>();
	mRenderer = std::make_unique<DefaultRenderer>(mScreenWidth, mScreenHeight);

	return true;
}

void Application::Run()
{
	SDL_Event ev;
	float lastTime = SDL_GetTicks() * 0.001f - 0.016f;
	float debugTime = SDL_GetTicks() * 0.001f;
	mCurrentTime = debugTime;

	Setup();

	while (true)
	{
		if (SDL_PollEvent(&ev) && ev.type == SDL_QUIT)
		{
			break;
		}

		mCurrentTime = SDL_GetTicks() * 0.001f;
		float dt = mCurrentTime - lastTime;
		lastTime = mCurrentTime;

		Update(dt);
		Render();
		SwapBuffer();

		if (mCurrentTime - debugTime > 1.0f)
		{
			std::cout << "FPS: " << (int)(1 / dt) << std::endl;
			debugTime = mCurrentTime;
		}
	}

	Destroy();
}

void Application::Render()
{
	mRenderer->Render(*mScene.get());
}

void Application::SwapBuffer()
{
	auto colorBuffer = mRenderer->GetFrameBuffer()->GetColorBuffer();
	auto pixels = colorBuffer->GetPixels();

	for (int32 y = 0; y < mScreenHeight; y++)
	{
		for (int32 x = 0; x < mScreenWidth; x++)
		{
			auto color = colorBuffer->GetPixel(x, y);
			Uint32 iColor = ((uint8_t)(255.0f * color.r) << 16) |
				((uint8_t)(255.0f * color.g) << 8) |
				((uint8_t)(255.0f * color.b)) & 0xffffff;

			mBackBuffer[x + (mScreenHeight - y - 1) * mScreenWidth] = iColor;
		}
	}

	SDL_UpdateTexture(mSDLTexture, NULL, mBackBuffer, mScreenWidth * sizeof(Uint32));
	SDL_RenderClear(mSDLRenderer);
	SDL_RenderCopy(mSDLRenderer, mSDLTexture, NULL, NULL);
	SDL_RenderPresent(mSDLRenderer);
}