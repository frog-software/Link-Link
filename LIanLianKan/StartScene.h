#pragma once

#include"Scene.h"

class StartScene :public Scene {
public:
	using Scene::Scene;
	StartScene() = default;
	~StartScene() = default;
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
};
