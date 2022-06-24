#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n = 1000;
    ofstream fo;
    fo.open("input10X.txt");

    fo << n << " " << n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fo << " 1";

    fo << endl << n << " " << n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fo << " 1";

    fo << endl;
}
