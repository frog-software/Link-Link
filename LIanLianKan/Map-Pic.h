/*****************************************************************//**
 * \file   Map-Pic.h
 * \brief  Map类和Pic类的声明
 * 在此头文件声明Map类和Pic类
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/
#pragma once
#include<vector>
#include<list>
/**
 * 图标类.
 * 存储每一个小图标的信息
 */
class Pic{
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
    Pic(int _kind, int _x, int _y);

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    int getKind() const;

    bool getIsVisible() const;
    void setIsVisible(bool isVisible);

    bool getIsStroke() const;
    void setIsStroke(bool isStroke);

    void draw();

    bool operator<(const Pic& b);
};

/*地图大小上限*/
const int N = 100;

/**
 * 地图类.
 */
class Map{
private:
    /**
     * 地图大小.
     */
    int m, n;
    /**
     * 存储地图中的图标.
     * 利用指针的方式
     */
    std::vector<Pic*>map;
    /**
     * 存储地图中可以匹配的序列.
     * 利用list+pair
     */
    std::list<std::pair<Pic*, Pic*> >matchedlist;
public:
    /*构建m*n的地图*/
    Map(int _m, int _n);
    /*重新排序*/
    void RandomOrder();
    /*是否“连连看”*/
    bool isMatch(Pic* a, Pic* b);
    /*地图中是否能够连*/
    bool anyMatch();
    /*绘制地图*/
    void draw();
};