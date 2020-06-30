#pragma once
#include"Scene.h"

class SetScene :public Scene {
public:
	SetScene() = default;
	~SetScene() = default;
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
};