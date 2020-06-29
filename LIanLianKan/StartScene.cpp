#include "StartScene.h"
#include "Control.h"
#include "GameScene.h"
extern Control* now;
void StartScene::update()
{
	now->putImage("./Pic/Start.png", 0, 0, 960, 640);
}


void StartScene::onMouse(Sint32 x, Sint32 y)
{
	now->scene = new GameScene(15,15);
	delete this;
}