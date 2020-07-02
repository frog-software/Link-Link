#pragma once
#include "Control.h"

class SelectScene :public Scene {
private:
	Scene* last = nullptr;
	int select = 0;
public:
	SelectScene(Scene* last_);
	~SelectScene() = default;
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};
