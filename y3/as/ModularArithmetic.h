#pragma once
#include "LongInt.h"

class LinearCongruence
{
    LongInt a,b,m;
public:
    LinearCongruence();
    LinearCongruence(const LongInt& x, const LongInt& y);
    LinearCongruence(const LongInt& x, const LongInt& y, const LongInt& z);

    /*LinearCongruence(std::string x)
    {
        if (x == "nan")
        {
            a = LongInt::nan();
            b = LongInt::nan();
            m = LongInt::nan();
        }

        auto i = std::find_if(x.begin(), x.end(), [](char c){return c=='='||c=='≡';});
        //while ()
    }*/

    bool isNaN() const;

    LongInt GetA() const;
    LongInt GetB() const;
    LongInt GetM() const;

    LinearCongruence operator&(const LinearCongruence& x) const;
    LinearCongruence& operator=(const LinearCongruence& x);
    LinearCongruence& operator&=(const LinearCongruence& x);

    static LinearCongruence nan();
    LinearCongruence solve() const;

    operator std::string() const;

    friend std::ostream& operator<<(std::ostream& os, const LinearCongruence& x);
    //friend std::istream& operator>>(std::istream& is, LinearCongruence& x);
};

std::pair<LongInt,LongInt> divmod(const LongInt& x, const LongInt& y);
LongInt div(const LongInt& x, const LongInt& y);
LongInt mod(const LongInt& x, const LongInt& y);
LongInt mod_add(const LongInt& x, const LongInt& y, const LongInt& m);
LongInt mod_sub(const LongInt& x, const LongInt& y, const LongInt& m);
LongInt mod_mul(const LongInt& x, const LongInt& y, const LongInt& m);
LongInt mod_div(const LongInt& x, const LongInt& y, const LongInt& m);
LongInt mod_pow(const LongInt& x, const LongInt& y, const LongInt& m);
std::pair<LongInt, std::pair<LongInt, LongInt>> exteuc(LongInt r0, LongInt r1);
LongInt mod_inv(const LongInt& x, const LongInt& m);

LinearCongruence::LinearCongruence()
{
    m = LongInt::nan();
}

LinearCongruence::LinearCongruence(const LongInt& x, const LongInt& y)
{
    a = x;
    b = y;
    m = 0;
}

LinearCongruence::LinearCongruence(const LongInt& x, const LongInt& y, const LongInt& z)
{
    if (z < 2)
        m = LongInt::nan();
    else
    {
        a = mod(x,z);
        b = mod(y,z);
        m = z;
    }
}

bool LinearCongruence::isNaN() const
{
    return a.isNaN() || a.isNull() || b.isNaN() || m.isNaN();
}

LongInt LinearCongruence::GetA() const
{
    return a;
}

LongInt LinearCongruence::GetB() const
{
    return b;
}

LongInt LinearCongruence::GetM() const
{
    return m;
}

LinearCongruence& LinearCongruence::operator=(const LinearCongruence& x)
{
    a = x.a;
    b = x.b;
    m = x.m;
    return *this;
}

LinearCongruence& LinearCongruence::operator&=(const LinearCongruence& x)
{
    if (isNaN() || x.isNaN())
        return operator=(nan());

    if (a != 1)
        operator=(solve());

    LinearCongruence y = x;
    if (y.a != 1)
        y = y.solve();

    //cout << "here " << y <<  endl;

    y = LinearCongruence(y.a*m,y.b-y.a*b,y.m);

    //cout << "ycon " << y << endl;

    y = y.solve();

    //cout << "ycon " << y.a << " " << y.b << " " << y.m << endl;

    //cout << "r ";
    a = 1;
    //cout << a << " (";
    //cout << b << " " << m*y.b << " " << m*y.m << ") ";
    b = mod_add(b, m*y.b, m*y.m);
    //cout << b << " ";
    m *= y.m;
    //cout << m << endl;

    return *this;
}

LinearCongruence LinearCongruence::operator&(const LinearCongruence& x) const
{
    LinearCongruence y = *this;
    y &= x;
    return y;
}

LinearCongruence LinearCongruence::nan()
{
    LinearCongruence x;
    return x;
}

LinearCongruence LinearCongruence::solve() const
{
    LinearCongruence r;

    if (m < 2)
        return r;

    if (a == 1)
        return *this;

    auto ee = exteuc(a,m);
    LongInt d = ee.first;

    if (mod(b,d) != 0)
        return r;

    LongInt a1 = div(a,d), b1 = div(b,d), m1 = div(m,d);
    r.a = 1;
    r.b = mod_mul(mod_inv(a1,m1),b1,m1);
    r.m = m1;
    return r;
}

LinearCongruence::operator std::string() const
{
    if (isNaN())
        return "nan";

    std::ostringstream ss;

    if (a != 1)
        ss << a;
    ss << "x=" << b;

    if (!m.isNull())
        ss << " (mod " << m << ")";

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const LinearCongruence& x)
{
    os << std::string(x);
    return os;
}

/*std::istream& operator>>(std::istream& is, LinearCongruence& x)
{
    std::string y;
    is >> y;
    x = LinearCongruence(y);
    return is;
}*/

std::pair<LongInt,LongInt> divmod(const LongInt& x, const LongInt& y)
{
    std::pair<LongInt,LongInt> qr;

    if (y < 1 || x.isNaN() || y.isNaN())
    {
        qr.first = LongInt::nan();
        qr.second = LongInt::nan();
        return qr;
    }

    qr.first = x / y;
    qr.second = x - qr.first * y;

    if (qr.second < 0)
    {
        qr.first -= 1;
        qr.second += y;
    }

    return qr;
}

LongInt div(const LongInt& x, const LongInt& y)
{
    return divmod(x, y).first;
}

LongInt mod(const LongInt& x, const LongInt& y)
{
    return divmod(x, y).second;
}

LongInt mod_add(const LongInt& x, const LongInt& y, const LongInt& m)
{
    if (x.isNaN() || y.isNaN() || m.isNaN() || m < 2)
        return LongInt::nan();

    return mod(mod(x, m) + mod(y, m), m);
}

LongInt mod_sub(const LongInt& x, const LongInt& y, const LongInt& m)
{
    if (x.isNaN() || y.isNaN() || m.isNaN() || m < 2)
        return LongInt::nan();

    return mod(mod(x, m) - mod(y, m), m);
}

LongInt mod_mul(const LongInt& x, const LongInt& y, const LongInt& m)
{
    if (x.isNaN() || y.isNaN() || m.isNaN() || m < 2)
        return LongInt::nan();

    return mod(mod(x, m) * mod(y, m), m);
}

LongInt mod_div(const LongInt& x, const LongInt& y, const LongInt& m)
{
    if (x.isNaN() || y.isNaN() || m.isNaN() || m < 2)
        return LongInt::nan();

    if (mod(x,m) == 0)
        return 0;

    return mod_mul(x,mod_inv(y,m),m);
}

LongInt mod_pow(const LongInt& x, const LongInt& y, const LongInt& m)
{
    if (x.isNaN() || y.isNaN() || m.isNaN() || m < 2)
        return LongInt::nan();

    if (y == 0)
        return 1;
    if (y < 0)
        return mod_inv(mod_pow(x,-y,m),m);

    LongInt z = mod_pow(mod_mul(x,x,m),y/2,m);

    if (y % 2 == 1)
        z = mod_mul(z,x,m);

    return z;
}

std::pair<LongInt, std::pair<LongInt, LongInt>> exteuc(LongInt r0, LongInt r1)
{
    LongInt t,q,s0=1,t0=0,s1=0,t1=1;

    while (r1 != 0)
    {
        q = div(r0,r1);

        t = r0 - q*r1;
        r0 = r1;
        r1 = t;

        t = s0 - q*s1;
        s0 = s1;
        s1 = t;

        t = t0 - q*t1;
        t0 = t1;
        t1 = t;
    }

    return std::pair<LongInt, std::pair<LongInt, LongInt>>(r0, std::pair<LongInt, LongInt>(s0,t0));
}

LongInt mod_inv(const LongInt& x, const LongInt& m)
{
    auto ee = exteuc(x,m);

    if (ee.first == 1)
        return mod(ee.second.first, m);
    else
        return LongInt::nan();
}
