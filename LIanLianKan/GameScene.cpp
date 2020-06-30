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
	/*以下为测试画线是否正常的代码*/
	Pic* a = new Pic(1, 1, 2);
	Pic* b = new Pic(2, 2, 4);
	Pic* c1 = new Pic(3, 4, 2);
	Pic* c2 = new Pic(3, 4, 4);
	ConnectLine* testline = new ConnectLine(a, b, c1, c1);
	map->setConnectLine(testline);
	map->getConnectLine()->drawLine(now);
	/*测试结束*/
	map-> draw();
}

void GameScene::onMouse(Sint32 x, Sint32 y)
{
}