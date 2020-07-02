/*****************************************************************/ /**
 * \file   Control.cpp
 * \brief  Control类的定义
 * Control类的函数定义
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/

#include "Control.h"
#include "GameScene.h"
#include "StartScene.h"
#include <cstdlib>
#include <ctime>
#include <deque>
#include <random>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace fs = std::filesystem;
extern Control* now;
/**
 * @brief 是否开启自动模式
 */
bool hasEnabledAutoMode = false;
/**
 * @brief 自动模式的速度选择数组.
 */
int autoSpeed[] = { 20, 10, 5, 2 };
/**
 * @brief 自动模式的速度选择下标.
 */
int autoSpeedIndicator = 0;

/**
 * @brief Construct a new Control object
 *
 * 创建一个width*height大小的窗口
 * SDL的各种准备工作
 * @param _width 窗口宽度
 * @param _height 窗口高度
 */
Control::Control(int _width, int _height) : width{ _width }, height{ _height }, scene{ nullptr }
{
	/*初始化SDL环境*/
	SDL_Init(SDL_INIT_EVERYTHING);
	/*初始化窗口*/
	window = SDL_CreateWindow("LianLianKan", 100, 100, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* surface = IMG_Load("./Pic/icon.png");
	SDL_SetWindowIcon(window, surface);
	SDL_FreeSurface(surface);

	/*初始化SDL的音频拓展*/
	Mix_Init(127);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 2048);
	/*初始化SDL的字体拓展*/
	TTF_Init();

	/*初始化随机数种子*/
	std::srand((int)time(NULL));
	bgnow = 0;
}

/**
 * @brief Destroy the Control object
 *
 * 释放SDL的各项资源
 * 释放指针资源
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
 * @brief 主循环.
 *
 * 程序控制逻辑的主体部分
 */
void Control::mainLoop()
{
	/*显示“加载资源中”*/
	SDL_RenderClear(renderer);
	this->putImage("./Pic/pre.png", 0, 0, width, height);
	SDL_RenderPresent(renderer);

	/*加载程序资源文件（音频*/
	Initmywavs(fs::path{ "./Sound" });

	/*播放背景音乐*/
	this->playSound(1, "./Sound/bgm.mp3", 0);

	/*加载程序资源文件（图片*/
	Initmypngs(fs::path{ "./Pic" });

	/*初始界面为StartScene*/
	this->scene = new StartScene();

	/*用户操作的事件*/
	SDL_Event e;

	/*键盘按键缓冲队列*/
	std::deque<SDL_Keycode> keyCodeBuffer;

	/*单次刷新缓冲计数器*/
	int cnt;

	while (!quit)
	{
		/*记录当前时间（为了控制帧率*/
		Uint64 start = SDL_GetPerformanceCounter();

		/*单次刷新最多执行20个事件*/
		cnt = 20;
		while (SDL_PollEvent(&e) != 0 && --cnt)
		{
			//用户选择退出
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			/*用户按下鼠标*/
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				scene->onMouse(e.button.x, e.button.y);
			}

			/*用户移动鼠标*/
			if (e.type == SDL_MOUSEMOTION)
			{
				scene->onMouseMotion(e.motion.x, e.motion.y);
			}

			/*用户按下键盘*/
			if (e.type == SDL_KEYDOWN)
			{
				// Auto mode /////

				/*将当前按键加入缓冲队列并只保留四个按键*/
				keyCodeBuffer.push_back(e.key.keysym.sym);
				if (keyCodeBuffer.size() > 4)
					keyCodeBuffer.pop_front();

				/*如果按下的是auto，则反转自动模式*/
				if (keyCodeBuffer.size() == 4 && keyCodeBuffer[0] == SDLK_a && keyCodeBuffer[1] == SDLK_u && keyCodeBuffer[2] == SDLK_t && keyCodeBuffer[3] == SDLK_o)
				{
					hasEnabledAutoMode = !hasEnabledAutoMode;
				}

				/*如果按下的是s，调整自动模式的速度*/
				if (keyCodeBuffer.size() > 3 && keyCodeBuffer[3] == SDLK_s)
				{
					if ((++autoSpeedIndicator) >= sizeof(autoSpeed) / sizeof(int))
					{
						autoSpeedIndicator = 0;
					}
				}
			}
		}

		/*更新绘制当前场景*/
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
 * @brief 绘制一张图片.
 *
 * 在位置x，y 以宽度 width 高度 height的方式 绘制图片path
 * @param path 图片的路径
 * @param x 绘制点的横坐标
 * @param y 绘制点的纵坐标
 * @param width 需要绘制的图片宽度
 * @param height 需要绘制的图片的高度
 */
void Control::putImage(std::string path, int x, int y, int width, int height)
{
	/*如果没有画过这张图片，则加载并记忆化*/
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
 * @brief 在某频道播放音乐path共cnt次.
 *
 * 在channel频道播放音乐path一共cnt次
 * @param channel 音乐播放的频道 ，BGM为频道1，音效为频道2
 * @param path 音乐的路径
 * @param cnt 播放次数，0为背景音乐(无限次)
 */
void Control::playSound(int channel, std::string path, int cnt)
{
	Mix_PlayChannel(channel, Sounds[path], cnt - 1);
}

/**
 * @brief 增大频道的音量
 *
 * @param channel 1表示bgm频道 2表示音效频道
 */
void Control::addVolume(int channel)
{
	if (1 == channel)
	{
		volm1 += 0.25;
		if (volm1 > 1)
			volm1 = 1;
		Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
	}
	if (2 == channel)
	{
		volm2 += 0.25;
		if (volm2 > 1)
			volm2 = 1;
		Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
	}
}

/**
 * @brief 减小频道的音量
 *
 * @param channel 1表示bgm频道 2表示音效频道
 */
void Control::decVolume(int channel)
{
	if (1 == channel)
	{
		volm1 -= 0.25;
		if (volm1 < 0)
			volm1 = 0;
		Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
	}
	if (2 == channel)
	{
		volm2 -= 0.25;
		if (volm2 < 0)
			volm2 = 0;
		Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
	}
}

/**
 * @brief 获取Control类当前的Renderer.
 *
 * @return SDL_Renderer* Renderer的指针
 */
SDL_Renderer* Control::getRenderer()
{
	return renderer;
}

/**
 * @brief Get the Volm1 object
 *
 * @return double 背景音乐的音量
 */
double Control::getVolm1() const
{
	return volm1;
}

/**
 * @brief Get the Volm2 object
 *
 * @return double 音效的音量
 */
double Control::getVolm2() const
{
	return volm2;
}

/**
 * @brief Get the Quit object
 *
 * @return true 退出游戏
 * @return false 继续游戏
 */
bool Control::getQuit() const
{
	return quit;
}
/**
 * @brief Set the Quit object
 *
 * @param quit_ 更改的退出标志的状态
 */
void Control::setQuit(bool quit_)
{
	quit = quit_;
}

/**
 * @brief 获取随机数
 *
 * @return int 返回一个随机数
 */
int Control::getRand() { return std::rand(); }

/**
 * @brief 输出文字信息.
 * 在(x,y)处输出字号为size的内容c
 * @param x 横坐标
 * @param y 纵坐标
 * @param c 输出内容
 * @param size 字号大小
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
* @brief 加载图片资源

* 采用cpp17标准，递归加载
* @param strPath 加载路径
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
		else if (fs::is_regular_file(fp))
			now->putImage(fp.generic_string().c_str(), 0, 0, 100, 100);
	}
}

/**
 * @brief 加载音频资源
 *
 * 采用cpp17标准，递归加载
 * @param strPath 加载路径
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
		else if (fs::is_regular_file(fp))
		{
			Sounds[fp.generic_string()] = Mix_LoadWAV(fp.generic_string().c_str());
		}
	}
}