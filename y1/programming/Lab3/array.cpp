#include <bits/stdc++.h>

int n = 12;
int* p = new int[n];

int getN()
{
    return n;
}

bool change_size(int x)
{
    if (x <= 0)
        return false;

    if (x > n)
    {
        x -= n;
        std::cout << "MEMORY ALLOC: length: " << n << "(+" << x << ") * 4 bytes, new bytes: " << 4*x << '\n';

        try
        {
            delete[] p;
            p = new int[n + x];
            n += x;
        }
        catch (...)
        {
            std::cout << "ERROR\n";
            return false;
        }
    }
    else if (x < n)
    {
        try
        {
            delete[] p;
            p = new int[x];
            n = x;
        }
        catch (...)
        {
            std::cout << "ERROR\n";
            return false;
        }
    }

    return true;
}

bool input_array()
{
    try
    {
        for (int i = 0; i < n; ++i)
            if (!scanf("%i", p+i))
                return false;
    }
    catch (...)
    {
        std::cin.clear();
        fflush(stdin);
        return false;
    }

    std::cin.clear();
    fflush(stdin);
    return true;
}

void randomize_array()
{
    srand(time(0));

    for (int i = 0; i < n; ++i)
        p[i] = rand();
}

bool print_array()
{
    try
    {
        for (int i = 0; i < n; i += 5)
        {
            for (int j = i; j < i + 5 && j < n; ++j)
                std::cout << p[j] << ' ';
            std::cout << '\n';
        }
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool paste_array(int x, int y)
{
    try
    {
        std::cout << "MEMORY ALLOC: length: " << n << "(+1) * 4 bytes, new bytes: 4\n";
        int* q = new int[n + 1];
        int i = 0;

        for (; i < y; ++i)
            q[i] = p[i];

        q[i] = x;

        for (; i < n; ++i)
            q[i + 1] = p[i];

        ++n;

        delete p;
        p = q;
    }
    catch (...)
    {
        std::cout << "ERROR\n";
        return false;
    }

    return true;
}

bool paste_element(int x)
{
    int mn = 0b01111111111111111111111111111111, mx = 0b10000000000000000000000000000000, u = 0, v = 0;

    for (int i = 0; i < n; ++i)
    {
        if (p[i] < mn)
            mn = p[i],
            u = i;
        if (p[i] >= mx)
            mx = p[i],
            v = i;
    }

    if (++u > v)
        std::swap(u,v);

    if (!(paste_array(x, v) && paste_array(x, u)))
        return false;

    return true;
}

void quicksort_array(int x, int y)
{
    int l = x, r = y, m = p[l + r >> 1];

    while (l < r)
    {
        while (p[l] < m) ++l;
        while (p[r] > m) --r;

        if (l < r)
            std::swap(p[l++], p[r--]);
    }

    if (x < r) quicksort_array(x, r);
    if (r+1 < y) quicksort_array(r+1, y);
}

void sort_array()
{
    quicksort_array(0,n-1);
}

void input_n()
{
    int x;

    if (scanf("%i", &x) != 1 || x <= 0)
        std::cout << "Wrong value of N\n";
    else
        change_size(x);
    std::cin.clear();
    fflush(stdin);
}

void input_element()
{
    long long x;

    if (scanf("%i", &x) != 1)
        std::cout << "Wrong value of element\n";
    else
        paste_element(x);
    std::cin.clear();
    fflush(stdin);
}
