#include <iostream>
#include <vector>

using namespace std;

const double a = 0;
const double b = 1;

double f(double x)
{
	return cos(x * x);
}

double F(double x)
{
	if (x == 0)
		return 0;
	return (x-1)/sqrt(sinh(x))+1/sqrt(x);
}

int main()
{
	int M = 30;
	double h = (b - a) / M;
	double I = 0;
	double I2 = 0;

	for (int i = 0; i < M; ++i)
	{
		I += f(a + (i + 1) * h) + f(a + i * h);
		I2 += f(a + (i + 0.5) * h);
	}
	
	I /= 2;
	I2 += I;
	I *= h;
	I2 *= h / 2;

	cout << "Tr: In=" << I << " I2n=" << I2 << " R=" << abs(I - I2) << " I=" << (I2+(I2-I)/3) << endl;

	M = 20;
	h = (b - a) / M;
	I = 0;
	I2 = 0;

	for (int i = 0; i < M; ++i)
	{
		I += 7 * (f(a + (i + 1.0) * h) + f(a + i * h)) + 12 * f(a + (i + 0.5) * h) + 32 * (f(a + (i + 0.75) * h) + f(a + (i + 0.25) * h));
		I2 += 7 * (f(a + (i + 1.0) * h) + f(a + i * h)) + 14 * f(a + (i + 0.5) * h) + 32 * (f(a + (i + 0.125) * h) + f(a + (i + 0.375) * h) + f(a + (i + 0.625) * h) + f(a + (i + 0.875) * h)) + 12 * (f(a + (i + 0.75) * h) + f(a + (i + 0.25) * h));
	}

	I *= h/90;
	I2 *= h/180;

	cout << "Bo: In=" << I << " I2n=" << I2 << " R=" << abs(I - I2)/31 << " I=" << (I2 + (I2 - I) / 31) << endl << "--------------------" << endl;

	I = 1;
	I2 = 0;
	M = 1;

	while (abs(I - I2) > 1e-6)
	{
		M *= 2;
		h = (b - a) / M;
		I = 0;
		I2 = 0;

		for (int i = 0; i < M; ++i)
		{
			I += F(a + (i + 1) * h) + F(a + i * h);
			I2 += F(a + (i + 0.5) * h);
		}

		I /= 2;
		I2 += I;
		I *= h;
		I2 *= h / 2;

		cout << "In=" << I << " I2n=" << I2 << " R=" << abs(I - I2) << " I=" << (I2 + (I2 - I) / 3) << endl;
	}

	return 0;
}