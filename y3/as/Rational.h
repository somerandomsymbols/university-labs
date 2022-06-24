#pragma once
#include "LongInt.h"

class Rational
{
public:
    bool sign;
    LongInt n,d;
public:
    Rational();
    Rational(const LongInt& x);
    Rational(const LongInt& x, const LongInt& y);

    bool isNull() const;
    bool isNaN() const;
    bool isInf() const;
    bool getSign() const;

    static Rational nan();
    static Rational inf(bool x);

    double to_double() const;

    operator std::string() const;

    friend std::ostream& operator<<(std::ostream& os, const Rational& x);
};

Rational::Rational()
{
    n = 0;
    d = 1;
}

Rational::Rational(const LongInt& x)
{
    if (x.isNaN())
        n = x;
    else if (x.getSign())
    {
        n = -x;
        sign = 1;
    }
    else
    {
        n = x;
        sign = 0;
    }

    d = 1;
}

Rational::Rational(const LongInt& x, const LongInt& y)
{
    if  (x.isNaN() || y.isNaN() || (x.isNull() && y.isNull()))
    {
        sign = 0;
        n = LongInt::nan();
        d = 1;
    }
    else if (y.isNull())
    {
        n = 1;
        sign = x.getSign();
        d = 0;
    }
    else if (x.isNull())
    {
        sign = y.getSign();
        n = 0;
        d = 1;
    }
    else
    {
        sign = 0;

        if (x.getSign())
        {
            sign = !sign;
            n = -x;
        }
        else
            n = x;
        if (y.getSign())
        {
            sign = !sign;
            d = -y;
        }
        else
            d = y;

        LongInt g = gcd(n,d);
        n /= g;
        d /= g;
    }
}

bool Rational::isNull() const
{
    return n.isNull();
}

bool Rational::isNaN() const
{
    return n.isNaN();
}

bool Rational::isInf() const
{
    return !n.isNaN() && d.isNull();
}

bool Rational::getSign() const
{
    return sign;
}

Rational Rational::nan()
{
    return Rational(LongInt::nan());
}

Rational Rational::inf(bool x)
{
    return Rational(x ? -1 : 1,0);
}

double Rational::to_double() const
{
    if (isNaN())
        return 0.0/0.0;
    if (isNull())
        return sign ? -0.0 : +0.0;
    if (isInf())
        return sign ? -1.0/0.0 : +1.0/0.0;

    string a = string(n), b = string(d);
    int64_t l = a.length();
    l -= b.length();
    double x,y;

    std::stringstream ss;

    ss << a.substr(0,10);
    ss >> x;

    ss.clear();

    ss << b.substr(0,10);
    ss >> y;

    return x/y * pow(10.0, l);
}

Rational::operator std::string() const
{
    if (isNaN())
        return "nan";

    std::ostringstream ss;

    ss << n;

    if (d != 1)
        ss << '/' << d;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Rational& x)
{
    os << std::string(x);
    return os;
}
