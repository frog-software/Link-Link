#pragma once
#include "Scene.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

/**
 * @brief ����ҳ��
 *
 * ��Ϸ����֮������ҳ�棬��ʾ���а��
 */
class OverScene : public Scene
{
    private:
        /*�ݴ�UI��ťͼƬ·�����ַ�����.*/
        char *background_pic = new char[50];
        /*�ݴ�������ַ�����.*/
        char buff[50];
        /*������*/
        std::vector<time_t> rank;
        /* ���洢/��ʾ�ķ�����¼���� */
        const int MAX_SCORES_NUM = 5;
        /*�ϸ����������˵� */
        Scene *last_scene;
        /*�Ƿ�ʱ*/
        bool tle;
    public:
        /**
         * @brief Construct a new Over Scene object
         *
         * @param last_scene_ �ϸ����������˵�
         * @param t �ؿ���ʱ
         * @param level �ؿ����
         */
        OverScene(Scene *last_scene_, time_t t, int level);
        /**
         * @brief ���»���
         *
         * ��˳��ӵײ㵽������һ���»���
         */
        void update();
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
