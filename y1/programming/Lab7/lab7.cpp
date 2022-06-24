#include <bits/stdc++.h>
#include "vec.h"

main()
{
    std::cout << "Shvets Misha K-15\nType four vectors in the format:\nx1 x2 x3 y1 y2 y3\na1 a2 a3 b1 b2 b3\n";
    double x1,x2,x3,y1,y2,y3,a1,a2,a3,b1,b2,b3;

    while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&x2,&x3,&y1,&y2,&y3,&a1,&a2,&a3,&b1,&b2,&b3) != 12)
        std::cout << "Wrong input!\n";

    vec3d x(x1,x2,x3), y(y1,y2,y3), a(a1,a2,a3), b(b1,b2,b3);

    if ((x & y).len() == 0 || (a & b).len() == 0)
        std::cout << "Multiple planes correspond to the pair of vectors given\n";
    else if ((x & y).col(a & b))
        std::cout << "Plane(x,y) is parallel to plane(a,b)\n";
    else
        std::cout << "Plane(x,y) is not parallel to plane(a,b)\n";
}
