#pragma once

/*********************************************************************
 * @file Pic.h
 * @brief Pic��������ļ�
 * @change ����࣬��Map��Pic����Ϊ����ͷ�ļ�
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

/**
 * @brief ͼ����
 *
 * �洢ÿһ��Сͼ�����Ϣ
 */
class Pic
{
    private:
        /**
         * ͼ���ڵ�ͼ�е�����.
         */
        int x, y;
        /**
         * ͼ�������.
         * 0Ϊ�ϰ���
         * �������ֶ�Ӧĳ�ֿ��������ķ���
         */
        int kind;
        /**
         * �Ƿ�ɼ�.
         * һ��ͼ�걻������Ҫ����Ϊ���ɼ�
         */
        bool isVisible;
        /**
         * ����Ƿ��б߿�.
         * ��ѡ��ʱ����Ҫ�����߿���ʾ����
         */
        bool isStroke;
    public:
        /**
         * @brief Pic��Ĺ��캯��
         *
         * ����ͼ��������������Ϣ
         * Ĭ�Ͽɼ���Ĭ���ޱ߿�
         * @param _kind ��ǰͼ������� ��0��ʾ�ϰ�
         * @param _x �ڵ�ͼ�еĵڼ���
         * @param _y �ڵ�ͼ�еĵڼ���
         */
        Pic(int _kind, int _x, int _y);

        /**
         * @brief ��ȡ������
         *
         * @return int ������
         */
        int getX() const;
        /**
         * @brief ���ú�����
         *
         * @param x ������
         */
        void setX(int x);

        /**
         * @brief ��ȡ������
         *
         * @return int ������
         */
        int getY() const;
        /**
         * @brief ����������
         *
         * @param y ������
         */
        void setY(int y);

        /**
         * @brief Get the Kind object
         *
         * @return int ͼ������
         */
        int getKind() const;

        /**
         * @brief Get the Is Visible object
         *
         * �ж��Ƿ�ɼ�
         * @return true �ɼ�
         * @return false ���ɼ�
         */
        bool getIsVisible() const;
        /**
         * @brief Set the Is Visible object
         *
         * @param isVisible �Ƿ�μ�
         */
        void setIsVisible(bool isVisible);

        /**
         * @brief Get the Is Stroke object
         *
         * �ж�ͼ���Ƿ��б߿�
         * @return true �б߿�
         * @return false �ޱ߿�
         */
        bool getIsStroke() const;
        /**
         * @brief Set the Is Stroke object
         *
         * @param isStroke �Ƿ�ӱ߿�
         */
        void setIsStroke(bool isStroke);

        /**
         * @brief Get the Valid object
         *
         * �ж�ͼ���ܷ�ѡ��
         * @return true �ܱ�ѡ��
         * @return false ���ܱ�ѡ��
         */
        bool getValid() const;

        /**
         * @brief �滭ͼ��.
         *
         * isVisibleΪfalseʱ���ɼ�
         * ����
         *   isStrokeΪtrueʱ�б߿�
         *   isStrokeΪfalseʱ�ޱ߿�
         */
        void draw();

        /**
         * @brief ����С�������.
         *
         * Ϊ�˿�������
         * \param b ��֮��Ƚϵ�ͼ��
         * \return �������С����
        */
        bool operator<(const Pic &b);
        /**
         * @brief ͼ��ľ��Կ��
         *
         */
        static int width;
        /**
         * @brief ͼ��ľ��Ը߶�
         *
         */
        static int height;
};