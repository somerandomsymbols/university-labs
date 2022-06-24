#pragma once
#include "LongInt.h"

using namespace std;

namespace Primes
{
    //private:
    const std::vector<LongInt> deftable =
    {
        2,3,5,7,11,13,17,19,23,29
    };
    std::vector<LongInt> primevec;
    bool Sieve(const LongInt& x);
    LongInt SieveFirst();
    void SieveNext(LongInt& x);
    void GenerateUntil(const LongInt& x);
    void GenerateAmount(int x);
    void SavePrimes();

    //

    void LoadUntil(const LongInt& x);
    void LoadAmount(int x);
    LongInt GetPrime(int x);
    LongInt Last();
    int Count();
    bool CheckPrime(const LongInt& x);
}

bool Primes::Sieve(const LongInt& x)
{
    for (auto& i : primevec)
    {
        if (i.log10()*2 > x.log10())
            return true;

        if (x % i == 0)
            return false;
    }

    return true;
}

LongInt Primes::SieveFirst()
{
    LongInt bound = primevec.back() / 30;
    bound *= 30;
    bound += 1;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 6;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 4;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 2;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 4;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 2;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 4;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 6;
    if (bound > primevec.back() && Sieve(bound))
        primevec.push_back(bound);
    bound += 1;

    return bound;
}

void Primes::SieveNext(LongInt& x)
{
    x += 1;
    if (Sieve(x))
        primevec.push_back(x);
    x += 6;
    if (Sieve(x))
        primevec.push_back(x);
    x += 4;
    if (Sieve(x))
        primevec.push_back(x);
    x += 2;
    if (Sieve(x))
        primevec.push_back(x);
    x += 4;
    if (Sieve(x))
        primevec.push_back(x);
    x += 2;
    if (Sieve(x))
        primevec.push_back(x);
    x += 4;
    if (Sieve(x))
        primevec.push_back(x);
    x += 6;
    if (Sieve(x))
        primevec.push_back(x);
    x += 1;
}

void Primes::GenerateUntil(const LongInt& x)
{
    if (primevec.empty())
        primevec = deftable;

    if (primevec.back() < x)
    {
        LongInt y = SieveFirst();

        while (primevec.back() < x)
            SieveNext(y);

        SavePrimes();
    }
}

void Primes::GenerateAmount(int x)
{
    if (primevec.empty())
        primevec = deftable;

    if (primevec.size() < x)
    {
        LongInt y = SieveFirst();

        while (primevec.size() < x)
            SieveNext(y);

        SavePrimes();
    }
}

void Primes::LoadUntil(const LongInt& x)
{
    if (x == 0)
        LoadAmount(0);
    else if (primevec.empty() || primevec.back() < x)
    {
        if (x < 31)
            primevec = deftable;
        else
        {
            std::ifstream fi;
            fi.open("primes.txt");
            std::string y = "",z;
            primevec.clear();

            while (!fi.eof() && (primevec.empty() || primevec.back() < x))
            {
                z = y;
                fi >> y;

                if (y != "" && y != z)
                    primevec.push_back(y);
            }

            GenerateUntil(x);
            fi.close();
        }
    }
}

void Primes::LoadAmount(int x)
{
    if (primevec.size() < x || x == 0)
    {
        if (x < 9 && x != 0)
            primevec = deftable;
        else
        {
            std::ifstream fi;
            fi.open("primes.txt");
            std::string y = "",z;
            primevec.clear();

            while (!fi.eof() && (primevec.size() < x || x == 0))
            {
                z = y;
                fi >> y;

                if (y != "" && y != z)
                    primevec.push_back(y);
            }

            GenerateAmount(x);
            fi.close();
        }
    }
}

void Primes::SavePrimes()
{
    std::ofstream fo;
    fo.open("primes.txt");

    for (auto& i : primevec)
    {
        fo << i << ' ';
    }

    fo.close();
}

LongInt Primes::GetPrime(int x)
{
    LoadAmount(x);
    return primevec[x-1];
}

bool Primes::CheckPrime(const LongInt& x)
{
    LoadUntil(x);
    return std::binary_search(primevec.begin(), primevec.end(), x);
}

LongInt Primes::Last()
{
    if (primevec.empty())
        primevec = deftable;

    return primevec.back();
}
int Primes::Count()
{
    if (primevec.empty())
        primevec = deftable;

    return primevec.size();
}
