#include <bits/stdc++.h>
#include "g2.h"
#include "g2use.h"

void printStudent()
{
    std::cout << "Made by Shvets Misha K-15\nVariant 11:\nCheck if polygonal chain ABCDA is rhombus\n";
    std::cout.flush();
}

std::string getFilePath(std::string default_path)
{
    std::cout << "file path:\n";
    std::cout.flush();
    std::string path;
    std::getline(std::cin, path);

    while (1)
    {
        if (path == "")
            return default_path;

        std::ifstream fi(path);

        if (fi.good())
            return path;
        else
            std::cout << "Wrong file path, try again:\n";
            std::cout.flush();
            std::getline(std::cin, path);
    }
}

main()
{
    printStudent();
    std::cout << "Input ";
    std::string fi = getFilePath("in.txt");
    std::cout << "Output ";
    std::string fo = getFilePath("out.txt");
    doMagic(fi, fo);
}
