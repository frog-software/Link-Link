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
    now->xyprintf(x * 40, y * 30, s, 20);
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

#define picwidth 40
#define picheight 30
void Map::drawMatchedLine(Pic* start, Pic* end)
{
    /*x1,x2,y1,y2：起终点的坐标，len：线段长度。默认start在end的左侧*/
    int x1,x2,y1,y2,len;
    x1 = start->getX() * picwidth;
    y1 = start->getY() * picheight;
    x2 = end->getX() * picwidth;
    y2 = end->getY() * picheight;
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

void Map::drawMatchedLine(Pic* start,Pic* end,Pic* corner1, Pic* corner2)
{
    drawMatchedLine(start, corner1);
    drawMatchedLine(corner1, corner2);
    drawMatchedLine(corner2, end);
}
