/*******************************************************************
 * @file   ConnectLine.h
 * @brief  ConnectLine������
 * ConnectLine�����������ͷ�ļ�
 * �������ɺͻ����������Ԫ�ؼ��������
 * @author wht
 * @date   June 30 2020
**********************************************************************/
#pragma once
#include "Pic.h"
#include "Control.h"

/**
 * @brief ��������������
 *
 * ��һ��������������·�����ֳ���
 */
class ConnectLine
{
    private:

        /*����������*/
        int number_of_corner;
        Pic *start;/**���*/
        Pic *end;/**�յ�*/
        Pic *corner1;/**�����1*/
        Pic *corner2;/**�����2*/

        /**�������þ��λ��ƣ����������ߵľ�����Ϣ*/
        SDL_Rect line_rect[3] { 0 };

    public:
        /**
         * @brief ��ʾ��������ʱ
         *
         * ÿ��ˢ�µ�ʱ���һ����������Ч��
         */
        int cnt = 10;

        /**
         * @brief Construct a new Connect Line object
         *
         * �����յ���ͬһֱ����
         * @param start_ ���ͼ��
         * @param end_  �յ�ͼ��
         */
        ConnectLine(Pic *start_, Pic *end_);
        /**
         * @brief Construct a new Connect Line object
         *
         *  �����յ�֮�����һ�Σ�corner1Ϊ�����
         * @param start_  ���
         * @param end_  �յ�
         * @param corner1_ �����1
         */
        ConnectLine(Pic *start_, Pic *end_, Pic *corner1_);
        /**
         * @brief Construct a new Connect Line object
         *
         * �����յ�֮��������Σ�corner1��2Ϊ�����
         * @param start_ ���
         * @param end_ �յ�
         * @param corner1_ �����1
         * @param corner2_ �����2
         */
        ConnectLine(Pic *start_, Pic *end_, Pic *corner1_, Pic *corner2_);

        /**
         * @brief Destroy the Connect Line object
         *
         * ������յ���ʧ������Ϊ���ɼ�
         */
        ~ConnectLine();

        /**
         * @brief ������ƾ��εľ�������
         *
         * ������������յ㣬����line_rect�ṹ������ƾ��εľ�������
         * @param s ���
         * @param e �յ�
         * @param index ����������±�
         */
        void geneLine_rect(Pic *s, Pic *e, int index);

        /**
         * @brief ����������
         *
         * line_rect�ڵľ������Ϊ3����������ȫ����Ⱦ����
         * @param now ������
         */
        void drawLine(Control *now);

        /**
         * @brief �Ƿ��и�ͼ��
         *
         * �ж������յ��Ƿ��и�ͼ��
         * @param a �жϵ�ͼ��
         * @return true ��
         * @return false û��
         */
        bool has(Pic *a);
};