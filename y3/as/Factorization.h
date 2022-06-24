#pragma once
#include "ModularArithmetic.h"
#include "Primes.h"
using namespace std;

LongInt Jacobi(LongInt a, LongInt n)
{
    if (n < 3 || n % 2 == 0)
        return LongInt::nan();

    if (gcd(a,n) != 1)
        return 0;

    LongInt r = 1,t;

    if (a < 0)
    {
        a = -a;

        if (mod(n,4) == 3)
            r = -r;
    }

    while (a != 0)
    {
        t = 0;

        while (a % 2 == 0)
        {
            t += 1;
            a /= 2;
        }

        if (t % 2 == 1)
        {
            LongInt nm8 = mod(n,8);

            if (nm8 == 3 || nm8 == 5)
                r = -r;
        }

        if (mod(a,4) == 3 && mod(n,4) == 3)
            r = -r;
        t = a;
        a = mod(n,t);
        n = t;
    }

    return r;
}

bool Solovay_Strassen(const LongInt& n, int k)
{
    if (n == 2)
        return true;
    if (n < 3 || n % 2 == 0)
        return false;

    for (int i = 0; i < k; ++i)
    {
        LongInt a = Rand_Long(2, n-1);

        if (gcd(a,n) > 1)
            return false;
        if (mod_pow(a,(n-1)/2,n) != mod(Jacobi(a,n),n))
            return false;
    }

    return true;
}

bool Primetest(const LongInt& n, int k)
{
    if (Primes::Last() < n)
        return Solovay_Strassen(n,k);
    else
        return Primes::CheckPrime(n);
}

bool Primetest(const LongInt& n)
{
    return Primetest(n,10);
}

LongInt PollardRho_Factor(const LongInt& n)
{
    if (n <= 0)
        return LongInt::nan();
    if (n == 1 || Primetest(n))
        return n;

    LongInt s = n.sqrt();
    LongInt x0 = 1;
    LongInt x;
    LongInt y;
    LongInt g = n;

    while (x0 <= s && g == n)
    {
        x0 += 1;
        x = x0;
        y = x0;
        g = gcd(n,x);

        while (g == 1)
        {
            x = mod_add(x*x,1,n);
            y = mod_add(y*y,1,n);
            y = mod_add(y*y,1,n);
            g = gcd(n, mod_sub(x, y, n));
        }
    }

    return g;
}

std::vector<LongInt> PollardRho(const LongInt& n)
{
    std::vector<LongInt> r;
    std::vector<LongInt> x = {n};

    while (!x.empty())
    {
        //cout << x.size() << " ";
        LongInt y = x.back();
        LongInt z = PollardRho_Factor(y);
        y /= z;
        x.pop_back();

        if (y == 1 || z == 1)
        {
            if (y != 1)
                r.push_back(y);
            if (z != 1)
                r.push_back(z);
        }
        else
        {
            x.push_back(y);
            x.push_back(z);
        }
    }

    std::sort(r.begin(), r.end());
    return r;
}

LongInt BGStep(const LongInt& a, const LongInt& b, const LongInt& n)
{
    if (n % a == 0)
        return LongInt::nan();

    std::vector<LongInt> v;
    LongInt m = n.sqrt() + 1;
    LongInt ajm = 1;
    LongInt am = mod_pow(a,m,n);
    LongInt bai = b;

    for (LongInt i = 0; i < m; i += 1)
    {
        v.push_back(bai);
        bai = mod_mul(bai,a,n);
    }

    for (LongInt j = 0; j <= m; j += 1)
    {
        auto f = std::find(v.begin(), v.end(), ajm);

        if (f != v.end())
            return mod_sub(mod_mul(j,m,n),std::distance(v.begin(), f),n);

        ajm = mod_mul(ajm,am,n);
    }

    return LongInt::nan();
}

LongInt Euler(LongInt x)
{
    if (x < 1)
        return LongInt::nan();
    if (x == 1)
        return 1;
    if (Primetest(x))
        return x-1;

    LongInt y = PollardRho_Factor(x);
    x /= y;
    LongInt d = gcd(x,y);
    return Euler(x)*Euler(y)*d/Euler(d);
}

LongInt Mobius(const LongInt& x)
{
    if (x == 1)
        return 1;
    if (x < 1)
        return LongInt::nan();

    vector<LongInt> v = PollardRho(x);

    for (int i = 1; i < v.size(); ++i)
        if (v[i] == v[i-1])
            return 0;

    return v.size()%2 ? -1 : 1;
}

LongInt Legendre(const LongInt& a, const LongInt& p)
{
    if (p == 2 || !Primetest(p))
        return LongInt::nan();

    if (a % p == 0)
        return 0;

    return Jacobi(a,p);

    /*if (mod_pow(a,(p-1)/2, p) == 1)
        return 1;
    else
        return -1;*/
}

std::pair<LongInt, LongInt> Cipolla_pow(std::pair<LongInt, LongInt> x, const LongInt& p, const LongInt& w, const LongInt& m)
{
    if (p == 0)
        return std::pair<LongInt, LongInt>(1,0);

    x.first = mod(x.first,m);
    x.second = mod(x.second,m);

    if (p == 1)
        return x;

    std::pair<LongInt, LongInt> y = Cipolla_pow(x,p/2,w,m);
    y = { mod_add(y.first*y.first,y.second*y.second*w,m) , mod_mul(y.first*2,y.second,m) };

    if (p % 2 == 1)
        y = { mod_add(x.first*y.first,x.second*y.second*w,m) , mod_add(x.first*y.second,x.second*y.first,m) };

    return y;
}

LongInt Cipolla(const LongInt& n, const LongInt& p)
{
    if (Legendre(n,p) != 1)
        return LongInt::nan();

    LongInt a = Rand_Long(0,p-1);

    while (Legendre(a*a-n,p) == 1)
        a = Rand_Long(0,p-1);

    LongInt x = a, y = mod_sub(mod_mul(a,a,p),n,p);

    return Cipolla_pow(std::pair<LongInt, LongInt>(a,1),(p+1)/2,a*a-n,p).first;
}
