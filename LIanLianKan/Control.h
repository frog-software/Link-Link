/*****************************************************************//**
 * \file   Control.h
 * \brief  Control类声明
 * Control类的声明所在头文件
 *
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "Scene.h"
#include "SDL.h"
#include <map>
#include <string>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <filesystem>
namespace fs = std::filesystem;

/*to control the program*/
class Control {
private:
	int width, height;
	/*音量初始值0.5*/
	double volm1{ 0.5 }, volm2{ 0.5 };
	/*将要渲染的窗口*/
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	/*为了节约时间，提前加载所有资源*/
	std::map<std::string, SDL_Texture*>Textures;
	std::map<int, TTF_Font* >Fonts;
	std::map<std::string, Mix_Chunk*>Sounds;
public:
	/*ctor,dtor*/
	Control(int _width, int _height);
	Control();
	~Control();
	/*主循环*/
	void mainLoop();
	/*在位置x，y 以宽度 width 高度 height的方式 绘制图片path*/
	void putImage(std::string path, int x, int y, int width, int height);
	/*在channel频道播放音乐path一共cnt次，BGM为频道1，音效为频道2*/
	void playSound(int channel, std::string path, int cnt = 1);
	/*调节音量大小*/
	void addVolume(int channel);
	void decVolume(int channel);
	/*在位置xy以字号size 输出内容c*/
	void xyprintf(int x, int y, const char* c, int size);
	/*获取一个随机数*/
	int getRand();
	/*加载图片、音频*/
	void Initmypngs(fs::path strPath);
	void Initmywavs(fs::path strPath);
	SDL_Renderer* getRenderer();
	Scene* scene;
};
