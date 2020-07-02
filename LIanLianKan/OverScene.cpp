#include "OverScene.h"
#include "Control.h"
#include "StartScene.h"
#include <SDL.h>
#include <SDL_image.h>


extern Control* now;
void OverScene::update() {
	bgnow++;
	if (bgnow == 49)bgnow = 0;
	char* s = new char[50];
	sprintf_s(s, 50, "./Pic/bgvideo/bgvideo%02d.png", bgnow);
	now->putImage(s, 0, 0, 960, 640);
	delete[] s;
	now->putImage(background_pic, 0, 0, 960, 640);
	now->xyprintf(300, 300, buff, 40);
	
	int i = 0;
	for (auto score : rank) {
		now->xyprintf(700, 200 + i * 30, (std::to_string(score)+"s").c_str(), 40);
		if (++i == MAX_SCORES_NUM) {
			break;
		}
	}
	
}
void OverScene::onMouse(Sint32 x, Sint32 y) {
	/*判断结束菜单的按键.*/
	if (x >= 390 && x <= 580 && y >= 520 && y <= 570) {
		/*应该回到主界面.*/
		now->scene = new StartScene();
	}
}

void OverScene::onMouseMotion(Sint32 x, Sint32 y)
{
	if (x >= 390 && x <= 580 && y >= 520 && y <= 570) {
		sprintf_s(background_pic, 50, "./Pic/endgame_stroke1.png");
	}
	else {
		sprintf_s(background_pic, 50, "./Pic/endgame.png");
	}
}