#include "StartScene.h"
#include "Control.h"
extern Control* now;
void StartScene::update()
{
	now->putImage("./Pic/Start.png", 0, 0, 960, 640);
}

void StartScene::onKey(SDL_Keycode key)
{

}

void StartScene::onMouse(Sint32 x, Sint32 y)
{
}