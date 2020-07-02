#include"Control.h"
#include<SDL.h>
Control* now = nullptr;

/**
 * @brief 程序入口
 *
 * main函数，程序运行的入口
 */
int main(int argc, char* argv[]) {
	now = new Control(960, 640);
	now->mainLoop();
	delete now;
	return 0;
}