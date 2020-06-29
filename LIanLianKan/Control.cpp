#include "Control.h"
#include "StartScene.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <random>
#include <ctime>
#include <cstdlib>
namespace fs = std::filesystem;
extern Control* now;


Control::Control(int _width, int _height)
{
	std::srand((int)time(NULL));
	width = _width;
	height = _height;
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Link Up", 100, 100, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//Mix_Init(127);
	//Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 2048);
	TTF_Init();
	scene = nullptr;
}

Control::Control() : Control{ 1366, 768 }
{
}

Control::~Control()
{
	for (auto i : Textures)
	{
		SDL_DestroyTexture(i.second);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	//Mix_CloseAudio();
	//Mix_Quit();
	SDL_Quit();

	delete scene;
	scene = nullptr;
}

void Control::mainLoop()
{
//	Initmywavs(fs::path{ "./Sound" });
//	Initmywavs(fs::path{ "./Music" });
	Initmypngs(fs::path{ "./Pic" });

	this->scene = new StartScene();
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		Uint64 start = SDL_GetPerformanceCounter();
		if (SDL_PollEvent(&e) != 0)
		{
			//用户选择退出
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				scene->onKey(e.key.keysym.sym);
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				scene->onMouse(e.button.x, e.button.y);
			}
		}
		else
		{
			SDL_RenderClear(renderer);
			scene->update();
			SDL_RenderPresent(renderer);
		}
		//控制帧率为60
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		if (elapsedMS < 16.666f)
			SDL_Delay(floor(16.666f - elapsedMS));
	}
}
SDL_Renderer* Control::getRenderer()
{
	return renderer;
}

void Control::putImage(std::string path, int x, int y, int width, int height)
{
	if (Textures[path] == nullptr)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		Textures[path] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	auto& texture = Textures[path];
	SDL_Rect box = { x, y, width, height };
	SDL_RenderCopy(renderer, texture, NULL, &box);
}

void Control::playSound(std::string path, int cnt)
{
	Mix_PlayChannel(-1, Sounds[path], 0);
}

int Control::getRand() { return std::rand(); }

void Control::xyprintf(int x, int y, const char* c, int size = 20)
{
	if (Fonts.find(size) == Fonts.end())
	{
		Fonts[size] = TTF_OpenFont("./MyFont.ttf", size);
	}
	auto& font = Fonts[size];
	SDL_Color color = { 2, 2, 2, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, c, color);
	SDL_Rect box = { x, y, surface->w, surface->h };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &box);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void Control::Initmypngs(fs::path strPath)
{
	for (auto& fe : fs::directory_iterator(strPath))
	{
		auto fp = fe.path();
		auto fFiename = fp.filename();
		if (fs::is_directory(fe))
		{
			if (fFiename != "." && fFiename != "..")
				Initmypngs(fp);
		}
		else
			if (fs::is_regular_file(fp))
				now->putImage(fp.generic_string().c_str(), 0, 0, 100, 100);
	}
}
void Control::Initmywavs(fs::path strPath)
{
	for (auto& fe : fs::directory_iterator(strPath))
	{
		auto fp = fe.path();
		auto fFiename = fp.filename();
		if (fs::is_directory(fe))
		{
			if (fFiename != "." && fFiename != "..")
				Initmywavs(fp);
		}
		else
			if (fs::is_regular_file(fp)) {
				Sounds[fp.generic_string()] = Mix_LoadWAV(fp.generic_string().c_str());
			}
	}
}