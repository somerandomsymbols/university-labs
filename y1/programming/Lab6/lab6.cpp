#include "vec.h"
#include <bits/stdc++.h>

using namespace std;

main()
{
    vec3d a(1,0,0);
    vec2d b(0,2);
    vec3d d = a - b, f = d.norm();
    double e = a * b;
    cout << '(' << d.x << ',' << d.y << ',' << d.z << ')' << endl << '(' << f.x << ',' << f.y << ',' << f.z << ')' << endl;
}
