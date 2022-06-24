#include "array.h"

int main()
{
    std::cout << "Made by Shvets Misha K-15\n";
    bool f = 1;

    while (f)
    {
        std::cout << "N = " + std::to_string(getN()) + " \n"
        << "Press \"1\" to fill array from keyboard\n"
        << "Press \"2\" to fill array with pseudorandom numbers\n"
        << "Press \"3\" to change N (0 < N < 2^31)\n"
        << "Press any other key to exit\n";
        switch (_getch())
        {
        case '1':
            std::cout << "Print " + std::to_string(getN()) + " new values for array\n";
            if (!input_array())
                std::cout << "Wrong array input\n";
            else
                f = 0;
            break;
        case '2':
            randomize_array();
            std::cout << "Array successfully randomized\n";
            f = 0;
            break;
        case '3':
            std::cout << "Set new value for N\n";
            input_n();
            break;
        default:
            std::cout << "Exit";
            return 0;
        }
    }

    f = 1;



    while (f)
    {
        std::cout << "Press \"1\" to add element after first min and before last max\n"
        << "Press \"2\" to quicksort array\n"
        << "Press \"Q\" to print array and stop the program\n";

        switch (_getch())
        {
        case '1':
            std::cout << "Set value for element (-2^31 <= x < 2^31)\n";
            input_element();
            break;
        case '2':
            sort_array();
            std::cout << "Array successfully sorted\n";
            break;
        case 'Q':
        case 'q':
            std::cout << "Exit\n";
            f = 0;
            break;
        default:
            std::cout << "Unknown option\n";
        }
    }

    if (!print_array())
        return -1;

    return 0;
}
