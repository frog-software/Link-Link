#include "Map-Pic.h"
#include "Control.h"
extern Control* now;

Pic::Pic(int _kind,int _x,int _y) :x{ _x }, y{ _y }, isVisible{ true }, isStroke{ true },kind{ _kind }
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

void Pic::draw()
{
    char* s = new char[100];
    sprintf_s(s, 100, "[%2d]", kind);
    now->xyprintf(x * 20, y * 30, s, 20);
}

bool Pic::operator<(const Pic& b)
{
    if (this->x != b.x)return this->x < b.x;
    else return this->y < b.y;
}


Map::Map(int _m, int _n):m{_m},n{_n}
{
    int t{ 0 };
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (t > 0)t = -t;
            else t = now->getRand() % 20 + 1;
            map.push_back(new Pic{ abs(t),i,j });

        }
    RandomOrder();
}

void Map::RandomOrder()
{
    /*to be continued*/
    now->xyprintf(0, 0, "随机排列顺序的函数还没有写！", 20);
}

bool Map::isMatch(Pic* a, Pic* b)
{
    auto p{ std::pair<Pic*,Pic*>{a,b} };
    for (auto i : matchedlist)
        if (i == p)return true;
    return false;
}


bool Map::anyMatch()
{
    return !matchedlist.empty();
}

void Map::draw()
{
    for (auto p : map)p->draw();
}




