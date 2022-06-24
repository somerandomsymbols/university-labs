#include <bits/stdc++.h>
#include "newstring_n.h"

main()
{
    char c[1000], u[1000], i = 0;
    long long v = 0;
    std::ifstream fi;
    fi.open("input.txt");
    std::ofstream fo;
    fo.open("output.txt");

    while (!fi.eof())
    {
        fi.getline(c, 80);

        if (c[0] != '\0')
        {
            int b = pop_back_n(c);
            v += b;

            if (strlen_n(c) > 1)
            {
                int a = pop_back_n(c);
                v += a;
                u[i++] = a;
                fo << c << a << b << '\n';
            }
            else
            {
                fo << b << '\n';
            }

            u[i++] = b;
        }
        else
            fo << '\n';
    }

    u[i] = '\0';
    fo << v;
    std::cout << u;
    fi.close();
    fo.close();
}
