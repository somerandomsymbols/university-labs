#include <cmath>

struct vec2d
{
    double x,y;

    vec2d()
    {
        x = 0;
        y = 0;
    }

    vec2d(double a, double b)
    {
        x = a;
        y = b;
    }

    bool operator==(vec2d a)
    {
        return x == a.x && y == a.y;
    }

    bool operator!=(vec2d a)
    {
        return x != a.x || y != a.y;
    }

    vec2d operator+=(vec2d a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }

    vec2d operator+(vec2d a)
    {
        a.x += x;
        a.y += y;
        return a;
    }

    vec2d operator-=(vec2d a)
    {
        x -= a.x;
        y -= a.y;
        return *this;
    }

    vec2d operator-(vec2d a)
    {
        a.x = x - a.x;
        a.y = y - a.y;
        return a;
    }

    double operator*(vec2d a)
    {
        return x * a.x + y * a.y;
    }

    vec2d operator*=(double a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    vec2d operator*(double a)
    {
        vec2d b = *this;
        b.x *= a;
        b.y *= a;
        return b;
    }

    double len()
    {
        return sqrt(x * x + y * y);
    }

    bool col(vec2d a)
    {
        return len() * a.len() == *this * a;
    }

    vec2d norm()
    {
        double a = len();
        if (a != 0)
            return vec2d(x / a, y / a);
        else
            return vec2d(0, 0);
    }
};


struct vec3d
{
    double x,y,z;

    vec3d()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vec3d(vec2d a)
    {
        x = a.x;
        y = a.y;
        z = 0;
    }

    vec3d(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    bool operator==(vec3d a)
    {
        return x == a.x && y == a.y && z == a.z;
    }

    bool operator!=(vec3d a)
    {
        return x != a.x || y != a.y || z != a.z;
    }

    vec3d operator+=(vec3d a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    vec3d operator+(vec3d a)
    {
        a.x += x;
        a.y += y;
        a.z += z;
        return a;
    }

    vec3d operator-=(vec3d a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    vec3d operator-(vec3d a)
    {
        a.x = x - a.x;
        a.y = y - a.y;
        a.z = z - a.z;
        return a;
    }

    double operator*(vec3d a)
    {
        return x * a.x + y * a.y + z * a.z;
    }

    vec3d operator*=(double a)
    {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    vec3d operator*(double a)
    {
        vec3d b = *this;
        b.x *= a;
        b.y *= a;
        b.z *= a;
        return b;
    }

    vec3d operator&=(vec3d a)
    {
        a = vec3d(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }

    vec3d operator&(vec3d a)
    {
        a = vec3d(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
        return a;
    }

    double len()
    {
        return sqrt(x * x + y * y + z * z);
    }

    bool col(vec3d a)
    {
        return len() * a.len() == *this * a;
    }

    vec3d norm()
    {
        double a = len();

        if (a != 0)
            return vec3d(x / a, y / a, z / a);
        else
            return vec3d(0, 0, 0);
    }
};
