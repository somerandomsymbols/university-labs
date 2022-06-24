#include <bits/stdc++.h>

class Point
{
    private:
    double e1, e2;
    public:
    Point();
    Point(double x, double y);
    double getX() const;
    double getY() const;
    bool operator==(const Point &x) const;
    bool operator!=(const Point &x) const;
};

class Line
{
    private:
    Point v1,v2;
    public:
    Line(const Point &x, const Point &y);
    Point getA() const;
    Point getB() const;
    double operator~() const;
};

class Vec2
{
    private:
    double e1,e2;
    public:
    Vec2(const Point &x);
    Vec2(const Point &x, const Point &y);
    double getX() const;
    double getY() const;
    bool operator==(const Vec2 &x);
    bool operator!=(const Vec2 &x);
    double operator*(const Vec2 &x);
    double operator~();
};

class Polygon
{
    private:
    std::vector<Point> v;
    public:
    Polygon(const std::vector<Point> &x);
    Point operator[](int x) const;
    Line getSegment(int x) const;
    Vec2 getVector(int x) const;
};
