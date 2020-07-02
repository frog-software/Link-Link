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

/**
 * @brief Control类控制窗口运行
 * 
 * 就像一个游戏窗口，控制本窗口的运行逻辑
 * 逻辑：mainloop函数
 */
class Control {
private:
	/*private变量*/

	/*窗体宽度*/
	int width;
	/*窗体高度*/
	int height;

	/*音量初始值0.5*/
	double volm1{ 0.5 }, volm2{ 0.5 };

	/*将要渲染的窗口*/
	SDL_Window* window = NULL;
	/*将要渲染的render*/
	SDL_Renderer* renderer = NULL;

	/*用户是否选择退出*/
	bool quit = false;

	/*记忆化Texture资源*/
	std::map<std::string, SDL_Texture*>Textures;
	/*记忆化字体资源*/
	std::map<int, TTF_Font* >Fonts;
	/*记忆化声音资源*/
	std::map<std::string, Mix_Chunk*>Sounds;

	/*private功能函数*/

	/**
	 * @brief 加载图片资源
	 *
	 * @param strPath 加载路径
	 */
	void Initmypngs(fs::path strPath);
	/**
	 * @brief 加载音频资源
	 *
	 * @param strPath 加载路径
	 */
	void Initmywavs(fs::path strPath);

public:
	/*Public变量*/

	/*用户点击的功能按键编号*/
	int click = 0;
	/*程序是否处于暂停中*/
	bool pause = false;
	/*目前已经解锁的关卡*/
	int level = 1;
	/*当前刷新的场景*/
	Scene* scene;

	/*ctor&&dtor*/

	/**
	 * @brief Construct a new Control object
	 * 创建一个width*height大小的窗口
	 * SDL的各种准备工作
	 * @param _width 窗口宽度
	 * @param _height 窗口高度
	 */
	Control(int _width, int _height);

	/**
	 * @brief Destroy the Control object
	 * 释放SDL的各项资源
	 * 释放指针资源
	 */
	~Control();

	/*功能函数*/

	/**
	* @brief 主循环.
	* 程序控制逻辑的主体部分
	*/
	void mainLoop();

	/**
	 * @brief 绘制一张图片.
	 * 在位置x，y 以宽度 width 高度 height的方式 绘制图片path
	 * @param path 图片的路径
	 * @param x 绘制点的横坐标
	 * @param y 绘制点的纵坐标
	 * @param width 需要绘制的图片宽度
	 * @param height 需要绘制的图片的高度
	 */
	void putImage(std::string path, int x, int y, int width, int height);

	/**
	 * @brief 在某频道播放音乐path共cnt次.
	 * 在channel频道播放音乐path一共cnt次
	 * @param channel 音乐播放的频道 ，BGM为频道1，音效为频道2
	 * @param path 音乐的路径
	 * @param cnt 播放次数，0为背景音乐(无限次)
	 */
	void playSound(int channel, std::string path, int cnt = 1);

	/**
	 * @brief 增大频道的音量
	 *
	 * @param channel 1表示bgm频道 2表示音效频道
	 */
	void addVolume(int channel);
	/**
	 * @brief 减小频道的音量
	 *
	 * @param channel 1表示bgm频道 2表示音效频道
	 */
	void decVolume(int channel);

	/**
	 * @brief 输出文字信息.
	 * 在(x,y)处输出字号为size的内容c
	 * @param x 横坐标
	 * @param y 纵坐标
	 * @param c 输出内容
	 * @param size 字号大小
	 */
	void xyprintf(int x, int y, const char* c, int size);

	/*getter&&setter*/

	/**
	 * @brief Get the Volm1 object
	 *
	 * @return double 背景音乐的音量
	 */
	double getVolm1() const;
	/**
	 * @brief Get the Volm2 object
	 *
	 * @return double 音效的音量
	 */
	double getVolm2() const;

	/**
	 * @brief Get the Quit object
	 *
	 * @return true 退出游戏
	 * @return false 继续游戏
	 */
	bool getQuit() const;
	/**
	 * @brief Set the Quit object
	 *
	 * @param quit_ 更改的退出标志的状态
	 */
	void setQuit(bool quit_);

	/**
	 * @brief Get the Renderer object
	 * 获取当前的Renderer
	 * @return SDL_Renderer*
	 */
	SDL_Renderer* getRenderer();

	/**
	 * @brief 获取一个随机数
	 *
	 * @return int 一个随机数
	 */
	int getRand();
};
