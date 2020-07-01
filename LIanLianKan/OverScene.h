#pragma once
#include "Scene.h"
#include <stdio.h>
class OverScene :
	public Scene
{
	char buff[50];
public:
	OverScene(time_t t) {
		sprintf_s(buff, 50, "Time:%4lld", t);
	};
	void update();
	void onMouse(Sint32 x, Sint32 y);
};
