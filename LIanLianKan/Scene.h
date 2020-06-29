#pragma once
#include<SDL_keycode.h>
class Scene {
public:
	Scene() = default;
	virtual void update() = 0;
	virtual void onKey(SDL_Keycode key) = 0;
	virtual void onMouse(Sint32 x, Sint32 y) = 0;
};
