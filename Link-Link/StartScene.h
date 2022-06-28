#pragma once

#include"Scene.h"

/**
 * @brief ��ʼҳ��
 *
 * ������Ϸ�����
 */
class StartScene : public Scene
{
    private:
        /*�ݴ�UI��ťͼƬ·�����ַ�����.*/
        char *background_pic = new char[50];
    public:
        /**
         * @brief Construct a new Start Scene object
         *
         */
        StartScene();
        /**
         * @brief Destroy the Start Scene object
         *
         */
        ~StartScene() = default;

        /**
         * @brief ���»���
         *
         * ��˳��ӵײ㵽������һ���»���
         */
        void update()override;
        /**
         * @brief �ж�������
         *
         * @param x �������x
         * @param y �������y
         */
        void onMouse(Sint32 x, Sint32 y) override;
        /**
         * @brief ����ƶ�����
         *
         * @param x ��ǰ����x
         * @param y ��ǰ����y
         */
        void onMouseMotion(Sint32 x, Sint32 y) override;
};
