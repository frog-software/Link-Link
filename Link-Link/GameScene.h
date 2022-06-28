#pragma once

#include"Scene.h"
#include"Map.h"
#include"Pic.h"
#include <ctime>
#include <list>

/**
 * @brief ��Ϸҳ��
 *
 * ��Ϸ��ʽ���е����в���
 */
class GameScene : public Scene
{
    private:

        Map *map = nullptr;/*map�����*/
        Pic *last = nullptr;/*��һ��ѡ�е�ͼ��*/
        Scene *scene_last;/*��һ����������ʼ���棩*/
        int level;/*��ǰ��Ϸ�����Ĺؿ�*/
        int timelimit;/*��ǰ�ȼ���ʱ*/

        /*��ʱ�����*/

        time_t counterTime_start;
        time_t counterTime_stop;
        time_t counterTimePause_start;
        time_t counterTimePause_stop;
        time_t timer = 0;
        /*
        ʱ���ʱ��״̬
        0 = counter stopped
        1 = counter started
        2 = counter paused
        */
        int counterStatus = 0;
        /*��ʼ��ʱ*/
        void startCounter();
        /*ֹͣ��ʱ*/
        void stopCounter();
        /*��ͣ��ʱ*/
        void pauseCounter();
        /*��ȡʱ��*/
        time_t getTimer();

        /**
        *this function returns the index in map which represents the picture
        *that has benn clicked.
        *It returns **-1** if the spot that has been clicked is outside the map.
        */
        int getMousePositionOnMap(Sint32 x, Sint32 y);

        /**
         * @brief autoģʽ�Զ���
         *
         * @return true ��Ϸ�����
         * @return false ��Ϸδ���
         */
        bool autoPlay();

    public:
        /**
         * @brief Construct a new Game Scene object
         *
         * @param scene_last_ ��һ��������������
         * @param m ��ͼx����ͼ�����
         * @param n ��ͼy����ͼ�����
         * @param totalkind ͼ��������
         * @param level_ ��ǰ�ĵ�
         * @param gravity �Ƿ�������ģʽ
         */
        GameScene(Scene *scene_last_, int m, int n, int totalkind, int level_, bool gravity);

        /**
         * @brief Destroy the Game Scene object
         *
         */
        ~GameScene();

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
