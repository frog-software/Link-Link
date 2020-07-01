#pragma once
#include "Scene.h"
#include <stdio.h>
class OverScene :
	public Scene
{
private:
	/*动态背景的当前帧数.*/
	int bgnow = 0;
	/*暂存UI按钮图片路径的字符数组.*/
	char* background_pic = new char[50];
	/*暂存分数的字符数组.*/
	char buff[50];
public:
	OverScene(time_t t) {
		sprintf_s(buff, 50, "%4llds", t);
		sprintf_s(background_pic, 50, "./Pic/endgame.png");
	};
	void update();
	void onMouse(Sint32 x, Sint32 y);
	void onMouseMotion(Sint32 x, Sint32 y);
};
