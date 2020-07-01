/*******************************************************************
 * @file   ConnectLine.h
 * @brief  ConnectLine类声明
 * ConnectLine类的声明所在头文件
 * 用于生成和绘制两个配对元素间的连接线
 * @author wht
 * @date   June 30 2020
**********************************************************************/
#pragma once
#include "Pic.h"
#include "Control.h"

class ConnectLine {
private:
	/*拐弯点的数量*/
	int number_of_corner;
	/*拐弯点的Pic对象*/
	Pic* start;
	Pic* end;
	Pic* corner1;
	Pic* corner2;
	/*连接线用矩形绘制，储存连接线的矩形信息*/
	SDL_Rect line_rect[3]{ 0 };
	/*倒计时*/

public:
	/*三个重载函数，根据参数个数确定连接线数量*/
	ConnectLine();
	ConnectLine(Pic* start_, Pic* end_); //起点和终点在同一直线上
	ConnectLine(Pic* start_, Pic* end_, Pic* corner1_);  //起点和终点之间拐弯一次，corner1为拐弯点
	ConnectLine(Pic* start_, Pic* end_, Pic* corner1_, Pic* corner2_); //起点和终点之间拐弯两次，corner1、2为拐弯点
	~ConnectLine();
	void geneLine_rect(Pic* s, Pic* e, int index);
	void drawLine(Control* now);
	bool has(Pic* a);
	int cnt = 5;
};