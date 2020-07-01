#pragma once

/*********************************************************************
 * @file Pic.h
 * @brief Pic类的声明文件
 * @change 拆分类，将Map和Pic类拆分为两个头文件
 * @author wht
 * @date   June 30 2020
 *********************************************************************/

 /**
  * 图标类.
  * 存储每一个小图标的信息
  */
class Pic {
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

	bool getValid() const;

	void draw();

	bool operator<(const Pic& b);

	static int width, height;
};