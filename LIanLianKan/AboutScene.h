#pragma once
#include "Scene.h"

class AboutScene :public Scene {
private:
	Scene* last = nullptr;
	int point[12] = { 150,1110,1400,2110,2290,3030,3245,3330,3960,3960,4235,4260 };
	int title[2] = { 290,1250 };
public:
	int about = 0, page = 1;
	bool isDone = true;
	AboutScene(Scene* last_);
	~AboutScene() = default;
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};