/*****************************************************************//**
 * \file   Map.cpp
 * \brief  Map�ඨ���ļ�
 * ԭ���� Map���Pic���и�����Ա������ʵ��
 * change: ���Map��Pic�� by wht
 * \author FrogDar

 * \date   June 30 2020
 *********************************************************************/

#include "Map.h"
#include "Control.h"
#include <algorithm>
extern Control *now;

/*��ȡPicʮ����·�Ŀ���Pic*/
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
 * @brief �ж�����Pic�ܷ�ƥ�䣬������ConnectLine����
 *
 * @param a Pic1
 * @param b Pic2
 * @param erase �Ƿ�Ҫ����������ConnectLine����
 * @return true ����ƥ��
 * @return false ����ƥ��
 */
bool Map::canMatch(Pic *a, Pic *b, bool erase)
{
    /*���Դ��룺 �������nullptr˵���������������*/
    if (a == nullptr || b == nullptr)
    {
        printf("����nullptr\n");
        return false;
    }

    /*���ͼ������Ч�ģ���Ȼ�޷�ƥ��*/
    if (a->getValid() == false || b->getValid() == false)
    {
        return false;
    }

    /*���ͼ�겻��ͬһ����Ȼ��ƥ��*/
    if (a->getKind() != b->getKind())
    {
        return false;
    }

    /*���ͼ����ͬһ����Ҳ��ƥ��*/
    if (a == b)
    {
        return false;
    }

    /*��ȡ��a��bΪԴ��ġ�ʮ�ּܡ��ϵ�ͼ��*/
    std::vector<Pic *>access_a;
    std::vector<Pic *>access_b;
    getAcross(a, access_a);
    getAcross(b, access_b);

    /*����ʮ�ּ�ֱ���ཻ��0��1������*/
    for (auto i : access_a)
        for (auto j : access_b)
            if (i == j)
            {
                if (erase)
                    connect_line = new ConnectLine{ a, b, i };

                return true;
            }

    /*����ʮ�ּ��м�ͨ���������ཻ����������*/
    for (auto i : access_a)
        for (auto j : access_b)

            /*x��ȣ���һ��ֱ��*/
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
    /*y��ȣ���һ��ֱ��*/
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

    /*û���ҵ�ƥ��*/
    return false;
}

/**
 * @brief Construct a new Map object
 *
 * @param _m x����ͼ�����
 * @param _n y����ͼ�����
 * @param totalkind ͼ��������
 * @param gravity_ �Ƿ�������ģʽ
 */
Map::Map(int _m, int _n, int totalkind, bool gravity_) : m{ _m + 2 }, n{ _n + 2 }, gravity{ gravity_ }
{
    /*
    ÿ��ͼ����Ҫ�ɶԳ���
    �������������为�����������µ������ķ���
    ʵ�ֳɶԳ���
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

    /*������ΧһȦ�����ڵġ��ڱ���*/
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

    /*�������*/
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
 * ����ƥ���б�ȫ�壩.
 * ö�����е�ԣ�һһ�ж����Ƿ��ܹ�����ƥ��
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
 * @brief �������
 *
 * ������������Pic��λ�ò������µ�MatchedList*
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
 * @brief �ж��Ƿ��ܹ�����
 *
 * ͨ��Matchedlist�ж�����ͼ���Ƿ��ܹ�����������
 * @param a ͼ��1
 * @param b ͼ��2
 * @return true ����ƥ�䣬������ƥ���б�
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
                /*�ȼ�װ�Ѿ������˸���ƥ���б�֮���ٽ��ж���*/
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
 * @brief �жϵ�ͼ���Ƿ��ܽ���ƥ��.
 *
 * ͨ���ж�matchedlist�Ƿ�Ϊ�վͿ���֪����ͼ���Ƿ���ƥ��
 * @return �ܷ�ƥ��
 */
bool Map::anyMatch()
{
    return !matchedlist.empty() || isWin();
}

/**
 * @brief �滭��ͼ
 *
 * ����ConnectLine�滭+��ͼ�е�ÿһ��ͼ��
 */
void Map::draw()
{
    /*����ConnectLine*/

    /*��������µ�ConnectLine����*/
    auto conline = getConnectLine();

    if (conline != nullptr)
    {
        line_list.push_back(conline);
        setConnectLine(nullptr);
    }

    /*���Ƶ�ǰ����ConnectLine����*/
    if (line_list.empty() == false)
        for (auto line : line_list)
        {
            line->drawLine(now);
            line->cnt--;
        }

    /*����������ݵ�ConnectLine����*/
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
 * @brief ������ʾ
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
 * @brief �ر���ʾ
 *
 */
void Map::closeHelp()
{
    help.first->setIsStroke(false);
    help.second->setIsStroke(false);
    help = { nullptr, nullptr };
}

/**
 * @brief �ж��Ƿ������Ϸ
 *
 * @return true ȫ��������
 * @return false ����û��������
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

/*�ж�ͼ���Ƿ���Գ�Ϊ·����һ����*/
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
 * @brief �жϵ�ͼ�Ƿ��ܹ����
 *
 * @return true ��ͼ׼�����ˣ����Ե��
 * @return false ��ͼû��׼�������ܵ��
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
 * @brief ���ص�ͼ��(x,y)��ͼ��
 *
 * @param x ������
 * @param y ������
 * @return Pic* ��ͼ��(x,y)��ͼ��
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
 * @brief ����Ч��
 *
 */
void Map::ifneeddown()
{
    /*û�п�����ģʽֱ���˳�*/
    if (gravity == false)
    {
        return;
    }

    /*�п����������գ�ִ������*/
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

    /*����ƥ���б�*/
    updateMatchedlist();
}

/*����map������ͼ��*/
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
 * ��ȡĳPic���Ϸ�Pic.
 *
 * \param a Pic����
 * \return  Pic�Ϸ���Pic������nullptr
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
 * ��ȡĳPic���·�Pic.
 *
 * \param a Pic����
 * \return  Pic�·���Pic������nullptr
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
 * ��ȡĳPic�����Pic.
 *
 * \param a Pic����
 * \return  Pic����Pic������nullptr
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
 * ��ȡĳPic���Ҳ�Pic.
 *
 * \param a Pic����
 * \return  Pic�Ҳ��Pic������nullptr
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