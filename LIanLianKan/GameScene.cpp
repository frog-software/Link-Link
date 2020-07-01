#include "GameScene.h"
#include "Control.h"
#include "StartScene.h"
#include "SetScene.h"
#include <queue>
extern Control* now;

/**
 * @brief Construct a new Game Scene:: Game Scene object
 * 生成一个m行n列的地图
 * @param m 地图x方向图标个数
 * @param n 地图y方向图标个数
 */
GameScene::GameScene(int m, int n)
{
	map = new Map{ m,n };

	map->setConnectLine(nullptr);
}

/**
 * @brief Destroy the Game Scene:: Game Scene object
 * 
 */
GameScene::~GameScene()
{
	delete map;
}

/**
 * @brief 更新画面
 * 按顺序从底层到顶层逐一更新画面
 */
std::queue<ConnectLine* > line_queue;
void GameScene::update()
{
	now->putImage("./Pic/Game.png", 0, 0, 960, 640);

	if (map->anyMatch() == false)map->RandomOrder();
	map->draw();

	auto conline = map->getConnectLine();
	if (conline != nullptr) {
		line_queue.push(conline);
	}
	while (!line_queue.empty()) {
		auto line = line_queue.front();
		line->drawLine(now);
		line->cnt--;
		if (line->cnt == 0) {
			map->setConnectLine(nullptr);
			line_queue.pop();
		}
	}

}

/**
 * @brief 判定鼠标操作
 * 
 * @param x 鼠标点击的x
 * @param y 鼠标点击的y
 */
void GameScene::onMouse(Sint32 x, Sint32 y)
{
	/*对于图标的判断*/
	int linearMousePositionOnMap = getMousePositionOnMap(x, y);
	if (linearMousePositionOnMap >= 0 && map->map[linearMousePositionOnMap]->getValid())
	{
		if(last==nullptr){
			/*这是第一次按图标，则图标加框*/
			last = map->map[linearMousePositionOnMap];
			last->setIsStroke(true);
		}
		else if(map->isMatch(last, map->map[linearMousePositionOnMap])==false){
			/*如果无法匹配，则切换加框的图标*/
			last->setIsStroke(false);
			last = map->map[linearMousePositionOnMap];
			last->setIsStroke(true);
		}else{
			/*如果完成匹配，那么要清除last（其他操作在匹配函数中已完成*/
			last = nullptr;
		}
	//	printf("%d %d\n", map->map[linearMousePositionOnMap]->getX(), map->map[linearMousePositionOnMap]->getY());
	}

	/*功能按键的判断*/

	/*设置界面*/
	if (x >= 900 && x <= 960 && y >= 0 && y <= 50) new SetScene(this);
}

/*
*this function returns the index in map which represents the picture
*that has benn clicked.
*It returns **-1** if the spot that has been clicked is outside the map.
*/
int GameScene::getMousePositionOnMap(Sint32 x, Sint32 y)
{
	// how many pictures are there horizontally
	const int NUM_OF_HORIZONTAL_PICTURES = 16;
	// how many pictures are there vertically
	const int NUM_OF_VERTICAL_PICTURES = 13;

	// consider the map as a rectangle
	// this is the coordinate of the upper left corner
	const int MAP_START_POSOTION_X = 50;
	const int MAP_START_POSOTION_Y = 50;
	// this is the coordinate of the lower right corner
	const int MAP_END_POSOTION_X = 50 * (NUM_OF_HORIZONTAL_PICTURES);
	const int MAP_END_POSOTION_Y = 50 * (NUM_OF_VERTICAL_PICTURES);

	int ln, col;
	// return value
	int ret = -1;

	if ((x >= MAP_START_POSOTION_X)
		&& (y >= MAP_START_POSOTION_Y)
		&& (x <= MAP_END_POSOTION_X)
		&& (y <= MAP_END_POSOTION_Y))
	{
		ln = (y - MAP_START_POSOTION_Y) / Pic::height + 1; // line index
		col = (x - MAP_START_POSOTION_X) / Pic::width + 1; // column index

		// index in map to return
		ret = col * NUM_OF_VERTICAL_PICTURES + ln;
	}

	return ret;
}

