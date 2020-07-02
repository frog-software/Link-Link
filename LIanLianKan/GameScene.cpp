#include "GameScene.h"
#include "Control.h"
#include "StartScene.h"
#include "SetScene.h"
#include "OverScene.h"

static int count = 0;
static int count_auto = 0;
extern Control* now;
extern bool hasEnabledAutoMode;
extern int autoSpeed[4];
extern int autoSpeedIndicator;

/**
 * @brief Construct a new Game Scene object
 * 
 * @param scene_last_ 上一个场景（主场景
 * @param m 地图x方向图标个数
 * @param n 地图y方向图标个数
 * @param totalkind 图标种类数
 * @param level_ 当前文档
 * @param gravity 是否开启重力模式
 */
GameScene::GameScene(Scene* scene_last_, int m, int n, int totalkind, int level_, bool gravity) :scene_last{ scene_last_ }, level{ level_ }
{
	map = new Map{ m,n ,totalkind,gravity };

	// start timer
	startCounter();

	map->setConnectLine(nullptr);
}

/**
 * @brief Destroy the Game Scene object
 * 
 */
GameScene::~GameScene()
{
	delete map;
}

/**
 * @brief 更新画面
 * 
 * 按顺序从底层到顶层逐一更新画面
 */
void GameScene::update()
{
	/*绘制画面背景图片.*/
	now->putImage("./Pic/Game.png", 0, 0, 960, 640);

	/*绘制画面按钮*/
	now->putImage("./Pic/Set/home.png", 890, 100, 50, 50);
	now->putImage("./Pic/main.png", 867, 155, 127, 37);
	now->putImage("./Pic/Set/cogwheel.png", 890, 200, 50, 50);
	now->putImage("./Pic/set.png", 883, 255, 127, 37);
	if (0 == now->pause) {
		now->putImage("./Pic/Set/pause.png", 890, 300, 50, 50);
		now->putImage("./Pic/pause.png", 883, 355, 127, 37);
	}
	if (1 == now->pause) {
		now->putImage("./Pic/Set/play.png", 890, 300, 50, 50);
		now->putImage("./Pic/play.png", 883, 355, 127, 37);
	}
	now->putImage("./Pic/Set/blub.png", 890, 400, 50, 50);
	now->putImage("./Pic/blub.png", 883, 455, 127, 37);
	now->putImage("./Pic/Set/refresh.png", 890, 500, 50, 50);
	now->putImage("./Pic/refresh.png", 883, 555, 127, 37);

	/*按钮“动画”*/
	/*按钮按下时*/
	if (count < 10 && now->click != 0) {
		if (5 == now->click)now->putImage("./Pic/Set/blub_.png", 890, 400, 50, 50);
		if (6 == now->click)now->putImage("./Pic/Set/refresh_.png", 890, 500, 50, 50);
		count++;
	}
	/*按钮恢复*/
	if (count == 10) {
		if (5 == now->click)map->closeHelp();
		now->click = 0;
		count = 0;
	}

	/*绘制图标矩阵*/
	while (map->anyMatch() == false && map->isWin() == false)
		map->RandomOrder();
	map->draw();

	// display timer
	char buff[50];
	sprintf_s(buff, 50, "%4lld", getTimer());
	now->xyprintf(870, 5, "Time", 40);
	now->xyprintf(870, 50, buff, 40);

	// Auto mode /////
	if (map->getReady() && hasEnabledAutoMode)
	{
		if (dynamic_cast<GameScene*>(now->scene)->map->isWin())
		{
			hasEnabledAutoMode = false;
		}
		if (count_auto < autoSpeed[autoSpeedIndicator]) { count_auto++; }
		else {
			count_auto = 0;
			dynamic_cast<GameScene*>(now->scene)->autoPlay();
		}
	}
	//////////////////

	/*如果完成消除，进入结束页面*/
	if (map->isWin()) {
		now->scene = new OverScene(this->scene_last, getTimer(), this->level);
		delete this;
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
	if (map->getReady() && linearMousePositionOnMap >= 0 && map->map[linearMousePositionOnMap]->getValid())
	{
		now->playSound(2, "./Sound/Touch.wav");
		if (last == nullptr) {
			/*这是第一次按图标，则图标加框*/
			last = map->map[linearMousePositionOnMap];
			last->setIsStroke(true);
		}
		else if (map->isMatch(last, map->map[linearMousePositionOnMap]) == false) {
			/*如果无法匹配，则切换加框的图标*/
			last->setIsStroke(false);
			last = map->map[linearMousePositionOnMap];
			last->setIsStroke(true);
		}
		else {
			/*如果完成匹配，那么要清除last（其他操作在匹配函数中已完成*/
			last = nullptr;
		}
		//	printf("%d %d\n", map->map[linearMousePositionOnMap]->getX(), map->map[linearMousePositionOnMap]->getY());
	}

	/*功能按键的判断*/
	if (x >= 890 && x <= 940 && y >= 100 && y <= 150) {
		now->scene = scene_last;
		delete this;
		//这里返回主菜单.
	}
	if (x >= 890 && x <= 940 && y >= 200 && y <= 250) {
		//这里进入设置界面
		new SetScene(this);
		pauseCounter();
		now->pause = 1;
	}
	if (x >= 890 && x <= 940 && y >= 300 && y <= 350) {
		now->pause = !now->pause;
		//这里是暂停按钮.
	}
	if (x >= 890 && x <= 940 && y >= 400 && y <= 450) {
		now->click = 5;
		map->openHelp();
		//这里是提示功能.
	}
	if (x >= 890 && x <= 940 && y >= 500 && y <= 550) {
		now->click = 6;
		//这里是重排功能.
		map->RandomOrder();
	}
	if (1 == now->pause) {
		this->pauseCounter();
		//这里是暂停功能.
	}
	if (0 == now->pause) {
		this->startCounter();
		//这里是取消暂停功能.
	}
}

/**
 * @brief 鼠标移动功能
 * 
 * @param x 当前鼠标的x
 * @param y 当前鼠标的y
 */
void GameScene::onMouseMotion(Sint32 x, Sint32 y)
{
	// Pass
	// by wht
}

/**
*this function returns the index in map which represents the picture
*that has benn clicked.
*It returns **-1** if the spot that has been clicked is outside the map.
*/
int GameScene::getMousePositionOnMap(Sint32 x, Sint32 y)
{
	// how many pictures are there horizontally
	const int NUM_OF_HORIZONTAL_PICTURES = map->m;
	// how many pictures are there vertically
	const int NUM_OF_VERTICAL_PICTURES = map->n;

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

/**
 * @brief auto模式自动玩
 * 
 * @return true 游戏已完成
 * @return false 游戏未完成
 */
bool GameScene::autoPlay()
{
	bool isWin = map->isWin();
	if (!isWin)
		map->isMatch(map->getFirstMatchedPair().first, map->getFirstMatchedPair().second);

	return isWin;
}

/*开始计时*/
void GameScene::startCounter()
{
	// if counter is stopped.
	if (counterStatus == 0)
	{
		timer = 0;
		counterStatus = 1;
		counterTime_start = time(NULL);
	}
	// if counter is paused.
	else if (counterStatus == 2)
	{
		counterStatus = 1;
		counterTimePause_stop = time(NULL);
		timer += counterTimePause_start - counterTimePause_stop;
	}
	return;
}

/*停止计时*/
void GameScene::stopCounter()
{
	// if counter is started.
	if (counterStatus == 1)
	{
		counterStatus = 0;
		counterTime_stop = time(NULL);
	}
	// if counter is paused.
	else if (counterStatus == 2)
	{
		counterStatus = 0;
		counterTimePause_stop = time(NULL);
		counterTime_stop = time(NULL);
		timer += counterTimePause_start - counterTimePause_stop;
	}
	return;
}

/*暂停计时*/
void GameScene::pauseCounter()
{
	// if counter is started.
	if (counterStatus == 1)
	{
		counterStatus = 2;
		counterTimePause_start = time(NULL);
	}
	return;
}

/*获取时间*/
time_t GameScene::getTimer()
{
	switch (counterStatus)
	{
	case 0: // counter stopped
		timer += counterTime_stop - counterTime_start;
		return timer;
		break;

	case 1: // counter started
		return timer + time(NULL) - counterTime_start;
		break;

	case 2: // counter paused
		return timer - counterTime_start + counterTimePause_start;
		break;

	default:
		break;
	}

	return 0;
}