/*****************************************************************//**
 * \file   Control.cpp
 * \brief  Control类的定义
 * Control类的函数定义
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/
#include "Control.h"
#include "StartScene.h"
#include "GameScene.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include <deque>
namespace fs = std::filesystem;
extern Control* now;
bool hasEnabledAutoMode = false;
int autoSpeed[4] = { 1, 5, 10, 20 };
int autoSpeedIndicator = 0;

/**
 * Control类的有参构造函数.
 * 创建一个width*height大小的窗口
 * \param _width 窗口宽度
 * \param _height 窗口高度
 */
Control::Control(int _width, int _height) :width{ _width }, height{ _height }, scene{ nullptr }
{
	/*初始化随机数种子*/
	std::srand((int)time(NULL));
	/*初始化SDL信息*/
	SDL_Init(SDL_INIT_EVERYTHING);
	/*初始化窗口信息*/
	window = SDL_CreateWindow("Link Up", 100, 100, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Mix_Init(127);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 2048);
	/*初始化SDL的字体拓展*/
	TTF_Init();
}

/**
 * Control类的无参构造函数.
 *
 */
Control::Control() : Control{ 1366, 768 }
{
}

/**
 * Control类的析构函数.
 * 处理指针问题
 *
 */
Control::~Control()
{
	for (auto i : Textures)
	{
		SDL_DestroyTexture(i.second);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();

	delete scene;
	scene = nullptr;
}

/**
 * 主循环.
 * 程序控制逻辑的主体部分
 */
void Control::mainLoop()
{
	/*加载程序资源文件（图片、音频*/
	Initmywavs(fs::path{ "./Sound" });
	Initmypngs(fs::path{ "./Pic" });

	/*初始界面为StartScene*/
	this->scene = new StartScene();

	/*用户是否选择退出*/
	bool quit = false;
	/*用户操作的事件*/
	SDL_Event e;

	std::deque<SDL_Keycode> keyCodeBuffer;

	int cnt = 0;

	while (!quit)
	{
		/*记录当前时间（为了控制帧率*/
		Uint64 start = SDL_GetPerformanceCounter();

		cnt = 0;
		while (SDL_PollEvent(&e) != 0 && ++cnt < 20)
		{
			//用户选择退出
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				scene->onMouse(e.button.x, e.button.y);
			}

			if (e.type == SDL_KEYDOWN) {
				// Auto mode /////
				keyCodeBuffer.push_back(e.key.keysym.sym);
				if (keyCodeBuffer.size() > 4)keyCodeBuffer.pop_front();
				if (keyCodeBuffer.size() == 4
					&& keyCodeBuffer[0] == SDLK_a
					&& keyCodeBuffer[1] == SDLK_u
					&& keyCodeBuffer[2] == SDLK_t
					&& keyCodeBuffer[3] == SDLK_o
					)
				{
					hasEnabledAutoMode = !hasEnabledAutoMode;
				}
				if (keyCodeBuffer.size() > 3
					&& keyCodeBuffer[3] == SDLK_s)
				{
					if ((++autoSpeedIndicator) >= sizeof(autoSpeed))
					{
						autoSpeedIndicator = 0;
					}
				}
			}
		}

		SDL_RenderClear(renderer);
		scene->update();
		SDL_RenderPresent(renderer);

		/*为控制帧率为60，手动delay剩余的时间*/
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		/*16.666f约等于60fps*/
		if (elapsedMS < 16.666f)
			SDL_Delay(static_cast<int>(floor(16.666f - elapsedMS)));
	}
}

/**
 * 获取Control类当前的Renderer.
 *
 * \return Renderer的指针
 */
SDL_Renderer* Control::getRenderer()
{
	return renderer;
}

/**
 * 绘制一张图片.
 *
 * \param path 图片的路径
 * \param x 绘制点的横坐标
 * \param y 绘制点的纵坐标
 * \param width 需要绘制的图片宽度
 * \param height 需要绘制的图片的高度
 */
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

/**
 * 播放音乐path共cnt次.
 * 只支持wav格式的音乐
 * \param channel 音乐播放的频道
 * \param path 音乐的路径
 * \param cnt 播放次数，-1为背景音乐
 */
void Control::playSound(int channel, std::string path, int cnt)
{
	Mix_PlayChannel(channel, Sounds[path], 0);
}
void Control::addVolume(int channel) {
	if (1 == channel) {
		volm1 += 0.25;
		if (volm1 > 1)volm1 = 1;
		Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
	}
	if (2 == channel) {
		volm2 += 0.25;
		if (volm2 > 1)volm2 = 1;
		Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
	}
}
void Control::decVolume(int channel) {
	if (1 == channel) {
		volm1 -= 0.25;
		if (volm1 < 0)volm1 = 0;
		Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
	}
	if (2 == channel) {
		volm2 -= 0.25;
		if (volm2 < 0)volm2 = 0;
		Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
	}
}
double Control::getVolm1() {
	return volm1;
}
double Control::getVolm2() {
	return volm2;
}
/**
 * 获取随机数.
 *
 * \return 一个随机数
 */
int Control::getRand() { return std::rand(); }

/**
 * 输出文字信息.
 * 在(x,y)处输出字号为size的内容c
 * \param x 横坐标
 * \param y 纵坐标
 * \param c 输出内容
 * \param size 字号大小
 */
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

/**
 * 加载png资源.
 * 自动递归操作，cpp17标准
 * \param strPath 加载的文件夹
 */
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

/**
 * 加载wav资源.
 * 自动递归操作，cpp17标准
 * \param strPath 加载的文件夹
 */
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