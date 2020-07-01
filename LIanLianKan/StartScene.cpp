#include "StartScene.h"
#include "Control.h"
#include "GameScene.h"
extern Control* now;
void StartScene::update()
{
	bgnow++;
	if (bgnow == 49)bgnow = 0;
	char* s = new char[50];
	sprintf_s(s, 50, "./Pic/bgvideo/bgvideo%02d.png", bgnow);
	now->putImage(s, 0, 0, 960, 640);
	delete[] s;
}

void StartScene::onMouse(Sint32 x, Sint32 y)
{
	now->scene = new GameScene(this, 14, 11);
}