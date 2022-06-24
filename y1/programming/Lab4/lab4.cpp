#include "newstring_n.h"
#include <iostream>

main()
{
    char a[100] = "abcdef", b[100] = "badcdef";

    std::cout << strlen_n(a) << '\n' << strlen_n(b) << '\n';
    std::cout << strncpy_n(a, b, 2) << '\n';
    std::cout << a;// << (a+b).tstr() << '\n' << (a == b) << '\n' << (a != b) << '\n';
}
