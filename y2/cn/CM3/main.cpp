#include<iostream>
#include<vector>

using namespace std;

template<typename T>
class Matrix
{
public:
    vector<vector<T>> values;
    const unsigned rows, columns;

    Matrix(unsigned x = 1, unsigned y = 1) : rows(x), columns(y)
    {
        if (x == 0 || y == 0)
            throw invalid_argument("");

        values.resize(columns);

        for (int i = 0; i < columns; ++i)
            values[i].resize(rows);
    }

    Matrix(const Matrix<T>& x) : rows(x.rows), columns(x.columns)
    {
        values = x.values;
    }

    Matrix& operator=(const vector<vector<T>>& x)
    {
        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < rows; ++j)
                values[i][j] = x[i][j];

        return *this;
    }

    Matrix& operator=(const Matrix<T>& x)
    {
        if (rows != x.rows || columns != x.columns)
            throw invalid_argument("");

        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < rows; ++j)
                values[i][j] = x.values[i][j];

        return *this;
    }

    T& operator()(int x, int y)
    {
        return values[x][y];
    }

    T operator()(int x, int y) const
    {
        return values[x][y];
    }

    Matrix<T>& operator+=(const Matrix<T>& x)
    {
        if (rows != x.rows || columns != x.columns)
            throw invalid_argument("");

        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < rows; ++j)
                values[i][j] += x(i, j);

        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& x) const
    {
        Matrix<T> y = *this;

        y += x;

        return y;
    }

    Matrix<T>& operator-=(const Matrix<T>& x)
    {
        if (rows != x.rows || columns != x.columns)
            throw invalid_argument("");

        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < rows; ++j)
                values[i][j] -= x(i, j);

        return *this;
    }

    Matrix<T> operator-(const Matrix<T>& x) const
    {
        Matrix<T> y = *this;

        y -= x;

        return y;
    }

    Matrix<T>& operator*=(const T& x)
    {
        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < rows; ++j)
                values[i][j] *= x;

        return *this;
    }

    Matrix<T> operator*(const T& x) const
    {
        Matrix<T> y = *this;

        y *= x;

        return y;
    }

    Matrix<T> operator*(const Matrix<T>& x) const
    {
        Matrix<T> y(rows, x.columns);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < x.columns; ++j)
            {
                y(j, i) = 0;

                for (int h = 0; h < columns; ++h)
                    y(j, i) += values[h][i] * x(j, h);
            }

        return y;
    }

    T Norm() const
    {
        T x = 0;

        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < rows; ++j)
                x += values[i][j] * values[i][j];

        return sqrt(x);
    }

    T tNorm() const
    {
        T x = 0;

        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < rows; ++j)
                if (i != j)
                    x += values[i][j] * values[i][j];

        return x;
    }

    T Det() const;

    T Min(int x, int y) const;

    Matrix<T> Transpose() const;

    Matrix<T> operator~() const;
};

template<typename T>
void print(const Matrix<T>& x)
{
    for (int i = 0; i < x.rows; ++i)
    {
        for (int j = 0; j < x.columns; ++j)
        {
            cout << x(j, i) << ' ';
        }

        cout << endl;
    }
}

template<typename T>
T Matrix<T>::Det() const
{
    if (rows != columns)
        throw invalid_argument("");

    if (rows == 1)
        return values[0][0];

    T x = 0;

    for (int i = rows - 1; i >= 0; --i)
    {
        x = values[0][i] * Min(0, i) - x;
        if (rows > 9)
            cout << '|';
    }
    if (rows > 9)
        cout << endl;

    return x;
}

template<typename T>
T Matrix<T>::Min(int x, int y) const
{
    if (x < 0 || y < 0 || x >= rows || y >= columns || rows == 1 || columns != rows)
        throw invalid_argument("");

    Matrix<T> z(rows - 1, rows - 1);

    for (int i = 0; i < rows - 1; ++i)
    {
        for (int j = 0; j < rows - 1; ++j)
        {
            int i1 = i >= x ? i + 1 : i;
            int j1 = j >= y ? j + 1 : j;

            z(i, j) = values[i1][j1];
        }
    }

    return z.Det();
}

template<typename T>
Matrix<T> Matrix<T>::Transpose() const
{
    Matrix<T> y(columns, rows);

    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < rows; ++j)
            y(j, i) = values[i][j];

    return y;
}

template<typename T>
Matrix<T> Matrix<T>::operator~() const
{
    T d = Det();
    if (rows != columns || d == 0)
        throw invalid_argument("");

    Matrix<T> y(rows, rows);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < rows; ++j)
            y(i, j) = (i % 2 == j % 2 ? 1 : -1) * Min(j, i);

        if (rows > 9)
            cout << 'l';
    }
    if (rows > 9)
        cout << endl;

    y *= 1 / d;

    return y.Transpose();
}

double stepin(const Matrix<double> &A, double eps)
{
    double m0, mk;
    Matrix<double> X0(5), XK(5), E0(5), m(1);
    X0 = { { 1, 1, 1, 1, 1 } };
    E0 = X0 * (1 / X0.Norm());
    cout << "\nx0:\n";
    print(X0);
    cout << "\ne0:\n";
    print(E0);
    XK = A * E0;
    cout << "\nx1:\n";
    print(XK);
    m = E0.Transpose() * XK;
    mk = m(0, 0);
    cout << "\nm0:\n" << mk;
    int i = 1;

    do
    {

        m0 = mk;
        X0 = XK;
        E0 = X0 * (1 / X0.Norm());
        XK = A * E0;
        cout << "\ne" << i <<":\n";
        print(E0);
        cout << "\nx" << i << ":\n";
        print(X0);
        m = E0.Transpose() * XK;
        mk = m(0, 0);
        cout << "\nm" << i << ":\n" << mk << endl;
        ++i;
    } while (abs(m0 - mk) >= eps);

    return mk;
}


Matrix<double> G(int i, int j, double th)
{
    Matrix<double> E5(5, 5);
    E5 = { { 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 1 } };

    E5(i, i) = cos(th);
    E5(j, j) = cos(th);
    E5(i, j) = sin(th);
    E5(j, i) = -sin(th);

    return E5;
}

Matrix<double> jacobi(Matrix<double> A, double eps)
{
    Matrix<double> G5(5, 5);
    cout << "\nA0:\n";
    print(A);
    int i = 1;

    while (A.tNorm() > eps)
    {
        int mi = 1, mj = 0;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                if (i != j && abs(A(i, j)) > abs(A(mi, mj)))
                {
                    mi = i;
                    mj = j;
                }

        G5 = G(mi, mj, atan(2 * A(mi, mj) / (A(mj, mj) - A(mi, mi))) / 2);
        cout << "\nU" << i << ":\n";
        print(G5);
        A = G5 * A * G5.Transpose();
        cout << "\nA" << i << ":\n";
        print(A);
        ++i;
    }

    return A;
}

int main()
{
    double eps = 1e-4, m0 = 0, mk = 1;
    Matrix<double> A(5, 5),X1(5), E5(5, 5);
    A = { { 6.68, 1.12, 0.95, 1.32, 0.83 },
        { 1.12, 2.78, 2.12, 0.57, 0.91 },
        { 0.95, 2.12, 7.63, 1.29, 1.57 },
        { 1.32, 0.57, 1.29, 3.07, 1.25 },
        { 0.83, 0.91, 1.57, 1.25, 6.71 } };
    E5 = { { 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 1 } };

    double lmaxa = stepin(A, 1e-4);

    cout << "\n----------------------------------------------------------\n";

    double lmaxb = stepin(E5 * lmaxa - A, 1e-4);

    cout << "\n----------------------------------------------------------\n";

    cout << "\nl1: " << lmaxa << "\nl5: " << lmaxa - lmaxb << endl;

    cout << "\n----------------------------------------------------------\n";

    jacobi(A, 1e-4);

    return 0;
}