#include "Control.h"
#include "SetScene.h"
#include "GameScene.h"
extern Control* now;

void SetScene::update() {
	now->putImage("./Pic/Set/Set.png", 0, 0, 960, 640);
	now->putImage("./Pic/Set/music.png", 125, 205, 50, 50);
	now->putImage("./Pic/Set/sound.png", 125, 353, 50, 50);
	now->putImage("./Pic/Set/minus.png", 395, 275, 50, 50);
	now->putImage("./Pic/Set/plus.png", 515, 275, 50, 50);
	now->putImage("./Pic/Set/minus.png", 395, 425, 50, 50);
	now->putImage("./Pic/Set/plus.png", 515, 425, 50, 50);
	if (0.25 == now->getVolm1()) {
		now->putImage("./Pic/Set/1.png", 200, 225, 140, 15);
	}
	if (0.50 == now->getVolm1()) {
		now->putImage("./Pic/Set/1.png", 200, 225, 140, 15);
		now->putImage("./Pic/Set/2.png", 340, 225, 140, 15);
	}
	if (0.75 == now->getVolm1()) {
		now->putImage("./Pic/Set/1.png", 200, 225, 140, 15);
		now->putImage("./Pic/Set/2.png", 340, 225, 140, 15);
		now->putImage("./Pic/Set/3.png", 480, 225, 140, 15);
	}
	if (1.00 == now->getVolm1()) {
		now->putImage("./Pic/Set/1.png", 200, 225, 140, 15);
		now->putImage("./Pic/Set/2.png", 340, 225, 140, 15);
		now->putImage("./Pic/Set/3.png", 480, 225, 140, 15);
		now->putImage("./Pic/Set/4.png", 620, 225, 140, 15);
	}
	if (0.25 == now->getVolm2()) {
		now->putImage("./Pic/Set/5.png", 210, 370, 133, 17);
	}
	if (0.50 == now->getVolm2()) {
		now->putImage("./Pic/Set/5.png", 210, 370, 133, 17);
		now->putImage("./Pic/Set/6.png", 343, 370, 133, 17);
	}
	if (0.75 == now->getVolm2()) {
		now->putImage("./Pic/Set/5.png", 210, 370, 133, 17);
		now->putImage("./Pic/Set/6.png", 343, 370, 133, 17);
		now->putImage("./Pic/Set/7.png", 476, 370, 133, 17);
	}
	if (1.00 == now->getVolm2()) {
		now->putImage("./Pic/Set/5.png", 210, 370, 133, 17);
		now->putImage("./Pic/Set/6.png", 343, 370, 133, 17);
		now->putImage("./Pic/Set/7.png", 476, 370, 133, 17);
		now->putImage("./Pic/Set/8.png", 609, 370, 134, 17);
	}
}

void SetScene::onMouse(Sint32 x, Sint32 y) {
	if (x >= 395 && x <= 445 && y >= 275 && y <= 325)now->decVolume(1);
	if (x >= 515 && x <= 565 && y >= 275 && y <= 325)now->addVolume(1);
	if (x >= 395 && x <= 445 && y >= 425 && y <= 475)now->decVolume(2);
	if (x >= 515 && x <= 565 && y >= 425 && y <= 475)now->addVolume(2);
}