#pragma once
#include "Control.h"
/**
 * @brief ѡ��ҳ��
 *
 * �����ؿ���ѡ��
 */
class SelectScene : public Scene
{
    private:
        Scene *last = nullptr;
        int select = 0;
    public:
        /**
         * @brief Construct a new Select Scene object
         *
         * @param last_ �ϸ�������������
         */
        SelectScene(Scene *last_);
        /**
         * @brief Destroy the Select Scene object
         *
         */
        ~SelectScene() = default;

        /**
         * @brief ���»���
         *
         * ��˳��ӵײ㵽������һ���»���
         */
        void update()override;
        /**
         * @brief �ж�������
         *
         * �����һ��
         * @param x �������x
         * @param y �������y
         */
        void onMouse(Sint32 x, Sint32 y) override;
        /**
         * @brief ����ƶ�����
         *
         * �ж��ƶ�����һ���Ϸ�
         * @param x ��ǰ����x
         * @param y ��ǰ����y
         */
        void onMouseMotion(Sint32 x, Sint32 y) override;
};
