#include "g2.h"

Point::Point()
{
    Point::e1 = 0;
    Point::e2 = 0;
}

Point::Point(double x, double y)
{
    Point::e1 = x;
    Point::e2 = y;
}

double Point::getX() const
{
    return Point::e1;
}

double Point::getY() const
{
    return Point::e2;
}

bool Point::operator==(const Point &x) const
{
    return Point::e1 == x.getX() && Point::e2 == x.getY();
}

bool Point::operator!=(const Point &x) const
{
    return Point::e1 != x.getX() || Point::e2 != x.getY();
}

Line::Line(const Point &x, const Point &y)
{
    Line::v1 = x;
    Line::v2 = y;

    if (x == y)
        throw std::runtime_error("Line is defined with two identical points (" + std::to_string(x.getX()) + "; " + std::to_string(x.getY()) + ")");
}

Point Line::getA() const
{
    return Line::v1;
}

Point Line::getB() const
{
    return Line::v2;
}

double Line::operator~() const
{
    return ~Vec2(Line::v1, Line::v2);
}

Vec2::Vec2(const Point &x)
{
    Vec2::e1 = x.getX();
    Vec2::e2 = x.getY();
}

Vec2::Vec2(const Point &x, const Point &y)
{
    Vec2::e1 = y.getX() - x.getX();
    Vec2::e2 = y.getY() - x.getY();
}

double Vec2::getX() const
{
    return Vec2::e1;
}

double Vec2::getY() const
{
    return Vec2::e2;
}

bool Vec2::operator==(const Vec2 &x)
{
    return Vec2::e1 == x.getX() && Vec2::e2 == x.getY();
}

bool Vec2::operator!=(const Vec2 &x)
{
    return Vec2::e1 != x.getX() || Vec2::e2 != x.getY();
}

double Vec2::operator*(const Vec2 &x)
{
    return Vec2::e1 * x.getX() + Vec2::e2 * x.getY();
}

double Vec2::operator~()
{
    return sqrt(Vec2::e1 * Vec2::e1 + Vec2::e2 * Vec2::e2);
}

Polygon::Polygon(const std::vector<Point> &x)
{
    Polygon::v = x;

    for (int i = 1; i < x.size(); ++i)
        if (x[i] == x[i - 1])
            throw std::runtime_error("Line is defined with two identical points (" + std::to_string(x[i].getX()) + "; " + std::to_string(x[i].getY()) + ")");
}

Point Polygon::operator[](int x) const
{
    return Polygon::v[x % Polygon::v.size()];
}

Line Polygon::getSegment(int x) const
{
    return Line(Polygon::v[x % Polygon::v.size()], Polygon::v[(x + 1) % Polygon::v.size()]);
}

Vec2 Polygon::getVector(int x) const
{
    return Vec2(Polygon::v[x % Polygon::v.size()], Polygon::v[(x + 1) % Polygon::v.size()]);
}
