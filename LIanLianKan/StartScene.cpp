#include "StartScene.h"
#include "Control.h"
#include "GameScene.h"
#include "SetScene.h"
#include <iostream>
extern Control* now;
StartScene::StartScene()
{
	sprintf_s(background_pic, 50, "./Pic/startgame.png");
}
void StartScene::update()
{
	bgnow++;
	if (bgnow == 49)bgnow = 0;
	char* s = new char[50];
	sprintf_s(s, 50, "./Pic/bgvideo/bgvideo%02d.png", bgnow);
	now->putImage(s, 0, 0, 960, 640);
	delete[] s;
	now->putImage(background_pic, 0, 0, 960, 640);
}

void StartScene::onMouse(Sint32 x, Sint32 y)
{
	/*判断开始菜单的按键.*/
	if (x >= 400 && x <= 560 && y >= 300 && y <= 350) {
		/*应该先生成选关界面.*/
		//now->scene = sence_select;
		now->scene = new GameScene(this, 14, 11);
	}
	if (x >= 400 && x <= 560 && y >= 360 && y <= 410) {
		/*应该进入设置界面.*/
		new SetScene(this);
	}
	if (x >= 400 && x <= 560 && y >= 430 && y <= 470) {
		/*应该进入关于界面.*/
		//new AboutScene(this);
		//delete this;
	}
	if (x >= 400 && x <= 560 && y >= 490 && y <= 540) {
		/*应该退出.*/
		now->setQuit(true);
	}
}

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