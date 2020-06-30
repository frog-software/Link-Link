/*******************************************************************
 * @file   Map-Pic.h
 * @brief  Map类和Pic类的声明
 * 在此头文件声明Map类和Pic类
 * @author FrogDar
 * @date   June 29 2020

 * @file Map.h
 * @change 拆分类，将Map和Pic类拆分为两个头文件
 * @author wht
 * @date   June 30 2020
 *********************************************************************/
#pragma once
#include<vector>
#include<list>
#include "Pic.h"
#include "ConnectLine.h"


/*地图大小上限*/
const int N = 100;

/**
 * 地图类.
 * @change 增加一个ConnectLine对象及其get函数 by wht
 * @date   June 30 2020
 */
class Map {
private:
	/**
	 * 地图大小.
	 */
	int m, n;
	/**
	 * 图片大小.
	 */



	 /**
	   * 存储配对元素的连接线.
	  */
	ConnectLine* connect_line;


	/**
	 * 存储地图中可以匹配的序列.
	 * 利用list+pair
	 */

	std::list<std::pair<Pic*, Pic*> >matchedlist;

	/**
	 * 判断a，b是否可以消除，erase表示是否要消除
	 */
	bool canMatch(Pic* a, Pic* b, bool erase);

	Pic* getPicup(Pic* a);
	Pic* getPicdown(Pic* a);
	Pic* getPicleft(Pic* a);
	Pic* getPicright(Pic* a);
public:
	/**
	 * 存储地图中的图标.
	 * 利用指针的方式
	* 排序之后，位置(x,y)对应[x*n+y]
	*/
	std::vector<Pic*>map;
	/*构建m*n的地图*/
	Map(int _m, int _n);
	/*重新更新matchedlist*/
	void updateMatchedlist();
	void updateMatchedlist(Pic*);
	/*连接线指针的get和set函数*/
	void setConnectLine(ConnectLine* line_);
	ConnectLine* getConnectLine();
	/*重新排序*/
	void RandomOrder();
	/*是否“连连看”*/
	bool isMatch(Pic* a, Pic* b);
	/*地图中是否能够连*/
	bool anyMatch();
	/*绘制地图*/
	void draw();
	/*获取Pic十字链路的可用Pic*/
	void getAcross(Pic* aa, std::vector<Pic*>& v);
};