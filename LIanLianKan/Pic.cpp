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
 * .Pic类的构造函数
 * 传入图标类型与坐标信息
 * 默认可见、默认无边框
 * \param _kind 当前图标的类型 （0表示障碍
 * \param _x 在地图中的第几行
 * \param _y 在地图中的第几列
 */
Pic::Pic(int _kind, int _x, int _y) :x{ _x }, y{ _y }, isVisible{ true }, isStroke{ false }, kind{ _kind }
{
}

int Pic::getX() const
{
	return x;
}

void Pic::setX(int x)
{
	this->x = x;
}

int Pic::getY() const
{
	return y;
}

void Pic::setY(int y)
{
	this->y = y;
}

int Pic::getKind() const
{
	return kind;
}

bool Pic::getIsVisible() const
{
	return isVisible;
}

void Pic::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

bool Pic::getIsStroke() const
{
	return isStroke;
}

void Pic::setIsStroke(bool isStroke)
{
	this->isStroke = isStroke;
}

bool Pic::getValid() const
{
	return kind > 0 && isVisible == true;
}

/**
 * 绘画图标.
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
 * 重载小于运算符.
 * 为了可以排序
 * \param b 与之相比较的图标
 * \return 按坐标大小排序
 */
bool Pic::operator<(const Pic& b)
{
	if (this->x != b.x)return this->x > b.x;
	else return this->y > b.y;
}