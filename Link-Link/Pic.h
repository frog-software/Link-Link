#pragma once

/*********************************************************************
 * @file Pic.h
 * @brief Pic类的声明文件
 * @change 拆分类，将Map和Pic类拆分为两个头文件
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

/**
 * @brief 图标类
 *
 * 存储每一个小图标的信息
 */
class Pic
{
    private:
        /**
         * 图标在地图中的坐标.
         */
        int x, y;
        /**
         * 图标的类型.
         * 0为障碍物
         * 其他数字对应某种可以消除的方块
         */
        int kind;
        /**
         * 是否可见.
         * 一对图标被消除后要设置为不可见
         */
        bool isVisible;
        /**
         * 外边是否有边框.
         * 被选中时，需要开启边框以示他人
         */
        bool isStroke;
    public:
        /**
         * @brief Pic类的构造函数
         *
         * 传入图标类型与坐标信息
         * 默认可见、默认无边框
         * @param _kind 当前图标的类型 （0表示障碍
         * @param _x 在地图中的第几行
         * @param _y 在地图中的第几列
         */
        Pic(int _kind, int _x, int _y);

        /**
         * @brief 获取横坐标
         *
         * @return int 横坐标
         */
        int getX() const;
        /**
         * @brief 设置横坐标
         *
         * @param x 横坐标
         */
        void setX(int x);

        /**
         * @brief 获取纵坐标
         *
         * @return int 纵坐标
         */
        int getY() const;
        /**
         * @brief 设置纵坐标
         *
         * @param y 纵坐标
         */
        void setY(int y);

        /**
         * @brief Get the Kind object
         *
         * @return int 图标类型
         */
        int getKind() const;

        /**
         * @brief Get the Is Visible object
         *
         * 判断是否可见
         * @return true 可见
         * @return false 不可见
         */
        bool getIsVisible() const;
        /**
         * @brief Set the Is Visible object
         *
         * @param isVisible 是否课件
         */
        void setIsVisible(bool isVisible);

        /**
         * @brief Get the Is Stroke object
         *
         * 判断图标是否有边框
         * @return true 有边框
         * @return false 无边框
         */
        bool getIsStroke() const;
        /**
         * @brief Set the Is Stroke object
         *
         * @param isStroke 是否加边框
         */
        void setIsStroke(bool isStroke);

        /**
         * @brief Get the Valid object
         *
         * 判断图标能否被选中
         * @return true 能被选中
         * @return false 不能被选中
         */
        bool getValid() const;

        /**
         * @brief 绘画图标.
         *
         * isVisible为false时不可见
         * 否则
         *   isStroke为true时有边框
         *   isStroke为false时无边框
         */
        void draw();

        /**
         * @brief 重载小于运算符.
         *
         * 为了可以排序
         * \param b 与之相比较的图标
         * \return 按坐标大小排序
        */
        bool operator<(const Pic &b);
        /**
         * @brief 图标的绝对宽度
         *
         */
        static int width;
        /**
         * @brief 图标的绝对高度
         *
         */
        static int height;
};