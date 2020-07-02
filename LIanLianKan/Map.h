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
const int N = 20;

/**
 * @brief 地图类
 *
 * 游戏界面引用地图类进行游戏
 */
class Map {
private:
	/**
	  * 存储配对元素的连接线.
	 */
	ConnectLine* connect_line;

	/**
	 * 存储地图中可以匹配的序列.
	 * 利用list+pair
	 */
	std::vector<std::pair<Pic*, Pic*> >matchedlist;
	std::pair<Pic*, Pic*>help;

	bool gravity;/*是否开启重力*/

	/**
	 * @brief 判断两个Pic能否匹配，并传出ConnectLine对象
	 *
	 * @param a Pic1
	 * @param b Pic2
	 * @param erase 是否要消除（传出ConnectLine对象
	 * @return true 可以匹配
	 * @return false 不能匹配
	 */
	bool canMatch(Pic* a, Pic* b, bool erase);

	Pic* getPicup(Pic* a);/*获取“上方”图标*/
	Pic* getPicdown(Pic* a);/*获取“下方”图标*/
	Pic* getPicleft(Pic* a);/*获取“左方”图标*/
	Pic* getPicright(Pic* a);/*获取“右方”图标*/

	/*获取Pic十字链路的可用Pic*/
	void getAcross(Pic* aa, std::vector<Pic*>& v, bool extend);

	/*交换map中两个图标*/
	void swap(Pic* a, Pic* b);

	/*判断图标是否可以成为路径的一部分*/
	bool canbepath(Pic* a);

	/**
	 * 更新匹配列表（全体）.
	 * 枚举所有点对，一一判断其是否能够进行匹配
	 */
	void updateMatchedlist();
public:
	/**
	 * @brief x方向图标个数
	 */
	int m;
	/**
	 * @brief y方向图标个数
	 */
	int n;

	/**
	 * @brief 存放map中的所有图标
	 */
	std::vector<Pic*>map;

	/**
	 * @brief 存放所有ConnectLine对象
	 *
	 */
	std::list<ConnectLine* > line_list;

	/**
	 * @brief Construct a new Map object
	 *
	 * @param _m x方向图标个数
	 * @param _n y方向图标个数
	 * @param totalkind 图标种类数
	 * @param gravity_ 是否开启重力模式
	 */
	Map(int _m, int _n, int totalkind, bool gravity_);

	/**
	 * @brief Destroy the Map object
	 *
	 */
	~Map();

	/**
	 * @brief Set the Connect Line object
	 *
	 * @param line_
	 */
	void setConnectLine(ConnectLine* line_);
	/**
	 * @brief Get the Connect Line object
	 *
	 * @return ConnectLine*
	 */
	ConnectLine* getConnectLine();

	/**
	 * @brief 随机排列
	 *
	 * 重新排列所有Pic的位置并生成新的MatchedList*
	 */
	void RandomOrder();

	/**
	 * @brief 判断是否能够连接
	 *
	 * 通过Matchedlist判断两个图标是否能够“连连看”
	 * @param a 图标1
	 * @param b 图标2
	 * @return true 可以匹配，并更新匹配列表
	 * @return false
	 */
	bool isMatch(Pic* a, Pic* b);

	/**
	 * @brief 判断地图中是否还能进行匹配.
	 *
	 * 通过判断matchedlist是否为空就可以知道地图中是否还能匹配
	 * @return 能否匹配
	 */
	bool anyMatch();

	/**
	 * @brief 绘画地图
	 *
	 * 处理ConnectLine绘画+地图中的每一个图标
	 */
	void draw();

	/**
	 * @brief 开启提示
	 *
	 */
	void openHelp();
	/**
	 * @brief 关闭提示
	 *
	 */
	void closeHelp();

	/**
	 * @brief 判断是否完成游戏
	 *
	 * @return true 全部消除了
	 * @return false 还有没有消除的
	 */
	bool isWin();

	/**
	 * @brief Get the First Matched Pair
	 *
	 * @return std::pair<Pic*, Pic*>
	 */
	std::pair<Pic*, Pic*> getFirstMatchedPair();

	/**
	 * @brief 判断地图是否能够点击
	 *
	 * @return true 地图准备好了，可以点击
	 * @return false 地图没有准备，不能点击
	 */
	bool getReady();

	/**
	 * @brief 返回地图中(x,y)的图标
	 *
	 * @param x 横坐标
	 * @param y 纵坐标
	 * @return Pic* 地图中(x,y)的图标
	 */
	Pic* at(int x, int y);

	/**
	 * @brief 重力效果
	 *
	 */
	void ifneeddown();
};