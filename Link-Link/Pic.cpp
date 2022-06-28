#pragma once

/*******************************************************************

 * @file Pic.cpp
 * @brief Pic���ʵ���ļ�
 * @change ����࣬��Map��Pic����Ϊ�����ļ�
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

#include "Pic.h"
#include "Control.h"
extern Control *now;

int Pic::width = 50;
int Pic::height = 50;

/**
 * @brief Pic��Ĺ��캯��
 *
 * ����ͼ��������������Ϣ
 * Ĭ�Ͽɼ���Ĭ���ޱ߿�
 * @param _kind ��ǰͼ������� ��0��ʾ�ϰ�
 * @param _x �ڵ�ͼ�еĵڼ���
 * @param _y �ڵ�ͼ�еĵڼ���
 */
Pic::Pic(int _kind, int _x, int _y) : x{ _x }, y{ _y }, isVisible{ true }, isStroke{ false }, kind{ _kind }
{
}

/**
 * @brief ��ȡ������
 *
 * @return int ������
 */
int Pic::getX() const
{
    return x;
}
/**
 * @brief ���ú�����
 *
 * @param x ������
 */
void Pic::setX(int x)
{
    this->x = x;
}

/**
 * @brief ��ȡ������
 *
 * @return int ������
 */
int Pic::getY() const
{
    return y;
}

/**
 * @brief ����������
 *
 * @param y ������
 */
void Pic::setY(int y)
{
    this->y = y;
}

/**
 * @brief Get the Kind object
 *
 * @return int ͼ������
 */
int Pic::getKind() const
{
    return kind;
}

/**
 * @brief Get the Is Visible object
 *
 * �ж��Ƿ�ɼ�
 * @return true �ɼ�
 * @return false ���ɼ�
 */
bool Pic::getIsVisible() const
{
    return isVisible;
}

/**
 * @brief Set the Is Visible object
 *
 * @param isVisible �Ƿ�μ�
 */
void Pic::setIsVisible(bool isVisible)
{
    this->isVisible = isVisible;
}

/**
 * @brief Get the Is Stroke object
 *
 * �ж�ͼ���Ƿ��б߿�
 * @return true �б߿�
 * @return false �ޱ߿�
 */
bool Pic::getIsStroke() const
{
    return isStroke;
}

/**
 * @brief Set the Is Stroke object
 *
 * @param isStroke �Ƿ�ӱ߿�
 */
void Pic::setIsStroke(bool isStroke)
{
    this->isStroke = isStroke;
}

/**
 * @brief Get the Valid object
 *
 * �ж�ͼ���ܷ�ѡ��
 * @return true �ܱ�ѡ��
 * @return false ���ܱ�ѡ��
 */
bool Pic::getValid() const
{
    return kind > 0 && isVisible == true;
}

/**
 * @brief �滭ͼ��.
 *
 * isVisibleΪfalseʱ���ɼ�
 * ����
 *   isStrokeΪtrueʱ�б߿�
 *   isStrokeΪfalseʱ�ޱ߿�
 */
void Pic::draw()
{
    if (this->isVisible == false)
    {
        return;
    }

    char *s = new char[100];

    if (this->isStroke == false)
    {
        sprintf_s(s, 100, "./Pic/icons/icon%d.png", kind);
    }
    else
    {
        sprintf_s(s, 100, "./Pic/icons/icon%d_.png", kind);
    }

    now->putImage(s, x * width, y * height, width, height);
    delete[] s;
}

/**
 * @brief ����С�������.
 *
 * Ϊ�˿�������
 * \param b ��֮��Ƚϵ�ͼ��
 * \return �������С����
 */
bool Pic::operator<(const Pic &b)
{
    if (this->x != b.x)
    {
        return this->x > b.x;
    }
    else
    {
        return this->y > b.y;
    }
}