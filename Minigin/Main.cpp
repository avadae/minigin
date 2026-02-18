#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	go->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(358, 180);
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	to->SetColor({ 255, 255, 0, 255 });
	to->SetPosition(292, 20);
	scene.Add(std::move(to));
}

SDL_AppResult SDL_AppInit(void** const appstate, int const, char** const)
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif

	*appstate = new dae::Minigin(data_location);
	load();
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* const appstate)
{
	static_cast<dae::Minigin*>(appstate)->RunOneFrame();
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* const appstate, SDL_Event* const event)
{
	return
		static_cast<dae::Minigin*>(appstate)->ProcessEvent(*event)
			? SDL_APP_CONTINUE
			: SDL_APP_SUCCESS;
}

void SDL_AppQuit(void* const appstate, SDL_AppResult const)
{
	delete static_cast<dae::Minigin*>(appstate);
}