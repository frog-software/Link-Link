#pragma once
#include <SDL_stdinc.h>
class Scene {
public:
	Scene() = default;
	virtual void update() = 0;
	virtual void onMouse(Sint32 x, Sint32 y) = 0;
};
