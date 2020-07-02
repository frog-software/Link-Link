#include "StartScene.h"
#include "Control.h"
#include "GameScene.h"
#include "SetScene.h"
#include "SelectScene.h"
#include "AboutScene.h"
#include <iostream>

extern Control* now;

/**
 * @brief Construct a new Start Scene object
 *
 */
StartScene::StartScene()
{
	sprintf_s(background_pic, 50, "./Pic/startgame.png");
}

/**
 * @brief 更新画面
 *
 * 按顺序从底层到顶层逐一更新画面
 */
void StartScene::update()
{
	/*动态背景*/
	now->bgnow++;
	if (now->bgnow == 49)now->bgnow = 0;
	char* s = new char[50];
	sprintf_s(s, 50, "./Pic/bgvideo/bgvideo%02d.png", now->bgnow);
	now->putImage(s, 0, 0, 960, 640);
	delete[] s;

	/*绘画菜单*/
	now->putImage(background_pic, 0, 0, 960, 640);
}

/**
 * @brief 判定鼠标操作
 *
 * @param x 鼠标点击的x
 * @param y 鼠标点击的y
 */
void StartScene::onMouse(Sint32 x, Sint32 y)
{
	/*判断开始菜单的按键.*/
	if (x >= 400 && x <= 560 && y >= 300 && y <= 350) {
		/*应该先生成选关界面.*/
		//now->scene = sence_select;
		now->scene = new SelectScene(this);
	}
	if (x >= 400 && x <= 560 && y >= 360 && y <= 410) {
		/*应该进入设置界面.*/
		new SetScene(this);
	}
	if (x >= 400 && x <= 560 && y >= 430 && y <= 470) {
		/*应该进入关于界面.*/
		now->scene = new AboutScene(this);
	}
	if (x >= 400 && x <= 560 && y >= 490 && y <= 540) {
		/*应该退出.*/
		now->setQuit(true);
	}
}

/**
 * @brief 鼠标移动功能
 *
 * @param x 当前鼠标的x
 * @param y 当前鼠标的y
 */
void StartScene::onMouseMotion(Sint32 x, Sint32 y)
{
	/*判断鼠标位置显示对应的按钮图片.*/
	if (x >= 400 && x <= 560 && y >= 300 && y <= 350) {
		/*开始游戏按钮.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke1.png");
	}
	else if (x >= 400 && x <= 560 && y >= 360 && y <= 410) {
		/*设置按钮.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke2.png");
	}
	else if (x >= 400 && x <= 560 && y >= 430 && y <= 470) {
		/*关于按钮.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke3.png");
	}
	else if (x >= 400 && x <= 560 && y >= 490 && y <= 540) {
		/*退出按钮.*/
		sprintf_s(background_pic, 50, "./Pic/startgame_stroke4.png");
	}
	else {
		/*鼠标在其他位置，不显示按钮.*/
		sprintf_s(background_pic, 50, "./Pic/startgame.png");
	}
}