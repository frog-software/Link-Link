#pragma once
#include <SDL_stdinc.h>
/**
 * @brief ҳ����ĳ�����
 *
 * ���е�Scene���̳��ڴ�
 */
class Scene
{
    public:
        /**
         * @brief Construct a new Scene object
         *
         */
        Scene() = default;
        /**
         * @brief ���»���
         *
         * ��˳��ӵײ㵽������һ���»���
         */
        virtual void update() = 0;
        /**
         * @brief �ж�������
         *
         * @param x �������x
         * @param y �������y
         */
        virtual void onMouse(Sint32 x, Sint32 y) = 0;
        /**
         * @brief ����ƶ�����
         *
         * @param x ��ǰ����x
         * @param y ��ǰ����y
         */
        virtual void onMouseMotion(Sint32 x, Sint32 y) = 0;
};
