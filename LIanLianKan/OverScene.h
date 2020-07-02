#pragma once
#include "Scene.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

/**
 * @brief 结束页面
 *
 * 游戏结束之后进入此页面，显示排行榜等
 */
class OverScene : public Scene
{
private:
	/*暂存UI按钮图片路径的字符数组.*/
	char* background_pic = new char[50];
	/*暂存分数的字符数组.*/
	char buff[50];
	/*分数榜*/
	std::vector<int> rank;
	/* 最多存储/显示的分数记录个数 */
	const int MAX_SCORES_NUM = 5;
	/*上个场景（主菜单 */
	Scene* last_scene;
	/*是否超时*/
	bool tle;
public:
	/**
	 * @brief Construct a new Over Scene object
	 *
	 * @param last_scene_ 上个场景（主菜单
	 * @param t 关卡用时
	 * @param level 关卡编号
	 */
	OverScene(Scene* last_scene_, time_t t, int level);
	/**
	 * @brief 更新画面
	 *
	 * 按顺序从底层到顶层逐一更新画面
	 */
	void update();
	/**
	 * @brief 判定鼠标操作
	 *
	 * @param x 鼠标点击的x
	 * @param y 鼠标点击的y
	 */
	void onMouse(Sint32 x, Sint32 y) override;
	/**
	 * @brief 鼠标移动功能
	 *
	 * @param x 当前鼠标的x
	 * @param y 当前鼠标的y
	 */
	void onMouseMotion(Sint32 x, Sint32 y) override;
};
