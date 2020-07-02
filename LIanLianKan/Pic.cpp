#pragma once

/*******************************************************************

 * @file Pic.cpp
 * @brief Pic类的实现文件
 * @change 拆分类，将Map和Pic类拆分为两个文件
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

#include "Pic.h"
#include "Control.h"
extern Control* now;

int Pic::width = 50;
int Pic::height = 50;

/**
 * @brief Pic类的构造函数
 *
 * 传入图标类型与坐标信息
 * 默认可见、默认无边框
 * @param _kind 当前图标的类型 （0表示障碍
 * @param _x 在地图中的第几行
 * @param _y 在地图中的第几列
 */
Pic::Pic(int _kind, int _x, int _y) :x{ _x }, y{ _y }, isVisible{ true }, isStroke{ false }, kind{ _kind }
{
}

/**
 * @brief 获取横坐标
 *
 * @return int 横坐标
 */
int Pic::getX() const
{
	return x;
}
/**
 * @brief 设置横坐标
 *
 * @param x 横坐标
 */
void Pic::setX(int x)
{
	this->x = x;
}

/**
 * @brief 获取纵坐标
 *
 * @return int 纵坐标
 */
int Pic::getY() const
{
	return y;
}

/**
 * @brief 设置纵坐标
 *
 * @param x 纵坐标
 */
void Pic::setY(int y)
{
	this->y = y;
}

/**
 * @brief Get the Kind object
 *
 * @return int 图标类型
 */
int Pic::getKind() const
{
	return kind;
}

/**
 * @brief Get the Is Visible object
 *
 * 判断是否可见
 * @return true 可见
 * @return false 不可见
 */
bool Pic::getIsVisible() const
{
	return isVisible;
}

/**
 * @brief Set the Is Visible object
 *
 * @param isVisible 是否课件
 */
void Pic::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

/**
 * @brief Get the Is Stroke object
 *
 * 判断图标是否有边框
 * @return true 有边框
 * @return false 无边框
 */
bool Pic::getIsStroke() const
{
	return isStroke;
}

/**
 * @brief Set the Is Stroke object
 *
 * @param isStroke 是否加边框
 */
void Pic::setIsStroke(bool isStroke)
{
	this->isStroke = isStroke;
}

/**
 * @brief Get the Valid object
 *
 * 判断图标能否被选中
 * @return true 能被选中
 * @return false 不能被选中
 */
bool Pic::getValid() const
{
	return kind > 0 && isVisible == true;
}

/**
 * @brief 绘画图标.
 *
 * isVisible为false时不可见
 * 否则
 *   isStroke为true时有边框
 *   isStroke为false时无边框
 */
void Pic::draw()
{
	if (this->isVisible == false)return;
	char* s = new char[100];
	if (this->isStroke == false) sprintf_s(s, 100, "./Pic/icons/icon%d.png", kind);
	else sprintf_s(s, 100, "./Pic/icons/icon%d_.png", kind);
	now->putImage(s, x * width, y * height, width, height);
	delete[] s;
}

/**
 * @brief 重载小于运算符.
 *
 * 为了可以排序
 * \param b 与之相比较的图标
 * \return 按坐标大小排序
 */
bool Pic::operator<(const Pic& b)
{
	if (this->x != b.x)return this->x > b.x;
	else return this->y > b.y;
}