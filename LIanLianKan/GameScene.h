#pragma once

#include"Scene.h"
#include"Map-Pic.h"
class GameScene :public Scene {
private:
	Map* map = nullptr;
public:
	GameScene(int m, int n);
	~GameScene();
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	int getMousePositionOnMap(Sint32 x, Sint32 y);
};
