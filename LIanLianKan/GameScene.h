#pragma once

#include"Scene.h"
#include"Map.h"
#include"Pic.h"
#include <list>
class GameScene :public Scene {
private:
	Map* map = nullptr;
	Pic* last = nullptr;
	std::list<ConnectLine* > line_list;
public:
	GameScene(int m, int n);
	~GameScene();
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	int getMousePositionOnMap(Sint32 x, Sint32 y);
};
