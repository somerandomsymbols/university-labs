#pragma once
#include "Factorization.h"

typedef pair<LongInt, LongInt> point;

class EllipticCurve
{
    LongInt a;
    LongInt b;
    LongInt p;
    LongInt n;
    LongInt h;
    std::pair<LongInt, LongInt> g;
public:
    EllipticCurve();
    EllipticCurve(const LongInt& a0, const LongInt& b0, const LongInt& p0, const LongInt& n0, const LongInt& h0, const std::pair<LongInt, LongInt>& g0);
    static std::pair<LongInt, LongInt> Inf();
    LongInt GetA() const;
    LongInt GetB() const;
    LongInt GetModulo() const;
    LongInt GetOrder() const;
    std::pair<LongInt, LongInt> GetGenerator() const;
    bool IsPoint(const std::pair<LongInt, LongInt>& x) const;
    bool IsInf(const std::pair<LongInt, LongInt>& x) const;
    bool Eq(const std::pair<LongInt, LongInt>& x, const std::pair<LongInt, LongInt>& y) const;
    std::pair<LongInt, LongInt> Neg(std::pair<LongInt, LongInt> x) const;
    std::pair<LongInt, LongInt> Add(const std::pair<LongInt, LongInt>& x, const std::pair<LongInt, LongInt>& y) const;
    std::pair<LongInt, LongInt> Mul(const std::pair<LongInt, LongInt>& x, const LongInt& y) const;
};

print(const point& x)
{
    std::cout << x.first << ' ' << x.second;
}

EllipticCurve::EllipticCurve()
{
    p = LongInt("4451685225093714772084598273548427");
    a = LongInt("4451685225093714772084598273548424");
    b = LongInt("2061118396808653202902996166388514");
    g.first =
        LongInt("188281465057972534892223778713752");
    g.second =
        LongInt("3419875491033170827167861896082688");
    n = LongInt("4451685225093714776491891542548933");
    h = 1;
}

EllipticCurve::EllipticCurve(const LongInt& a0, const LongInt& b0, const LongInt& p0, const LongInt& n0, const LongInt& h0, const std::pair<LongInt, LongInt>& g0)
{
    a = mod(a0,p0);
    b = mod(b0,p0);
    p = p0;
    n = n0;
    h = h0;
    g = std::pair<LongInt, LongInt>(mod(g0.first,p0),mod(g0.second,p0));
}

std::pair<LongInt, LongInt> EllipticCurve::Inf()
{
    return std::pair<LongInt, LongInt>(LongInt::nan(), LongInt::nan());
}

LongInt EllipticCurve::GetA() const
{
    return a;
}

LongInt EllipticCurve::GetB() const
{
    return b;
}

LongInt EllipticCurve::GetModulo() const
{
    return p;
}

LongInt EllipticCurve::GetOrder() const
{
    return n;
}

std::pair<LongInt, LongInt> EllipticCurve::GetGenerator() const
{
    return g;
}

bool EllipticCurve::IsPoint(const std::pair<LongInt, LongInt>& x) const
{
    return IsInf(x) || mod_mul(x.second,x.second,p) == mod_add(mod_mul(x.first,x.first*x.first+a,p),b,p);
}

bool EllipticCurve::IsInf(const std::pair<LongInt, LongInt>& x) const
{
    return x.first.isNaN() || x.second.isNaN();
}

bool EllipticCurve::Eq(const std::pair<LongInt, LongInt>& x, const std::pair<LongInt, LongInt>& y) const
{
    if (IsInf(x) && IsInf(y))
        return true;

    return x.first == y.first && x.second == y.second;
}

std::pair<LongInt, LongInt> EllipticCurve::Neg(std::pair<LongInt, LongInt> x) const
{
    x.second = -x.second;
    return x;
}

std::pair<LongInt, LongInt> EllipticCurve::Add(const std::pair<LongInt, LongInt>& x, const std::pair<LongInt, LongInt>& y) const
{
    /*print(x);
    std::cout << " + ";
    print(y);
    std::cout << endl;*/
    if (IsInf(x))
        return y;
    if (IsInf(y))
        return x;
    if (x.second == -y.second)
        return Inf();
    if (!Eq(x,y) && x.first == y.first)
        return Inf();
    if (Eq(x,y) && x.second.isNull())
        return Inf();

    /*LongInt l, v;

    if (!Eq(x,y) && x.first != y.first)
    {
        l = mod_div(y.second-x.second, y.first-x.first,p);
        v = mod_div(mod_mul(x.second,y.first,p)-mod_mul(y.second,x.first,p), y.first-x.first,p);
    }
    else
    {
        l = mod_div(x.first*x.first*3+a,x.second*2,p);
        v = mod_div(a*x.first+b*2-mod_pow(x.first,3,p),x.second*2,p);
    }

    return std::pair<LongInt, LongInt>(mod_sub(l,x.first+y.first,p), mod_sub(mod_mul(l,x.first+y.first,p),v+mod_pow(l,3,p),p));*/

    LongInt m;
    if (!Eq(x,y))
        m = mod_div(y.second-x.second,y.first-x.first,p);
    else
        m = mod_div(x.first*x.first*3+a,x.second*2,p);

    LongInt xr = mod_sub(m*m,x.first+y.first,p);
    return std::pair<LongInt, LongInt>(xr, mod_sub(mod_mul(m,x.first-xr,p),x.second,p));
}

std::pair<LongInt, LongInt> EllipticCurve::Mul(const std::pair<LongInt, LongInt>& x, const LongInt& y) const
{
    if (y.isNull())
        return Inf();

    if (y < 0)
        return Neg(Mul(x,-y));

    std::pair<LongInt, LongInt> z = Mul(x,y/2);
    z = Add(z,z);

    if (y % 2 == 1)
        z = Add(z,x);

    return z;
}


std::pair<std::pair<LongInt, LongInt>, std::pair<LongInt, LongInt>> ElGamal_encrypt(const EllipticCurve& E, const std::pair<LongInt, LongInt>& Y, const std::pair<LongInt, LongInt>& M)
{
    LongInt r = Rand_Long(1, E.GetOrder()-1);
    std::pair<LongInt, LongInt> g = E.Mul(E.GetGenerator(),r);
    std::pair<LongInt, LongInt> h = E.Add(M,E.Mul(Y,r));
    return std::pair<std::pair<LongInt, LongInt>, std::pair<LongInt, LongInt>>(g,h);
}

std::pair<LongInt, LongInt> ElGamal_decrypt(const EllipticCurve& E, const LongInt& k, const std::pair<std::pair<LongInt, LongInt>, std::pair<LongInt, LongInt>>& c)
{
    return E.Add(E.Neg(E.Mul(c.first,k)),c.second);
}

