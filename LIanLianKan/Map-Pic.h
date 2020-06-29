#pragma once
#include<vector>
#include<list>
class Pic{
private:
    int x, y, kind;
    bool isVisible, isStroke;
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

const int N = 100;
class Map{
private:
    int m, n;
    std::vector<Pic*>map;
    std::list<std::pair<Pic*, Pic*> >matchedlist;
public:
    Map(int _m, int _n);
    void RandomOrder();
    bool isMatch(Pic* a, Pic* b);
    bool anyMatch();
    void draw();
    void drawMatchedLine(Pic* start, Pic* end);
    void drawMatchedLine(Pic* start, Pic* end, Pic* corner1);
    void drawMatchedLine(Pic* start, Pic* end, Pic* corner1, Pic* corner2);
};