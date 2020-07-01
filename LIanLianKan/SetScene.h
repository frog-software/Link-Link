#pragma once
#include"Scene.h"

class SetScene :public Scene {
private:
	Scene* last = nullptr;
public:
	SetScene(Scene* last_);
	~SetScene() = default;
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};