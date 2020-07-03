/*****************************************************************//**
 * \file   Map.cpp
 * \brief  Map类定义文件
 * 原本： Map类和Pic类中各个成员函数的实现
 * change: 拆分Map和Pic类 by wht
 * \author FrogDar

 * \date   June 30 2020
 *********************************************************************/

#include "Map.h"
#include "Control.h"
#include <algorithm>
extern Control *now;

/*获取Pic十字链路的可用Pic*/
void Map::getAcross(Pic *aa, std::vector<Pic *> &v, bool extend = false)
{
    v.push_back(aa);
    Pic *a = nullptr;
    a = aa;

    while (getPicup(a) != nullptr && canbepath(getPicup(a)))
    {
        a = getPicup(a);
        v.push_back(a);
    }

    a = aa;

    while (getPicdown(a) != nullptr && canbepath(getPicdown(a)))
    {
        a = getPicdown(a);
        v.push_back(a);
    }

    a = aa;

    while (getPicleft(a) != nullptr && canbepath(getPicleft(a)))
    {
        a = getPicleft(a);
        v.push_back(a);
    }

    a = aa;

    while (getPicright(a) != nullptr && canbepath(getPicright(a)))
    {
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
bool Map::canMatch(Pic *a, Pic *b, bool erase)
{
    /*测试代码： 如果出现nullptr说明传入代码有问题*/
    if (a == nullptr || b == nullptr)
    {
        printf("出现nullptr\n");
        return false;
    }

    /*如果图标是无效的，显然无法匹配*/
    if (a->getValid() == false || b->getValid() == false)
    {
        return false;
    }

    /*如果图标不是同一种显然不匹配*/
    if (a->getKind() != b->getKind())
    {
        return false;
    }

    /*如果图标是同一个，也不匹配*/
    if (a == b)
    {
        return false;
    }

    /*获取以a、b为源点的“十字架”上的图标*/
    std::vector<Pic *>access_a;
    std::vector<Pic *>access_b;
    getAcross(a, access_a);
    getAcross(b, access_b);

    /*两个十字架直接相交，0或1个拐弯*/
    for (auto i : access_a)
        for (auto j : access_b)
            if (i == j)
            {
                if (erase)
                    connect_line = new ConnectLine{ a, b, i };

                return true;
            }

    /*两个十字架中间通过辅助线相交，两个拐弯*/
    for (auto i : access_a)
        for (auto j : access_b)

            /*x相等，画一条直线*/
            if (i->getX() == j->getX())
            {
                Pic *begin;
                Pic *end;

                if (i->getY() < j->getY())
                {
                    begin = i;
                    end = j;
                }
                else
                {
                    begin = j;
                    end = i;
                }

                bool flag = true;

                do
                {
                    begin = getPicright(begin);

                    if (begin != end && begin->getIsVisible() == true)
                    {
                        flag = false;
                        break;
                    }
                } while (begin != end);

                if (flag == true)
                {
                    if (erase)
                        connect_line = new ConnectLine{ a, b, i, j };

                    return true;
                }
            }
    /*y相等，画一条直线*/
            else if (i->getY() == j->getY())
            {
                Pic *begin;
                Pic *end;

                if (i->getX() < j->getX())
                {
                    begin = i;
                    end = j;
                }
                else
                {
                    begin = j;
                    end = i;
                }

                bool flag = true;

                do
                {
                    begin = getPicdown(begin);

                    if (begin != end && begin->getIsVisible() == true)
                    {
                        flag = false;
                        break;
                    }
                } while (begin != end);

                if (flag == true)
                {
                    if (erase)
                        connect_line = new ConnectLine{ a, b, i, j };

                    return true;
                }
            }

    /*没有找到匹配*/
    return false;
}

/**
 * @brief Construct a new Map object
 *
 * @param _m x方向图标个数
 * @param _n y方向图标个数
 * @param totalkind 图标种类数
 * @param gravity_ 是否开启重力模式
 */
Map::Map(int _m, int _n, int totalkind, bool gravity_) : m{ _m + 2 }, n{ _n + 2 }, gravity{ gravity_ }
{
    /*
    每种图形需要成对出现
    所以利用正数变负数，负数变新的正数的方法
    实现成对出现
    */
    int t{ 0 };

    for (int i = 1; i <= _m; i++)
        for (int j = 1; j <= _n; j++)
        {
            if (t > 0)
            {
                t = -t;
            }
            else
            {
                t = now->getRand() % totalkind + 1;
            }

            map.push_back(new Pic{ abs(t), i, j });
        }

    /*生成周围一圈不存在的“哨兵”*/
    for (int i = 0; i < m; i++)
    {
        map.push_back(new Pic{ -1, i, 0 });
        map.back()->setIsVisible(false);
    }

    for (int i = 0; i < m; i++)
    {
        map.push_back(new Pic{ -1, i, _n + 1 });
        map.back()->setIsVisible(false);
    }

    for (int i = 1; i < n - 1; i++)
    {
        map.push_back(new Pic{ -1, 0, i });
        map.back()->setIsVisible(false);
    }

    for (int i = 1; i < n - 1; i++)
    {
        map.push_back(new Pic{ -1, _m + 1, i });
        map.back()->setIsVisible(false);
    }

    for (unsigned int i = 0; i < map.size(); i++)
        for (unsigned int j = 0; j < map.size(); j++)
            if ((*map[j]) < (*map[i]))
            {
                std::swap(map[i], map[j]);
            }

    /*随机排序*/
    RandomOrder();
}

/**
 * @brief Destroy the Map object
 *
 */
Map::~Map()
{
    for (auto i : map)
    {
        delete i;
    }
}

/**
 * 更新匹配列表（全体）.
 * 枚举所有点对，一一判断其是否能够进行匹配
 */
void Map::updateMatchedlist()
{
    matchedlist.clear();

    for (unsigned int i = 0; i < map.size(); i++)
        if (map[i]->getValid() && canbepath(map[i]) == false)
            for (unsigned int j = i + 1; j < map.size(); j++)
                if (map[j]->getValid() && canbepath(map[j]) == false)
                    if (canMatch(map[i], map[j], false))
                        matchedlist.push_back(std::pair<Pic *, Pic *> {map[i], map[j]});
    sort(matchedlist.begin(), matchedlist.end());
    matchedlist.erase(unique(matchedlist.begin(), matchedlist.end()), matchedlist.end());
    /*  for (auto i : matchedlist)
            printf("%d %d %d %d\n", i.first->getX(), i.first->getY(), i.second->getX(), i.second->getY());*/
}

/**
 * @brief 随机排列
 *
 * 重新排列所有Pic的位置并生成新的MatchedList*
 */
void Map::RandomOrder()
{
    // used to store the index of all visible objects
    std::vector <int> visibleObjIdx;

    // store the index of all visible objects
    for (size_t i = 0; i < map.size(); i++)
    {
        if (map[i]->getIsVisible() && canbepath(map[i]) == false)
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
            Pic *tmpPic = nullptr;

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
 * @brief 判断是否能够连接
 *
 * 通过Matchedlist判断两个图标是否能够“连连看”
 * @param a 图标1
 * @param b 图标2
 * @return true 可以匹配，并更新匹配列表
 * @return false
 */
bool Map::isMatch(Pic *a, Pic *b)
{
    auto p{ std::pair<Pic *, Pic *>{a, b} }, q{ std::pair<Pic *, Pic *>{b, a} };

    for (auto i = matchedlist.begin(); i != matchedlist.end(); i++)
        if (*i == p || *i == q)
        {
            this->canMatch(a, b, true);
            a->setIsStroke(true);
            b->setIsStroke(true);

            if (gravity == false)
            {
                /*先假装已经消除了更新匹配列表之后再进行动画*/
                a->setIsVisible(false);
                b->setIsVisible(false);
                updateMatchedlist();
                a->setIsVisible(true);
                b->setIsVisible(true);
            }

            now->playSound(2, "./Sound/Got.wav");
            return true;
        }

    return false;
}

/**
 * @brief 判断地图中是否还能进行匹配.
 *
 * 通过判断matchedlist是否为空就可以知道地图中是否还能匹配
 * @return 能否匹配
 */
bool Map::anyMatch()
{
    return !matchedlist.empty() || isWin();
}

/**
 * @brief 绘画地图
 *
 * 处理ConnectLine绘画+地图中的每一个图标
 */
void Map::draw()
{
    /*处理ConnectLine*/

    /*检测有无新的ConnectLine对象*/
    auto conline = getConnectLine();

    if (conline != nullptr)
    {
        line_list.push_back(conline);
        setConnectLine(nullptr);
    }

    /*绘制当前所有ConnectLine对象*/
    if (line_list.empty() == false)
        for (auto line : line_list)
        {
            line->drawLine(now);
            line->cnt--;
        }

    /*清理可以退休的ConnectLine对象*/
    while (line_list.empty() == false && line_list.front()->cnt == 0)
    {
        delete line_list.front();
        line_list.pop_front();
        ifneeddown();
    }

    for (auto p : map)
    {
        p->draw();
    }
}

/**
 * @brief 开启提示
 *
 */
void Map::openHelp()
{
    if (help.first != nullptr || help.second != nullptr)
    {
        closeHelp();
    }

    help = matchedlist.front();
    help.first->setIsStroke(true);
    help.second->setIsStroke(true);
}

/**
 * @brief 关闭提示
 *
 */
void Map::closeHelp()
{
    help.first->setIsStroke(false);
    help.second->setIsStroke(false);
    help = { nullptr, nullptr };
}

/**
 * @brief 判断是否完成游戏
 *
 * @return true 全部消除了
 * @return false 还有没有消除的
 */
bool Map::isWin()
{
    for (auto i : map)
        if (i->getIsVisible() && canbepath(i) == false)
        {
            return false;
        }

    return true;
}

/**
 * @brief Get the First Matched Pair
 *
 * @return std::pair<Pic*, Pic*>
 */
std::pair<Pic *, Pic *> Map::getFirstMatchedPair()
{
    return matchedlist.front();
}

/*判断图标是否可以成为路径的一部分*/
bool Map::canbepath(Pic *a)
{
    for (auto i : line_list)
    {
        if (i->has(a))
        {
            return true;
        }
    }

    return !a->getIsVisible();
}

/**
 * @brief 判断地图是否能够点击
 *
 * @return true 地图准备好了，可以点击
 * @return false 地图没有准备，不能点击
 */
bool Map::getReady()
{
    if (now->pause == true)
    {
        return false;
    }

    if (gravity == false)
    {
        return true;
    }

    if (gravity == true)
    {
        return line_list.empty();
    }

    return false;
}

/**
 * @brief 返回地图中(x,y)的图标
 *
 * @param x 横坐标
 * @param y 纵坐标
 * @return Pic* 地图中(x,y)的图标
 */
Pic *Map::at(int x, int y)
{
    if (x >= 0 && x < m && y >= 0 && y < n)
    {
        return map[x * n + y];
    }
    else
    {
        return nullptr;
    }
}

/**
 * @brief 重力效果
 *
 */
void Map::ifneeddown()
{
    /*没有开重力模式直接退出*/
    if (gravity == false)
    {
        return;
    }

    /*有可能有两个空，执行两次*/
    for (int i = m - 2; i > 0; i--)
        for (int j = n - 2; j > 1; j--)
            if (at(i, j)->getIsVisible() == false && at(i, j)->getKind())
            {
                this->swap(at(i, j), at(i, j - 1));
            }

    for (int i = m - 2; i > 0; i--)
        for (int j = n - 2; j > 1; j--)
            if (at(i, j)->getIsVisible() == false && at(i, j)->getKind())
            {
                this->swap(at(i, j), at(i, j - 1));
            }

    /*更新匹配列表*/
    updateMatchedlist();
}

/*交换map中两个图标*/
void Map::swap(Pic *a, Pic *b)
{
    std::swap(*a, *b);
    int tx = b->getX(), ty = b->getY();
    b->setX(a->getX());
    a->setX(tx);
    b->setY(a->getY());
    a->setY(ty);
}

/**
 * 获取某Pic的上方Pic.
 *
 * \param a Pic对象
 * \return  Pic上方的Pic，无则nullptr
 */
Pic *Map::getPicup(Pic *a)
{
    if (a->getX() == 0)
    {
        return nullptr;
    }

    return map[n * (a->getX() - 1) + a->getY()];
}

/**
 * 获取某Pic的下方Pic.
 *
 * \param a Pic对象
 * \return  Pic下方的Pic，无则nullptr
 */
Pic *Map::getPicdown(Pic *a)
{
    if (a->getX() == m - 1)
    {
        return nullptr;
    }

    return map[n * (a->getX() + 1) + a->getY()];
}

/**
 * 获取某Pic的左侧Pic.
 *
 * \param a Pic对象
 * \return  Pic左侧的Pic，无则nullptr
 */
Pic *Map::getPicleft(Pic *a)
{
    if (a->getY() == 0)
    {
        return nullptr;
    }

    return map[n * (a->getX()) + a->getY() - 1];
}

/**
 * 获取某Pic的右侧Pic.
 *
 * \param a Pic对象
 * \return  Pic右侧的Pic，无则nullptr
 */
Pic *Map::getPicright(Pic *a)
{
    if (a->getY() == n - 1)
    {
        return nullptr;
    }

    return map[n * (a->getX()) + a->getY() + 1];
}

/**
 * @brief Set the Connect Line object
 *
 * @param line_
 */
void Map::setConnectLine(ConnectLine *line_)
{
    connect_line = line_;
}

/**
 * @brief Get the Connect Line object
 *
 * @return ConnectLine*
 */
ConnectLine *Map::getConnectLine()
{
    return connect_line;
}