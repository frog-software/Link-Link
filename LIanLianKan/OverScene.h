#pragma once
#include "Scene.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

class OverScene : public Scene
{
private:
	/*动态背景的当前帧数.*/
	int bgnow = 0;
	/*暂存UI按钮图片路径的字符数组.*/
	char* background_pic = new char[50];
	/*暂存分数的字符数组.*/
	char buff[50];
	/*分数榜*/
	std::vector<int> rank;
	/* 最多存储/显示的分数记录个数 */
	const int MAX_SCORES_NUM = 5;
	Scene* last_scene;
public:
	OverScene(Scene* last_scene_, time_t t, int level);
	void update();
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};
