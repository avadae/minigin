#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	printf("Compiled with SDL %d.%d.%d\n",
		SDL_MAJOR_VERSION,
		SDL_MINOR_VERSION,
		SDL_MICRO_VERSION);

	int version = SDL_GetVersion();
	printf("Linked with SDL %d.%d.%d\n",
		SDL_VERSIONNUM_MAJOR(version),
		SDL_VERSIONNUM_MINOR(version),
		SDL_VERSIONNUM_MICRO(version));

	printf("Compiled with SDL_image %u.%u.%u\n",
		SDL_IMAGE_MAJOR_VERSION,
		SDL_IMAGE_MINOR_VERSION,
		SDL_IMAGE_MICRO_VERSION);

	version = IMG_Version();
	printf("Linked with SDL_image %d.%d.%d\n",
		SDL_VERSIONNUM_MAJOR(version),
		SDL_VERSIONNUM_MINOR(version),
		SDL_VERSIONNUM_MICRO(version));

	printf("Compiled with SDL_ttf %u.%u.%u\n",
		SDL_TTF_MAJOR_VERSION,
		SDL_TTF_MINOR_VERSION,
		SDL_TTF_MICRO_VERSION);

	version = TTF_Version();
	printf("Linked with SDL_ttf %d.%d.%d\n",
		SDL_VERSIONNUM_MAJOR(version),
		SDL_VERSIONNUM_MINOR(version),
		SDL_VERSIONNUM_MICRO(version));

}

dae::Minigin::Minigin(const std::filesystem::path& dataPath)
{
	PrintSDLVersion();
	
	if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
	{
		SDL_Log("Renderer error: %s", SDL_GetError());
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	// todo: this update loop could use some work.
	bool doContinue = true;
	while (doContinue)
	{
		doContinue = input.ProcessInput();
		sceneManager.Update();
		renderer.Render();
	}
}
