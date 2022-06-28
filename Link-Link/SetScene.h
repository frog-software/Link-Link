#pragma once
#include"Scene.h"

/**
 * @brief ����ҳ��
 *
 * ����������С
 */
class SetScene : public Scene
{
    private:
        Scene *last = nullptr;/*��һ��ҳ��*/
        int count = 0;/*������*/
    public:
        /**
         * @brief Set the Scene object
         *
         * @param last_ ��Դҳ��
         */
        SetScene(Scene *last_);
        /**
         * @brief Destroy the Set Scene object
         *
         */
        ~SetScene() = default;

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