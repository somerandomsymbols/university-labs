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
                values[i][j] = x(i, j);

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



int main()
{
    const int n = 9;
    double b[n + 1] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 };
    double c[n + 1] = { 1, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
    double a[n + 1] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    double f[n + 1] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    Matrix<double> MA(10, 10), MB(10);

    for (int i = 0; i < 10; ++i)
    {
        MB(0, i) = f[i];

        for (int j = 0; j < 10; ++j)
        {
            if (i == j)
                MA(i, j) = c[i];

            if (i == j + 1)
                MA(i, j) = b[i - 1];

            if (i == j - 1)
                MA(i, j) = a[i + 1];
        }
    }

    cout << "A:\n";
    print(MA);
    cout << "b:\n";
    print(MB);
    Matrix<double> MAM1(10, 10);

    const int N = n + 1;
    double d[N + 2];
    double th[N + 2], ph[N + 2];

    d[0] = 1;
    d[1] = c[0];

    for (int i = 2; i <= N; ++i)
        d[i] = c[i - 1] * d[i - 1] - a[i - 1] * b[i - 2] * d[i - 2];

    ph[N + 1] = 1;
    ph[N] = c[n];
    th[0] = 1;
    th[1] = c[0];

    for (int i = 2; i <= N; ++i)
        th[i] = c[i - 1] * th[i - 1] - a[i - 1] * b[i - 2] * th[i - 2];

    for (int i = N - 1; i >= 1; --i)
        ph[i] = c[i - 1] * ph[i + 1] - a[i] * b[i - 1] * ph[i + 2];

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            if (i < j)
            {
                MAM1(j - 1, i - 1) = (i % 2 == j % 2 ? 1 : -1) * th[i - 1] * ph[j + 1] / th[N];

                for (int h = i; h <= j - 1; ++h)
                    MAM1(j - 1, i - 1) *= b[h - 1];
            }

            if (i == j)
                MAM1(j - 1, i - 1) = th[i - 1] * ph[j + 1] / th[N];

            if (i > j)
            {
                MAM1(j - 1, i - 1) = (i % 2 == j % 2 ? 1 : -1) * th[j - 1] * ph[i + 1] / th[N];

                for (int h = j; h <= i - 1; ++h)
                    MAM1(j - 1, i - 1) *= a[h];
            }
        }

	for (int i = 0; i <= n; ++i)
	{
		c[i] = -c[i];
		f[i] = -f[i];
	}

	double A[n + 1];
	double B[n + 1];

	A[1] = b[0] / c[0];
	B[1] = f[0] / c[0];

	for (int i = 1; i < n; ++i)
	{
		A[i + 1] = b[i] / (c[i] - a[i] * A[i]);
		B[i + 1] = (f[i] + a[i] * B[i]) / (c[i] - a[i] * A[i]);
	}

	double y[n + 1];

	y[n] = (f[n] + a[n] * B[n]) / (c[n] - a[n] * A[n]);

	for (int i = n - 1; i >= 0; --i)
	{
		y[i] = A[i + 1] * y[i + 1] + B[i + 1];
	}

    Matrix<double> E10(10, 10), IC(10, 10), IB(10,10), If(10);

    for (int i = 0; i < 10; ++i)
        E10(i, i) = 1;

    IC = E10 * 0.3;

    IB = E10 - IC * MA;
    If = IC * MB;

	cout << "\nalpha: ";

	for (int i = 0; i <= n; ++i)
		cout << A[i] << ' ';

	cout << "\nbeta: ";

	for (int i = 0; i <= n; ++i)
		cout << B[i] << ' ';

	cout << "\ny: ";

	for (int i = 0; i <= n; ++i)
		cout << y[i] << ' ';

    cout << "\nC:\n";
    print(IC);
    cout << "\nB:\n";
    print(IB);
    cout << "\nf:\n";
    print(If);
    Matrix<double> X0(10);

    for (int i = 0; i <= 100000; ++i)
    {
        X0 = IB * X0 + If;

        if (i % 10000 == 0)
        {
            cout << "i = " << i << ": ";
            print(X0.Transpose());
        }
    }

    cout << "\ndet(A) = " << d[N] << endl;
    cout << "A^-1:\n";
    print(MAM1);
    cout << "cond(A) = " << MA.Norm() * MAM1.Norm() << endl;

	return 0;
}