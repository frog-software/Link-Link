#include"Control.h"
#include<SDL.h>
Control *now = nullptr;

/**
 * @brief �������
 *
 * main�������������е����
 */
int main(int argc, char *argv[])
{
    now = new Control(960, 640);
    now->mainLoop();
    delete now;
    return 0;
}