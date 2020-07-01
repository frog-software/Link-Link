#pragma once

#include"Scene.h"

class StartScene :public Scene {
private:
	/*动态背景的当前帧数.*/
	int bgnow = 0;
	/*暂存UI按钮图片路径的字符数组.*/
	char* background_pic = new char[50];
public:
	using Scene::Scene;
	StartScene();
	~StartScene() = default;
	void update()override;
	void onMouse(Sint32 x, Sint32 y) override;
	void onMouseMotion(Sint32 x, Sint32 y) override;
};
