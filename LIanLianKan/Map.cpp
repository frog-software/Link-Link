/*****************************************************************//**
 * \file   Map.cpp
 * \brief  Map类定义文件
 * Map类和Pic类中各个成员函数的实现
 * \author FrogDar
 * @change 拆分Map和Pic类 by wht
 * \date   June 30 2020
 *********************************************************************/

#include "Map.h"
#include "Control.h"
#include <algorithm>
extern Control* now;

void Map::getAcross(Pic* aa, std::vector<Pic*>& v, bool extend = false) {
	v.push_back(aa);
	Pic* a = nullptr;
	a = aa;
	while (getPicup(a) != nullptr && getPicup(a)->getIsVisible() == false) {
		a = getPicup(a);
		v.push_back(a);
	}
	//if(extend && getPicup(a)!=nullptr&&)
	a = aa;
	while (getPicdown(a) != nullptr && getPicdown(a)->getIsVisible() == false) {
		a = getPicdown(a);
		v.push_back(a);
	}
	a = aa;
	while (getPicleft(a) != nullptr && getPicleft(a)->getIsVisible() == false) {
		a = getPicleft(a);
		v.push_back(a);
	}
	a = aa;
	while (getPicright(a) != nullptr && getPicright(a)->getIsVisible() == false) {
		a = getPicright(a);
		v.push_back(a);
	}
}

/**
 * @brief 判断两个Pic能否匹配，并传出ConnectLine对象
 *
 * @param a Pic1
 * @param b Pic2
 * @param erase 是否要消除（传出ConnectLine对象
 * @return true 可以匹配
 * @return false 不能匹配
 */
bool Map::canMatch(Pic* a, Pic* b, bool erase)
{
	/*测试代码： 如果出现nullptr说明传入代码有问题*/
	if (a == nullptr || b == nullptr)
	{
		printf("出现nullptr\n");
		return false;
	}
	/*如果图标是无效的，显然无法匹配*/
	if (a->getValid() == false || b->getValid() == false)
		return false;
	/*如果图标不是同一种显然不匹配*/
	if (a->getKind() != b->getKind())
		return false;
	/*如果图标是同一个，也不匹配*/
	if (a == b)return false;

	/*获取以a、b为源点的“十字架”上的图标*/
	std::vector<Pic*>access_a;
	std::vector<Pic*>access_b;
	getAcross(a, access_a);
	getAcross(b, access_b);

	/*两个十字架直接相交，0或1个拐弯*/
	for (auto i : access_a)
		for (auto j : access_b)
			if (i == j) {
				if (erase)
					connect_line = new ConnectLine{ a,b,i };
				return true;
			}

	/*两个十字架中间通过辅助线相交，两个拐弯*/
	for (auto i : access_a)
		for (auto j : access_b)
			/*x相等，画一条直线*/
			if (i->getX() == j->getX()) {
				Pic* begin; Pic* end;
				if (i->getY() < j->getY()) {
					begin = i; end = j;
				}
				else {
					begin = j; end = i;
				}
				bool flag = true;
				do {
					begin = getPicright(begin);
					if (begin != end && begin->getIsVisible() == true) {
						flag = false;
						break;
					}
				} while (begin != end);
				if (flag == true) {
					if (erase)
						connect_line = new ConnectLine{ a,b,i,j };
					return true;
				}
			}
	/*y相等，画一条直线*/
			else if (i->getY() == j->getY()) {
				Pic* begin; Pic* end;
				if (i->getX() < j->getX()) {
					begin = i; end = j;
				}
				else {
					begin = j; end = i;
				}
				bool flag = true;
				do {
					begin = getPicdown(begin);
					if (begin != end && begin->getIsVisible() == true) {
						flag = false;
						break;
					}
				} while (begin != end);
				if (flag == true) {
					if (erase)
						connect_line = new ConnectLine{ a,b,i,j };
					return true;
				}
			}

	/*没有找到匹配*/
	return false;
}

/**
 * 地图类的构造函数
 * 生成一个m行n列的地图
 * \param _m  地图行数
 * \param _n  地图列数
 */
Map::Map(int _m, int _n) :m{ _m + 2 }, n{ _n + 2 }
{
	/*
	每种图形需要成对出现
	所以利用正数变负数，负数变新的正数的方法
	实现成对出现
	*/
	int t{ 0 };
	for (int i = 1; i <= _m; i++)
		for (int j = 1; j <= _n; j++) {
			if (t > 0)t = -t;
			else t = now->getRand() % 20 + 1;
			map.push_back(new Pic{ abs(t),i,j });
		}
	/*生成周围一圈不存在的“哨兵”*/
	for (int i = 0; i < m; i++) {
		map.push_back(new Pic{ -1,i,0 });
		map.back()->setIsVisible(false);
	}
	for (int i = 0; i < m; i++) {
		map.push_back(new Pic{ -1,i,_n + 1 });
		map.back()->setIsVisible(false);
	}
	for (int i = 1; i < n - 1; i++) {
		map.push_back(new Pic{ -1,0,i });
		map.back()->setIsVisible(false);
	}
	for (int i = 1; i < n - 1; i++) {
		map.push_back(new Pic{ -1,_m + 1,i });
		map.back()->setIsVisible(false);
	}
	for (unsigned int i = 0; i < map.size(); i++)
		for (unsigned int j = 0; j < map.size(); j++)
			if ((*map[j]) < (*map[i]))
				std::swap(map[i], map[j]);

	RandomOrder();
}

Map::~Map()
{
	for (auto i : map)
		delete i;
}

/**
 * 更新匹配列表（全体）.
 * 枚举所有点对，一一判断其是否能够进行匹配
 */
void Map::updateMatchedlist()
{
	matchedlist.clear();
	for (unsigned int i = 0; i < map.size(); i++)
		if (map[i]->getValid())
			for (unsigned int j = i + 1; j < map.size(); j++)
				if (map[j]->getValid())
					if (canMatch(map[i], map[j], false))
						matchedlist.push_back(std::pair<Pic*, Pic*>{map[i], map[j]});
	sort(matchedlist.begin(), matchedlist.end());
	matchedlist.erase(unique(matchedlist.begin(), matchedlist.end()), matchedlist.end());
	/*	for (auto i : matchedlist)
			printf("%d %d %d %d\n", i.first->getX(), i.first->getY(), i.second->getX(), i.second->getY());*/
}

/**
 * 更新匹配列表（通过一个Pic.
 * 更新Pic的四周所有有效点的匹配信息
 * \param a 通过该位置更新匹配列表
 */
void Map::updateMatchedlist(Pic* a)
{
	/*删除和本图标有关的匹配*/
	for (auto it = matchedlist.begin(); it != matchedlist.end();)
		if (it->first == a || it->second == a)
			it = matchedlist.erase(it);
		else it++;

	/*探寻本图标周边的点*/
	std::vector<Pic*>v;
	if (getPicup(a) != nullptr)v.push_back(getPicup(a));
	if (getPicdown(a) != nullptr)v.push_back(getPicdown(a));
	if (getPicleft(a) != nullptr)v.push_back(getPicleft(a));
	if (getPicright(a) != nullptr)v.push_back(getPicright(a));
	for (auto i : v)
		if (i->getValid() && i->getIsStroke() == false)
			for (auto j : map)
				if (j->getValid() && i != j && canMatch(i, j, false))
					matchedlist.push_back(std::pair<Pic*, Pic*>{i, j});
	sort(matchedlist.begin(), matchedlist.end());
	matchedlist.erase(unique(matchedlist.begin(), matchedlist.end()), matchedlist.end());
	printf("---------\n");
	for (auto i : matchedlist)
		printf("%d %d %d %d\n", i.first->getX(), i.first->getY(), i.second->getX(), i.second->getY());
}

/**
 * 随机排列
 *
 * 重新排列所有Pic的位置并生成新的MatchedList *
 */
void Map::RandomOrder()
{
	// used to store the index of all visible objects
	std::vector <int> visibleObjIdx;

	// store the index of all visible objects
	for (size_t i = 0; i < map.size(); i++)
	{
		if (map[i]->getIsVisible())
		{
			visibleObjIdx.push_back(i);
		}
	}

	// if there is no more than 2 objects left,
	// then there is no need for a rearrangement.
	if (visibleObjIdx.size() > 2)
	{
		for (size_t i = 0; i < visibleObjIdx.size(); i++)
		{
			Pic* tmpPic = nullptr;

			// generate two random numbers to determine which objects to swap
			int randomIdx1 = now->getRand() % visibleObjIdx.size();
			int randomIdx2 = now->getRand() % visibleObjIdx.size();
			int tmpX, tmpY;

			// swap X and Y
			tmpX = map[visibleObjIdx[randomIdx1]]->getX();
			map[visibleObjIdx[randomIdx1]]->setX(map[visibleObjIdx[randomIdx2]]->getX());
			map[visibleObjIdx[randomIdx2]]->setX(tmpX);

			tmpY = map[visibleObjIdx[randomIdx1]]->getY();
			map[visibleObjIdx[randomIdx1]]->setY(map[visibleObjIdx[randomIdx2]]->getY());
			map[visibleObjIdx[randomIdx2]]->setY(tmpY);

			// swap the indexes of two objects
			tmpPic = map[visibleObjIdx[randomIdx1]];
			map[visibleObjIdx[randomIdx1]] = map[visibleObjIdx[randomIdx2]];
			map[visibleObjIdx[randomIdx2]] = tmpPic;
		}
	}

	// update matched list
	updateMatchedlist();
}

/**
 * .判断是否能够连接
 * 通过Matchedlist判断两个图标是否能够“连连看”
 * \param a 图标1
 * \param b 图标2
 * \return  是否能够匹配
 */
bool Map::isMatch(Pic* a, Pic* b)
{
	auto p{ std::pair<Pic*,Pic*>{a,b} }, q{ std::pair<Pic*,Pic*>{b,a} };
	for (auto i = matchedlist.begin(); i != matchedlist.end(); i++)
		if (*i == p || *i == q) {
			this->canMatch(a, b, true);
			a->setIsStroke(true);
			b->setIsStroke(true);
			a->setIsVisible(false);
			b->setIsVisible(false);
			/*	updateMatchedlist(a);
				updateMatchedlist(b);*/
			matchedlist.clear();
			updateMatchedlist();
			a->setIsVisible(true);
			b->setIsVisible(true);
			return true;
		}
	return false;
}

/**
 * 判断地图中是否还能进行匹配.
 * 通过判断matchedlist是否为空就可以知道地图中是否还能匹配
 * \return 能否匹配
 */
bool Map::anyMatch()
{
	return !matchedlist.empty() || isWin();
}

/**
 * 绘画地图.
 * 绘画地图中的每一个图标
 */
void Map::draw()
{
	for (auto p : map)p->draw();
}

void Map::openHelp()
{
	if (help.first != nullptr || help.second != nullptr)closeHelp();
	help = matchedlist.front();
	help.first->setIsStroke(true);
	help.second->setIsStroke(true);
}

void Map::closeHelp()
{
	help.first->setIsStroke(false);
	help.second->setIsStroke(false);
	help = { nullptr,nullptr };
}

bool Map::isWin()
{
	for (auto i : map)
		if (i->getIsVisible())return false;
	return true;
}

std::pair<Pic*, Pic*> Map::getFirstMatchedPair()
{
	return matchedlist.front();
}

/**
 * 获取某Pic的上方Pic.
 *
 * \param a Pic对象
 * \return  Pic上方的Pic，无则nullptr
 */
Pic* Map::getPicup(Pic* a)
{
	if (a->getX() == 0) return nullptr;
	return map[n * (a->getX() - 1) + a->getY()];
}

/**
 * 获取某Pic的下方Pic.
 *
 * \param a Pic对象
 * \return  Pic下方的Pic，无则nullptr
 */
Pic* Map::getPicdown(Pic* a)
{
	if (a->getX() == m - 1) return nullptr;
	return map[n * (a->getX() + 1) + a->getY()];
}

/**
 * 获取某Pic的左侧Pic.
 *
 * \param a Pic对象
 * \return  Pic左侧的Pic，无则nullptr
 */
Pic* Map::getPicleft(Pic* a)
{
	if (a->getY() == 0)return nullptr;
	return map[n * (a->getX()) + a->getY() - 1];
}

/**
 * 获取某Pic的右侧Pic.
 *
 * \param a Pic对象
 * \return  Pic右侧的Pic，无则nullptr
 */
Pic* Map::getPicright(Pic* a)
{
	if (a->getY() == n - 1)return nullptr;
	return map[n * (a->getX()) + a->getY() + 1];
}

void Map::setConnectLine(ConnectLine* line_)
{
	connect_line = line_;
}

ConnectLine* Map::getConnectLine()
{
	return connect_line;
}