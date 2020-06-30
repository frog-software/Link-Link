/*****************************************************************//**
 * \file   Map-Pic.cpp
 * \brief  Map类和Pic类的定义文件
 * Map类和Pic类中各个成员叔叔的实现
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/

#include "Map-Pic.h"
#include "Control.h"
#include <algorithm>
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
 * 正常来说是绘画一张图片，这里是临时写法输出数字
 */
void Pic::draw()
{
	char* s = new char[100];
	if (this->isVisible) sprintf_s(s, 100, "./Pic/icons/icon%d.png", kind);
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

void Map::getAcross(Pic* aa, std::vector<Pic*>& v){
	Pic* a = nullptr;
	a = aa;
	while (getPicup(a) != nullptr && getPicup(a)->getIsVisible() == false) {
		a = getPicup(a);
		v.push_back(a);
	}
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


bool Map::canMatch(Pic* a, Pic* b, bool erase)
{
	if (a == nullptr || b == nullptr)
	{
		printf("出现nullptr\n");
		return false;
	}
	if (a->getValid() == false || b->getValid() == false)
		return false;
	if (a->getKind() != b->getKind())
		return false;
	if (a == b)return false;
	std::vector<Pic*>access_a;
	std::vector<Pic*>access_b;
	getAcross(a, access_a);
	getAcross(b, access_b);
	if (access_a.size()==0 || access_b.size()==0)return false;
	for(auto i:access_a)
		for(auto j:access_b)
			if(i==j){
				printf("%d %d hhh\n", i->getX(), i->getY());
				return true;
			}
	for (auto i : access_a)
		for (auto j : access_b)
			if (i->getX() == j->getX()) {
				Pic* begin; Pic* end;
				if (i->getY() < j->getY()) {
					begin = i; end = j;
				}
				else{
					begin = j; end = i;
				}
				bool flag = true;
				do{
					begin = getPicright(begin);
					if(begin->getIsVisible()==true){
						flag = false;
						break;
					}
				} while (begin != end);
				if (flag == true)
					return true;
			}
			else if(i->getY() == j->getY()) {
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
					if (begin->getIsVisible() == true) {
						flag = false;
						break;
					}
				} while (begin != end);
				if (flag == true)
					return true;
			}
	return false;

}

/**
 * 地图类的构造函数
 * 生成一个m行n列的地图
 * \param _m  地图行数
 * \param _n  地图列数
 */
Map::Map(int _m, int _n) :m{ _m+2 }, n{ _n+2 }
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
	for (int i = 0; i < m; i++) {
		map.push_back(new Pic{ -1,i,0 });
		map.back()->setIsVisible(false);
	}
	for (int i = 0; i < m; i++) {
		map.push_back(new Pic{ -1,i,_n+1 });
		map.back()->setIsVisible(false);
	}
	for (int i = 1; i < n-1; i++) {
		map.push_back(new Pic{ -1,0,i });
		map.back()->setIsVisible(false);
	}
	for (int i = 1; i < n-1; i++) {
		map.push_back(new Pic{ -1,_m+1,i });
		map.back()->setIsVisible(false);
	}
	for(unsigned int i=0;i<map.size();i++)
		for(unsigned int j=0;j<map.size();j++)
			if ((*map[j]) < (*map[i]))
				std::swap(map[i], map[j]);

	printf("test\n");
	RandomOrder();
}

/**
 * 更新匹配列表（全体）.
 * 枚举所有点对，一一判断其是否能够进行匹配
 */
void Map::updateMatchedlist()
{
	matchedlist.clear();
	for (unsigned int i = 0; i < map.size(); i++)
		if(map[i]->getValid())
		for (unsigned int j = i + 1; j < map.size(); j++)
			if(map[j]->getValid())
			if (  canMatch(map[i], map[j], false))
				matchedlist.push_back(std::pair<Pic*, Pic*>{map[i], map[j]});

	matchedlist.unique();
	for (auto i : matchedlist)
		printf("%d %d %d %d\n", i.first->getX(), i.first->getY(), i.second->getX(), i.second->getY());
}

/**
 * 更新匹配列表（通过一个Pic.
 * 更新Pic的四周所有有效点的匹配信息
 * \param a 通过该位置更新匹配列表
 */
void Map::updateMatchedlist(Pic* a)
{
	std::vector<Pic*>v;
	if (getPicup(a) != nullptr && getPicup(a)->getValid())v.push_back(getPicup(a));
	if (getPicdown(a) != nullptr && getPicdown(a)->getValid())v.push_back(getPicdown(a));
	if (getPicleft(a) != nullptr && getPicleft(a)->getValid())v.push_back(getPicleft(a));
	if (getPicright(a) != nullptr && getPicright(a)->getValid())v.push_back(getPicright(a));
	for (auto i : v)
		for (auto j : map)
			if (j->getValid() && i != j && canMatch(i, j, false))
				matchedlist.push_back(std::pair<Pic*, Pic*>{i, j});
	matchedlist.unique();

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

	// update map
	draw();

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
	auto p{ std::pair<Pic*,Pic*>{a,b} };
	for (auto i : matchedlist)
		if (i == p)return true;
	return false;
}

/**
 * 判断地图中是否还能进行匹配.
 * 通过判断matchedlist是否为空就可以知道地图中是否还能匹配
 * \return 能否匹配
 */
bool Map::anyMatch()
{
	return !matchedlist.empty();
}

/**
 * 绘画地图.
 * 绘画地图中的每一个图标
 */
void Map::draw()
{
	for (auto p : map)p->draw();
}

void Map::drawMatchedLine(Pic* start, Pic* end)
{
	/*x1,x2,y1,y2：起终点的坐标，len：线段长度。默认start在end的左侧*/

	int x1, x2, y1, y2;
	x1 = start->getX() * Pic::width;
	y1 = start->getY() * Pic::height;
	x2 = end->getX() * Pic::width;
	y2 = end->getY() * Pic::height;

	SDL_Rect line_rect;
	if (x1 == x2) { //x坐标相等，线段垂直方向
		if (y1 - y2 > 0) {
			line_rect.x = x2;
			line_rect.y = y2;
			line_rect.w = 5;
			line_rect.h = y1 - y2;
		}
		else {
			line_rect.x = x1;
			line_rect.y = y1;
			line_rect.w = 5;
			line_rect.h = y2 - y1;
		}
		SDL_SetRenderDrawColor(now->getRenderer(), 0, 74, 140, 255);
		SDL_Rect* pline = &line_rect;
		SDL_RenderFillRect(now->getRenderer(), pline);
	}
	else {//y坐标相等，线段水平方向
		if (x1 - x2 > 0) {
			line_rect.x = x2;
			line_rect.y = y2;
			line_rect.w = x1 - x2;
			line_rect.h = 5;
		}
		else {
			line_rect.x = x1;
			line_rect.y = y1;
			line_rect.w = x2 - x1;
			line_rect.h = 5;
		}
		SDL_SetRenderDrawColor(now->getRenderer(), 0, 74, 140, 255);
		SDL_Rect* pline = &line_rect;
		SDL_RenderFillRect(now->getRenderer(), pline);
	}
}

void Map::drawMatchedLine(Pic* start, Pic* end, Pic* corner1)
{
	drawMatchedLine(start, corner1);
	drawMatchedLine(corner1, end);
}

void Map::drawMatchedLine(Pic* start, Pic* end, Pic* corner1, Pic* corner2)
{
	drawMatchedLine(start, corner1);
	drawMatchedLine(corner1, corner2);
	drawMatchedLine(corner2, end);
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
	if (a->getX() == m-1) return nullptr;
	return map[n * (a->getX()+1) + a->getY() ];
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
	return map[n * (a->getX() ) + a->getY() - 1];
}

/**
 * 获取某Pic的右侧Pic.
 *
 * \param a Pic对象
 * \return  Pic右侧的Pic，无则nullptr
 */
Pic* Map::getPicright(Pic* a)
{
	if (a->getY() == n-1)return nullptr;
	return map[n * (a->getX() ) + a->getY()+1];
}