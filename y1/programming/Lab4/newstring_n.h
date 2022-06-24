int strlen_n(char* x)
{
    int i = 0;

    while (*x != '\0')
        ++i,
        ++x;

    return i;
}

int strcmp_n(char* x, char* y)
{
    while (*x == *y && *x != '\0' && *y != '\0')
        ++x,
        ++y;

    if (*x < *y)
        return -1;
    else
        return *x > *y;
}

int strncmp_n(char* x, char* y, int z)
{
    while (--z && *x == *y && *x != '\0' && *y != '\0')
        ++x,
        ++y;

    if (*x < *y)
        return -1;
    else
        return *x > *y;
}

char* strchr_n(char* x, char y)
{
    while (*x != '\0' && *x != y)
        ++x;

    return x;
}

char* strcpy_n(char* x, char* y)
{
    char* z = x;

    while (*y != '\0')
        *z = *y,
        ++z,
        ++y;

    *z = '\0';
    return x;
}

char* strncpy_n(char* x, char* y, int z)
{
    char* w = x;

    while (z-- && *y != '\0' && *w != '\0')
        *w = *y,
        ++w,
        ++y;

    *w = '\0';
    return x;
}

char* strcat_n(char* x, char* y)
{
    int n = strlen_n(x), n2 = strlen_n(y);
    char* z = new char[n];
    strcpy_n(z, x);
    x = new char[n + n2];
    strcpy_n(x, z);
    z = x;

    while (*z != '\0')
        ++z;

    while (*y != '\0')
        *z = *y,
        ++z,
        ++y;

    *z = '\0';
    return x;
}

char* strncat_n(char* x, char* y, int w)
{
    int n = strlen_n(x);
    int n2 = strlen_n(y);
    char* z = new char[n];
    strcpy_n(z, x);
    x = new char[n + n2];
    strcpy_n(x, z);
    z = x;

    while (*z != '\0')
        ++z;

    while (w-- && *y != '\0')
        *z = *y,
        ++z,
        ++y;

    *z = '\0';
    return x;
}

char* strstr_n(char* x, char* y)
{
    char* z = nullptr;
    int n = strlen_n(y);

    while (*x != '\0')
    {
        if(*x == *y)
        {
            char* w = y;
            z = x;
            int i = n;

            while (z != '\0' && *z == *w)
                z++,
                w++,
                i--;

            if (i <= 0 || z=='\0')
                break;
        }

        x++;
    }

    return z;
}

char* strpbrk_n(char* x, char* y)
{
    for (; *x != '\0'; ++x)
        for (char* z = y; *z != '\0'; ++z)
            if (*z == *x)
                return x;
    return nullptr;
}

int strspn_n(char* x, char* y)
{
    int i = 0;

    for (const char* z; *x != '\0'; ++x, ++i)
    {
        for (z = y; *z != '\0'; ++z)
            if (*z == *x)
                break;

        if (*z == '\0')
            break;
    }

    return i;
}

int strcspn_n(char* x, char* y)
{
    for (int i = 0; *x != '\0'; ++x, ++i)
        for (char* z = y; *z != '\0'; ++z)
            if (*z == *x)
                return i;
    return 0;
}

int find_last_of_n(char* x, char* y)
{
    int l = strlen_n(y);

    for (char* z = x + strlen_n(x); z != x;)
    {
        --z;

        for (char *w = y + l, *v = z; w != y;)
        {
            --w;

            if (v == x)
                return -1;

            if (w == y)
                return v - x;

            if (*w != *v)
                break;

            --v;
        }
    }

    return -1;
}

int find_first_of_n(char* x, char y)
{
    for (int i = 0; *x != '\0'; ++x, ++i)
        if (*x == y)
            return i;

    return -1;
}

int find_first_not_of_n(char* x, char* y)
{
    for (int i = 0; *x != '\0'; ++x, ++i)
    {
        char* z = y;

        for (; *z != '\0'; ++z)
            if (*z == *x)
                break;
        if (*z == '\0')
            return i;
    }

    return -1;
}

char pop_back_n(char* x)
{
    x = x + strlen_n(x) - 1;
    char z = *x;
    *x = '\0';
    return z;
}

int compare_n(char* x, char* y)
{
    int l1 = strlen_n(x), l2 = strlen_n(y);

    if (l1 == l2)
    {
        for (; *x != '\0'; ++x, ++y)
            if (*x < *y)
                return -1;
            else if (*x > *y)
                return 1;

        return 0;
    }
    else if (l1 < l2)
        return -1;
    else
        return 1;
}
