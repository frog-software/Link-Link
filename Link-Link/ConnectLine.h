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

/**
 * @brief ”画线消除”类
 *
 * 将一对连连看的消除路径体现出来
 */
class ConnectLine
{
    private:

        /*拐弯点的数量*/
        int number_of_corner;
        Pic *start;/**起点*/
        Pic *end;/**终点*/
        Pic *corner1;/**拐弯点1*/
        Pic *corner2;/**拐弯点2*/

        /**连接线用矩形绘制，储存连接线的矩形信息*/
        SDL_Rect line_rect[3] { 0 };

    public:
        /**
         * @brief 显示次数倒计时
         *
         * 每次刷新的时候减一，做出动画效果
         */
        int cnt = 10;

        /**
         * @brief Construct a new Connect Line object
         *
         * 起点和终点在同一直线上
         * @param start_ 起点图标
         * @param end_  终点图标
         */
        ConnectLine(Pic *start_, Pic *end_);
        /**
         * @brief Construct a new Connect Line object
         *
         *  起点和终点之间拐弯一次，corner1为拐弯点
         * @param start_  起点
         * @param end_  终点
         * @param corner1_ 拐弯点1
         */
        ConnectLine(Pic *start_, Pic *end_, Pic *corner1_);
        /**
         * @brief Construct a new Connect Line object
         *
         * 起点和终点之间拐弯两次，corner1、2为拐弯点
         * @param start_ 起点
         * @param end_ 终点
         * @param corner1_ 拐弯点1
         * @param corner2_ 拐弯点2
         */
        ConnectLine(Pic *start_, Pic *end_, Pic *corner1_, Pic *corner2_);

        /**
         * @brief Destroy the Connect Line object
         *
         * 让起点终点消失（设置为不可见
         */
        ~ConnectLine();

        /**
         * @brief 计算绘制矩形的绝对坐标
         *
         * 根据输入的起终点，计算line_rect结构体里绘制矩形的绝对坐标
         * @param s 起点
         * @param e 终点
         * @param index 矩形数组的下标
         */
        void geneLine_rect(Pic *s, Pic *e, int index);

        /**
         * @brief 绘制连接线
         *
         * line_rect内的矩形最多为3个，将他们全部渲染绘制
         * @param now 控制类
         */
        void drawLine(Control *now);

        /**
         * @brief 是否含有该图标
         *
         * 判断起点或终点是否有该图标
         * @param a 判断的图标
         * @return true 有
         * @return false 没有
         */
        bool has(Pic *a);
};