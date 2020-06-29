#include "GameScene.h"
#include "Control.h"
extern Control* now;
GameScene::GameScene(int m, int n)
{
	map = new Map{ m,n };
}

GameScene::~GameScene()
{
	delete map;
}

void GameScene::update()
{
	now->putImage("./Pic/Game.png", 0, 0, 960, 640);
	map->draw();
}

void GameScene::onMouse(Sint32 x, Sint32 y)
{
}
