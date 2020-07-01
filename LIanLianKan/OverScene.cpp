#include "OverScene.h"
#include "Control.h"
#include "StartScene.h"
#include <SDL.h>
#include <SDL_image.h>

extern Control* now;
void OverScene::update() {
	now->putImage("./Pic/Over.png", 0, 0, 960, 640);
	now->xyprintf(300, 300, buff, 40);
}
void OverScene::onMouse(Sint32 x, Sint32 y) {
	now->scene = new StartScene();
	delete this;
}