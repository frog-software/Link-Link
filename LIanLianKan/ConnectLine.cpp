/*******************************************************************

 * @file ConnectLine.cpp
 * @brief ConnectLine类的实现文件
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

#include "ConnectLine.h"

 /**
  * @brief Construct a new Connect Line object
  * 起点和终点在同一直线上
  * @param start_ 起点图标
  * @param end_  终点图标
  */
ConnectLine::ConnectLine(Pic* start_, Pic* end_)
{
	number_of_corner = 0;
	start = start_;
	end = end_;
	corner1 = nullptr;
	corner2 = nullptr;
	geneLine_rect(start, end, 0);
}

/**
 * @brief Construct a new Connect Line object
 *  起点和终点之间拐弯一次，corner1为拐弯点
 * @param start_  起点
 * @param end_  终点
 * @param corner1_ 拐弯点1
 */
ConnectLine::ConnectLine(Pic* start_, Pic* end_, Pic* corner1_)
{
	number_of_corner = 1;
	start = start_;
	end = end_;
	corner1 = corner1_;
	corner2 = nullptr;
	geneLine_rect(start, corner1, 0);
	geneLine_rect(corner1, end, 1);
}

/**
 * @brief Construct a new Connect Line object
 * 起点和终点之间拐弯两次，corner1、2为拐弯点
 * @param start_ 起点
 * @param end_ 终点
 * @param corner1_ 拐弯点1
 * @param corner2_ 拐弯点2
 */
ConnectLine::ConnectLine(Pic* start_, Pic* end_, Pic* corner1_, Pic* corner2_)
{
	number_of_corner = 2;
	start = start_;
	end = end_;
	corner1 = corner1_;
	corner2 = corner2_;
	geneLine_rect(start, corner1, 0);
	geneLine_rect(corner1, corner2, 1);
	geneLine_rect(corner2, end, 2);
}

/**
 * @brief Destroy the Connect Line object
 * 让起点终点消失（设置为不可见
 */
ConnectLine::~ConnectLine()
{
	start->setIsVisible(false);
	end->setIsVisible(false);
}

/**
 * @brief 计算绘制矩形的绝对坐标
 * 根据输入的起终点，计算line_rect结构体里绘制矩形的绝对坐标
 * @param s 起点
 * @param e 终点
 * @param index 矩形数组的下标
 */
void ConnectLine::geneLine_rect(Pic* s, Pic* e, int index)
{
	int x1, x2, y1, y2;
	x1 = s->getX() * Pic::width + Pic::width / 2;
	y1 = s->getY() * Pic::height + Pic::height / 2;
	x2 = e->getX() * Pic::width + Pic::width / 2;
	y2 = e->getY() * Pic::height + Pic::height / 2;;
	if (x1 == x2) { //x坐标相等，线段垂直方向
		if (y1 - y2 > 0) {
			line_rect[index].x = x2;
			line_rect[index].y = y2;
			line_rect[index].w = 5;
			line_rect[index].h = y1 - y2 + 5;
		}
		else {
			line_rect[index].x = x1;
			line_rect[index].y = y1;
			line_rect[index].w = 5;
			line_rect[index].h = y2 - y1 + 5;
		}
	}
	else {//y坐标相等，线段水平方向
		if (x1 - x2 > 0) {
			line_rect[index].x = x2;
			line_rect[index].y = y2;
			line_rect[index].w = x1 - x2 + 5;
			line_rect[index].h = 5;
		}
		else {
			line_rect[index].x = x1;
			line_rect[index].y = y1;
			line_rect[index].w = x2 - x1 + 5;
			line_rect[index].h = 5;
		}
	}
}

/**
 * @brief 绘制连接线
 * line_rect内的矩形最多为3个，将他们全部渲染绘制
 * @param now 控制类
 */
void ConnectLine::drawLine(Control* now)
{
	for (auto i : line_rect) {
		SDL_SetRenderDrawColor(now->getRenderer(), 0, 74, 140, 255);
		SDL_Rect* pline = &i;
		SDL_RenderFillRect(now->getRenderer(), pline);
	}
}

/**
 * @brief 是否含有该图标
 * 判断起点或终点是否有该图标
 * @param a 判断的图标
 * @return true 有
 * @return false 没有
 */
bool ConnectLine::has(Pic* a)
{
	return start == a || end == a;
}