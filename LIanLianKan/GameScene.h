#pragma once

#include"Scene.h"
#include"Map.h"
#include"Pic.h"
#include <ctime>
#include <list>
#include <Windows.h>

class GameScene :public Scene {
private:
	Map* map = nullptr;
	Pic* last = nullptr;
	Scene* scene_last;

	time_t counterTime_start;
	time_t counterTime_stop;
	time_t counterTimePause_start;
	time_t counterTimePause_stop;
	time_t timer = 0;
	/*
	0 = counter stopped
	1 = counter started
	2 = counter paused
	*/
	int counterStatus = 0;

	std::list<ConnectLine* > line_list;

public:
	GameScene(Scene* scene_last_, int m, int n);
	~GameScene();
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	int getMousePositionOnMap(Sint32 x, Sint32 y);
	bool autoPlay();
	void startCounter();
	void stopCounter();
	void pauseCounter();
	time_t getTimer();
};
