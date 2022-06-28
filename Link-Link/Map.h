/*******************************************************************
 * @file   Map-Pic.h
 * @brief  Map���Pic�������
 * �ڴ�ͷ�ļ�����Map���Pic��
 * @author FrogDar
 * @date   June 29 2020

 * @file Map.h
 * @change ����࣬��Map��Pic����Ϊ����ͷ�ļ�
 * @author wht
 * @date   June 30 2020
 *********************************************************************/
#pragma once
#include<vector>
#include<list>
#include "Pic.h"
#include "ConnectLine.h"

/*��ͼ��С����*/
const int N = 20;

/**
 * @brief ��ͼ��
 *
 * ��Ϸ�������õ�ͼ�������Ϸ
 */
class Map
{
    private:
        /**
          * �洢���Ԫ�ص�������.
         */
        ConnectLine *connect_line;

        /**
         * �洢��ͼ�п���ƥ�������.
         * ����list+pair
         */
        std::vector<std::pair<Pic *, Pic *> >matchedlist;
        std::pair<Pic *, Pic *>help;

        bool gravity;/*�Ƿ�������*/

        /**
         * @brief �ж�����Pic�ܷ�ƥ�䣬������ConnectLine����
         *
         * @param a Pic1
         * @param b Pic2
         * @param erase �Ƿ�Ҫ����������ConnectLine����
         * @return true ����ƥ��
         * @return false ����ƥ��
         */
        bool canMatch(Pic *a, Pic *b, bool erase);

        Pic *getPicup(Pic *a);/*��ȡ���Ϸ���ͼ��*/
        Pic *getPicdown(Pic *a);/*��ȡ���·���ͼ��*/
        Pic *getPicleft(Pic *a);/*��ȡ���󷽡�ͼ��*/
        Pic *getPicright(Pic *a);/*��ȡ���ҷ���ͼ��*/

        /*��ȡPicʮ����·�Ŀ���Pic*/
        void getAcross(Pic *aa, std::vector<Pic *> &v, bool extend);

        /*����map������ͼ��*/
        void swap(Pic *a, Pic *b);

        /*�ж�ͼ���Ƿ���Գ�Ϊ·����һ����*/
        bool canbepath(Pic *a);

        /**
         * ����ƥ���б�ȫ�壩.
         * ö�����е�ԣ�һһ�ж����Ƿ��ܹ�����ƥ��
         */
        void updateMatchedlist();
    public:
        /**
         * @brief x����ͼ�����
         */
        int m;
        /**
         * @brief y����ͼ�����
         */
        int n;

        /**
         * @brief ���map�е�����ͼ��
         */
        std::vector<Pic *>map;

        /**
         * @brief �������ConnectLine����
         *
         */
        std::list<ConnectLine * > line_list;

        /**
         * @brief Construct a new Map object
         *
         * @param _m x����ͼ�����
         * @param _n y����ͼ�����
         * @param totalkind ͼ��������
         * @param gravity_ �Ƿ�������ģʽ
         */
        Map(int _m, int _n, int totalkind, bool gravity_);

        /**
         * @brief Destroy the Map object
         *
         */
        ~Map();

        /**
         * @brief Set the Connect Line object
         *
         * @param line_
         */
        void setConnectLine(ConnectLine *line_);
        /**
         * @brief Get the Connect Line object
         *
         * @return ConnectLine*
         */
        ConnectLine *getConnectLine();

        /**
         * @brief �������
         *
         * ������������Pic��λ�ò������µ�MatchedList*
         */
        void RandomOrder();

        /**
         * @brief �ж��Ƿ��ܹ�����
         *
         * ͨ��Matchedlist�ж�����ͼ���Ƿ��ܹ�����������
         * @param a ͼ��1
         * @param b ͼ��2
         * @return true ����ƥ�䣬������ƥ���б�
         * @return false
         */
        bool isMatch(Pic *a, Pic *b);

        /**
         * @brief �жϵ�ͼ���Ƿ��ܽ���ƥ��.
         *
         * ͨ���ж�matchedlist�Ƿ�Ϊ�վͿ���֪����ͼ���Ƿ���ƥ��
         * @return �ܷ�ƥ��
         */
        bool anyMatch();

        /**
         * @brief �滭��ͼ
         *
         * ����ConnectLine�滭+��ͼ�е�ÿһ��ͼ��
         */
        void draw();

        /**
         * @brief ������ʾ
         *
         */
        void openHelp();
        /**
         * @brief �ر���ʾ
         *
         */
        void closeHelp();

        /**
         * @brief �ж��Ƿ������Ϸ
         *
         * @return true ȫ��������
         * @return false ����û��������
         */
        bool isWin();

        /**
         * @brief Get the First Matched Pair
         *
         * @return std::pair<Pic*, Pic*>
         */
        std::pair<Pic *, Pic *> getFirstMatchedPair();

        /**
         * @brief �жϵ�ͼ�Ƿ��ܹ����
         *
         * @return true ��ͼ׼�����ˣ����Ե��
         * @return false ��ͼû��׼�������ܵ��
         */
        bool getReady();

        /**
         * @brief ���ص�ͼ��(x,y)��ͼ��
         *
         * @param x ������
         * @param y ������
         * @return Pic* ��ͼ��(x,y)��ͼ��
         */
        Pic *at(int x, int y);

        /**
         * @brief ����Ч��
         *
         */
        void ifneeddown();
};