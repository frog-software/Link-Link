#pragma once
#include "Scene.h"

/**
 * @brief ���ڽ���
 *
 * ��ʾ������Ա����+����ҳ��
 */
class AboutScene : public Scene
{
    private:
        Scene *last = nullptr;
        int point[12] = { 150, 1110, 1400, 2110, 2290, 3030, 3245, 3330, 3960, 3960, 4235, 4260 };
        int title[2] = { 290, 1250 };
        int count1 = 0;
        int count2 = 0;
    public:
        /**
         * @brief aboutҳ�������
         *
         */
        int about = 0;
        /**
         * @brief ����ҳ��ҳ��
         *
         */
        int page = 1;
        /**
         * @brief ��ҳ�����Ƿ������
         *
         */
        bool isDone = true;

        /**
         * @brief Construct a new About Scene object
         *
         * @param last_ ��һ����������������
         */
        AboutScene(Scene *last_);

        /**
         * @brief Destroy the About Scene object
         *
         */
        ~AboutScene() = default;

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