#pragma once
#include <bits/stdc++.h>

class LongInt
{
    static int const base = 100000000;
    static int const basepow = 8;
    bool sign;
    std::vector<int> digits;
public:
    LongInt();
    LongInt(int64_t x);
    LongInt(std::string x);

    bool isNull() const;
    bool isNaN() const;
    bool getSign() const;
    bool operator==(const LongInt& x) const;
    bool operator!=(const LongInt& x) const;
    bool operator<(const LongInt& x) const;
    bool operator>(const LongInt& x) const;
    bool operator<=(const LongInt& x) const;
    bool operator>=(const LongInt& x) const;

    LongInt operator-() const;
    LongInt operator+(const LongInt& x) const;
    LongInt operator-(const LongInt& x) const;
    LongInt operator*(const LongInt& x) const;
    LongInt operator/(const LongInt& x) const;
    LongInt operator%(const LongInt& x) const;
    LongInt operator^(const LongInt& x) const;
    LongInt operator<<(const LongInt& x) const;
    LongInt operator>>(const LongInt& x) const;

    LongInt& operator=(const LongInt& x);
    LongInt& operator+=(const LongInt& x);
    LongInt& operator-=(const LongInt& x);
    LongInt& operator*=(const LongInt& x);
    LongInt& operator/=(const LongInt& x);
    LongInt& operator%=(const LongInt& x);
    LongInt& operator^=(const LongInt& x);
    LongInt& operator<<=(const LongInt& x);
    LongInt& operator>>=(const LongInt& x);

    /*LongInt mod_add(const LongInt& x, int m) const;
    LongInt mod_sub(const LongInt& x, int m) const;
    LongInt mod_mul(const LongInt& x, int m) const;
    LongInt mod_div(const LongInt& x, int m) const;
    LongInt mod_pow(const LongInt& x, int m) const;*/
    static LongInt nan();
    LongInt sqr() const;
    LongInt sqrt() const;

    int64_t to_int64() const;
    int64_t log10() const;

    operator std::string() const;

    friend std::ostream& operator<<(std::ostream& os, const LongInt& x);
    friend std::istream& operator>>(std::istream& is, LongInt& x);
};

LongInt gcd(LongInt x, LongInt y);
LongInt Rand_Long(LongInt x, LongInt y);

LongInt::LongInt()
{
    sign = 0;
    digits.clear();
}

LongInt::LongInt(int64_t x)
{
    sign = x < 0;
    digits.clear();

    if (x < 0)
        x *= -1;

    while (x != 0)
    {
        digits.push_back(x % base);
        x /= base;
    }
}

LongInt::LongInt(std::string x)
{
    sign = 0;
    digits.clear();

    if (x == "nan")
    {
        sign = 1;
        return;
    }

    if (x[0] == '-')
    {
        sign = 1;
        x.erase(x.begin(), x.begin()+1);
    }

    if (x.empty())
        throw -1;

    x.erase(x.begin(), std::find_if(x.begin(), x.end(), [](char d){return d!='0';}));

    if (!x.empty())
    {
        int y = 0, z = 1;

        for (auto i = x.rbegin(); i != x.rend(); ++i)
        {
            if (*i > '9' || *i < '0')
                throw -1;

            y += (*i - '0') * z;
            z *= 10;

            if (z >= base)
            {
                digits.push_back(y);
                y = 0;
                z = 1;
            }
        }

        if (y != 0)
            digits.push_back(y);
    }
    else
    {
        sign = 0;
    }
}

bool LongInt::isNull() const
{
    return !sign && digits.size() == 0;
}

bool LongInt::isNaN() const
{
    return sign && digits.size() == 0;
}

bool LongInt::getSign() const
{
    return sign;
}

LongInt LongInt::operator-() const
{
    LongInt x;

    if (digits.empty())
        return x;

    x.sign = !sign;
    x.digits = digits;
    return x;
}

LongInt& LongInt::operator=(const LongInt& x)
{
    sign = x.sign;
    digits = x.digits;
    return *this;
}

LongInt& LongInt::operator+=(const LongInt& x)
{
    if (isNaN() || x.isNaN())
        return operator=(nan());
    if (isNull())
        return operator=(x);
    if (x.isNull())
        return *this;

    if (x.sign)
        return operator-=(-x);

    if (sign)
    {
        LongInt y;
        y = operator-();
        y -= x;
        return operator=(-y);
    }

    std::vector<int> y;

    y.reserve(digits.size()+1);
    y.reserve(x.digits.size()+1);
    int c = 0;

    for (int i = 0; i < digits.size() || i < x.digits.size(); ++i)
    {
        if (i < digits.size())
            c += digits[i];
        if (i < x.digits.size())
            c += x.digits[i];

        y.push_back(c % base);
        c /= base;
    }

    if (c != 0)
        y.push_back(c);

    digits = y;

    return *this;
}

LongInt LongInt::operator+(const LongInt& x) const
{
    LongInt y;
    y = *this;
    y += x;
    return y;
}

LongInt& LongInt::operator-=(const LongInt& x)
{
    if (isNaN() || x.isNaN())
        return operator=(nan());
    if (isNull())
        return operator=(-x);
    if (x.isNull())
        return *this;

    if (x.sign)
        return operator+=(-x);

    if (sign)
    {
        LongInt y;
        y = operator-();
        y += x;
        return operator=(-y);
    }

    if (operator<(x))
    {
        LongInt y;
        y = x;
        y -= *this;
        return operator=(-y);
    }

    int c = 0;

    for (int i = 0; i < digits.size() || i < x.digits.size(); ++i)
    {
        if (i < x.digits.size())
            c += x.digits[i];

        if (digits[i] < c)
        {
            digits[i] -= c - base;
            c = 1;
        }
        else
        {
            digits[i] -= c;
            c = 0;
        }
    }

    int i = digits.size()-1;

    while (i >= 0 && digits[i] == 0)
        --i;

    digits.resize(i+1);
    return *this;
}

LongInt LongInt::operator-(const LongInt& x) const
{
    LongInt y;
    y = *this;
    y -= x;
    return y;
}

LongInt& LongInt::operator*=(const LongInt& x)
{
    if (isNaN() || x.isNaN())
        return operator=(nan());
    if (isNull())
        return *this;
    if (x.isNull())
        return operator=(x);

    if (sign)
    {
        LongInt y = operator-();
        y *= -x;
        return operator=(y);
    }

    if (x.sign)
    {
        operator*=(-x);
        return operator=(operator-());
    }

    if (x.digits.size() == 1)
    {
        int64_t c = 0,r;

        for (int i = 0; i < digits.size(); ++i)
        {
            r = digits[i];
            r *= x.digits.back();
            r += c;
            c = r / base;
            digits[i] = r % base;
        }

        if (c != 0)
            digits.push_back(c);

        return *this;
    }

    if (x.digits[0] == 0)
    {
        int i = 0;

        while (x.digits[i] == 0)
            ++i;

        operator*=(x >> i);
        return operator<<=(i);
    }

    return operator=(operator*(x));
}

LongInt LongInt::operator*(const LongInt& x) const
{
    if (isNaN() || x.isNaN())
        return nan();
    if (isNull())
        return *this;
    if (x.isNull())
        return x;

    LongInt y;

    if (sign)
        return -operator-().operator*(x);

    if (x.sign)
        return -operator*(-x);

    if (digits.size() == 1 || digits[0] == 0)
    {
        y = x;
        y *= *this;
        return y;
    }

    if (x.digits.size() == 1 || x.digits[0] == 0)
    {
        y = *this;
        y *= x;
        return y;
    }

    size_t lim = 16;

    if (digits.size() >= lim && x.digits.size() >= lim)
    {
        //(aM+b)*(cM+d)
        if (digits.size() == x.digits.size())
        {
            LongInt a, b, c, d;
            size_t h = digits.size()/2;

            a.digits.assign(digits.begin()+h, digits.end());
            b.digits.assign(digits.begin(), digits.begin()+h);
            b.digits.erase(std::find_if(b.digits.rbegin(), b.digits.rend(), [](int d){return d!=0;}).base(), b.digits.end());

            c.digits.assign(x.digits.begin()+h, x.digits.end());
            d.digits.assign(x.digits.begin(), x.digits.begin()+h);
            d.digits.erase(std::find_if(d.digits.rbegin(), d.digits.rend(), [](int d){return d!=0;}).base(), d.digits.end());

            LongInt ac = a*c, bd = b*d;

            LongInt r;
            r = ac;
            r <<= h;
            r += (a+b)*(c+d)-ac-bd;
            r <<= h;
            r += bd;

            return r;
        }

        //(aM+b)*c
        if (digits.size() > x.digits.size())
        {
            LongInt a, b;
            size_t h = x.digits.size();

            a.digits.assign(digits.begin()+h, digits.end());
            b.digits.assign(digits.begin(), digits.begin()+h);
            b.digits.erase(std::find_if(b.digits.rbegin(), b.digits.rend(), [](int d){return d!=0;}).base(), b.digits.end());

            LongInt r;
            r = a*x;
            r <<= h;
            r += b*x;

            return r;
        }
        else
            return x * (*this);
    }


    for (auto i = x.digits.rbegin(); i != x.digits.rend(); ++i)
    {
        LongInt z;
        z = *this;
        z *= *i;
        y <<= 1;
        y += z;
    }

    return y;
}

LongInt& LongInt::operator/=(const LongInt& x)
{
    if (isNaN() || x.isNaN() || x.isNull())
        return operator=(nan());
    if (isNull())
        return *this;


    if (sign)
    {
        LongInt y = operator-();
        y /= -x;
        return operator=(y);
    }

    if (x.sign)
    {
        operator/=(-x);
        return operator=(operator-());
    }

    if (operator<(x))
    {
        sign = 0;
        digits.clear();
        return *this;
    }

    if (x.digits.size() == 1)
    {
        int64_t c = 0;

        for (int i = digits.size()-1; i >= 0; --i)
        {
            c *= base;
            c += digits[i];
            digits[i] = c / x.digits.back();
            c %= x.digits.back();
        }

        if (digits.back() == 0)
            digits.pop_back();

        return *this;
    }

    LongInt y;

    while (operator>=(x))
    {
        LongInt z;

        if (digits.size() == x.digits.size())
        {
            int64_t a = digits.back();
            a *= base;
            a += digits[digits.size()-2];
            int64_t b = x.digits.back();
            b *= base;
            b += x.digits[x.digits.size()-2]+1;
            a /= b;

            if (a == 0)
                z = 1;
            else
                z = a;
        }
        else
        {
            int64_t a = digits.back();
            a *= base;
            a += digits[digits.size()-2];
            a /= x.digits.back()+1;
            z = a;
            z <<= digits.size() - x.digits.size() - 1;
        }

        y += z;
        operator-=(z*x);
    }

    return operator=(y);
/*
    LongInt u = 1, l = 1, w, h;
    int64_t c = digits.back()+1;
    c *= base;
    c += digits[digits.size()-2];
    c /= x.digits.back();
    u = c;
    c = digits.back();
    c *= base;
    c += digits[digits.size()-2];
    c /= x.digits.back()+1;
    l = c;

    //cout << "(" << digits.back() << " " << digits[digits.size()-2] << " " << x.digits.back() << ") "<< "l: " << l << " u: " << u << endl;

    if (digits.size() == x.digits.size())
    {
        u >>= 1;
        l >>= 1;
    }
    else
    {
        u <<= digits.size() - x.digits.size() - 1;
        l <<= digits.size() - x.digits.size() - 1;
    }

    //cout << "(" << digits.back() << " " << digits[digits.size()-2] << " " << x.digits.back() << ") "<< "l: " << l << " u: " << u << endl;

    while (u != l)
    {
        w = (u+l)/2+1;
        h = w * x;

        if (operator==(h))
            return operator=(w);

        if (operator<(h))
            u = w-1;
        else
            l = w;
    }

    return operator=(l);*/
}

LongInt LongInt::operator/(const LongInt& x) const
{
    LongInt y;
    y = *this;
    y /= x;
    return y;
}

LongInt& LongInt::operator%=(const LongInt& x)
{
    if (isNaN() || x.isNaN() || x.isNull())
        return operator=(nan());
    if (isNull())
        return *this;


    if (sign)
    {
        LongInt y = operator-();
        y %= -x;
        return operator=(y);
    }

    if (x.sign)
    {
        operator%=(-x);
        return operator=(operator-());
    }

    if (operator<(x))
    {
        return *this;
    }

    if (x.digits.size() == 1)
    {
        int64_t c = 0;

        for (int i = digits.size()-1; i >= 0; --i)
        {
            c *= base;
            c += digits[i];
            c %= x.digits.back();
        }

        return operator=(c);
    }

    while (operator>=(x))
    {
        LongInt z;

        if (digits.size() == x.digits.size())
        {
            int64_t a = digits.back();
            a *= base;
            a += digits[digits.size()-2];
            int64_t b = x.digits.back();
            b *= base;
            b += x.digits[x.digits.size()-2]+1;
            a /= b;

            if (a == 0)
                z = 1;
            else
                z = a;
        }
        else
        {
            int64_t a = digits.back();
            a *= base;
            a += digits[digits.size()-2];
            a /= x.digits.back()+1;
            z = a;
            z <<= digits.size() - x.digits.size() - 1;
        }

        operator-=(z*x);
    }

    return *this;
    /*if (x.digits.size() == 0)
        throw -1;

    if (sign)
    {
        sign = !sign;
        operator%=(x);
        sign = !sign;
        return *this;
    }

    if (x.sign)
    {
        operator%=(-x);
        sign = !sign;
        return *this;
    }

    if (digits.size() == 0 || operator<(x))
        return *this;

    if (x.digits.size() == 1)
    {
        int64_t c = 0;

        for (int i = digits.size()-1; i >= 0; --i)
        {
            c *= base;
            c += digits[i];
            digits[i] = c / x.digits.back();
            c %= x.digits.back();
        }

        if (digits.back() == 0)
            digits.pop_back();

        return operator=(c);
    }

    LongInt u = 1, l = 1, w, h;
    u = (digits.back()*base+digits[digits.size()-2]+1)/x.digits.back();
    l = (digits.back()*base+digits[digits.size()-2])/(x.digits.back()+1);

    if (digits.size() == x.digits.size())
    {
        u >>= 1;
        l >>= 1;
    }
    else
    {
        u <<= digits.size() - x.digits.size() - 1;
        l <<= digits.size() - x.digits.size() - 1;
    }

    while (u != l)
    {
        w = (u+l)/2+1;
        h = w * x;

        if (operator==(h))
            return operator-=(x*w);

        if (operator<(h))
            u = w-1;
        else
            l = w;
    }

    return operator-=(x*l);*/
}

LongInt LongInt::operator%(const LongInt& x) const
{
    LongInt y;
    y = *this;
    y %= x;
    return y;
}

LongInt& LongInt::operator^=(const LongInt& x)
{
    return operator=(operator^(x));
}

LongInt LongInt::operator^(const LongInt& x) const
{
    if (isNaN() || x.isNaN() || (isNull() && x.isNull()))
        return nan();
    if (isNull())
        return *this;
    if (x.isNull())
        return 1;

    if (x == 1)
        return *this;

    LongInt y = operator^(x / 2).sqr();

    if (x.digits[0] % 2 == 1)
        y *= *this;

    return y;
}

LongInt& LongInt::operator<<=(const LongInt& x)
{
    if (isNaN() || x.isNaN())
        return operator=(nan());

    if (isNull() || x.isNull() || x.sign)
        return *this;

    digits.insert(digits.begin(), x.to_int64(), 0);
    return *this;
}

LongInt LongInt::operator<<(const LongInt& x) const
{
    LongInt y;
    y = *this;
    y <<= x;
    return y;
}

LongInt& LongInt::operator>>=(const LongInt& x)
{
    if (isNaN() || x.isNaN())
        return operator=(nan());

    if (isNull() || x.isNull() || x.sign)
        return *this;

    int64_t y = x.to_int64();

    if (y >= digits.size())
    {
        sign = 0;
        digits.clear();
    }
    else
        digits.erase(digits.begin(), digits.begin()+y);

    return *this;
}

LongInt LongInt::operator>>(const LongInt& x) const
{
    LongInt y;
    y = *this;
    y >>= x;
    return y;
}

bool LongInt::operator==(const LongInt& x) const
{
    if (isNaN() || x.isNaN())
        throw -1;

    if (sign != x.sign || digits.size() != x.digits.size())
        return false;

    return digits == x.digits;
}

bool LongInt::operator!=(const LongInt& x) const
{
    return !operator==(x);
}

bool LongInt::operator<(const LongInt& x) const
{
    if (isNaN() || x.isNaN())
        throw -1;

    if (sign > x.sign)
        return true;
    if (sign < x.sign)
        return false;

    if (digits.size() < x.digits.size())
        return !sign;
    if (digits.size() > x.digits.size())
        return sign;

    for (int i = digits.size()-1; i >=0; --i)
    {
        if (digits[i] < x.digits[i])
            return !sign;
        if (digits[i] > x.digits[i])
            return sign;
    }

    return false;
}

bool LongInt::operator>(const LongInt& x) const
{
    return !operator<(x) && operator!=(x);
}

bool LongInt::operator<=(const LongInt& x) const
{
    return !operator>(x);
}

bool LongInt::operator>=(const LongInt& x) const
{
    return !operator<(x);
}

LongInt LongInt::sqr() const
{
    if (isNull() || isNaN())
        return *this;

    if(digits.size() == 1)
    {
        int64_t s = digits.back();
        s *= s;
        LongInt x;
        x.digits.push_back(s % base);

        if (s / base != 0)
            x.digits.push_back(s / base);

        return x;
    }

    LongInt x, y;
    size_t h = digits.size()/2;
    x.digits.assign(digits.begin()+h, digits.end());
    y.digits.assign(digits.begin(), digits.begin()+h);
    y.digits.erase(std::find_if(y.digits.rbegin(), y.digits.rend(), [](int d){return d!=0;}).base(), y.digits.end());

    LongInt r;
    r = x.sqr();
    r <<= h;
    r += x * y * 2;
    r <<= h;
    r += y.sqr();

    return r;
}

LongInt LongInt::nan()
{
    LongInt x;
    x.sign = 1;
    return x;
}

LongInt LongInt::sqrt() const
{
    if (isNaN() || sign)
        return nan();

    if (operator<(2))
        return *this;

    LongInt u = 1, l = 1, w, h;
    u <<= (digits.size()-1)/2+1;
    l <<= (digits.size()-1)/2;

    while (u != l)
    {
        w = (u+l)/2+1;
        h = w.sqr();

        if (operator==(h))
            return w;

        if (operator<(h))
            u = w-1;
        else
            l = w;
    }

    return l;
}

int64_t LongInt::to_int64() const
{
    if (isNaN())
        throw -1;

    int64_t x = 0;

    for (auto i = digits.rbegin(); i != digits.rend(); ++i)
    {
        x *= base;
        x += *i;
    }

    if (sign)
        x *= -1;

    return x;
}

int64_t LongInt::log10() const
{
    if (digits.size() == 0 || sign)
        return 0/0;

    int64_t l = digits.size() - 1;
    l *= basepow;
    l += floor(std::log10(digits.back()));

    return l;
}

LongInt::operator std::string() const
{
    if (isNaN())
        return "nan";

    std::ostringstream ss;

    if (sign)
        ss << '-';

    if (digits.empty())
        ss << 0;
    else
    {
        auto i = digits.rbegin();
        ss << *i;
        ++i;

        while (i != digits.rend())
        {
            ss << std::setfill('0') << std::setw(basepow) << *i;
            ++i;
        }
    }

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const LongInt& x)
{
    os << std::string(x);
    return os;
}

std::istream& operator>>(std::istream& is, LongInt& x)
{
    std::string y;
    is >> y;
    x = LongInt(y);
    return is;
}

LongInt gcd(LongInt x, LongInt y)
{
    LongInt t;

    while (y != 0)
    {
        t = x % y;
        x = y;
        y = t;
    }

    return x;
}

LongInt Rand_Long(LongInt x, LongInt y)
{
    LongInt z;
    while (x < y)
    {
        z = y-x;
        LongInt r = rand();

        if (z <= RAND_MAX)
        {
            x += (r % z);

            if (x < y)
                y = x;
        }
        else
        {
            z /= RAND_MAX;
            x += r * z;

            if (x < y)
                y = x + z;
        }
    }

    return y;
}
