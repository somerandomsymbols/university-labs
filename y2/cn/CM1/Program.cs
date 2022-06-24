using System;
using System.Collections.Generic;

namespace CM1
{
    class Program
    {
        static double F(double x)
        {
            return x * x * x * x + 2.0 * x * x - 6.0 * x + 2.0;
        }

        static double dF(double x)
        {
            return 4.0 * x * x * x + 4.0 * x - 6.0;
        }

        static double d2F(double x)
        {
            return 12.0 * x * x + 4.0;
        }

        static List<double> Newton(Func<double, double> f, Func<double, double> df, double x0, int i)
        {
            List<double> res = new List<double> { x0 };

            while (--i >= 0 && Math.Abs(f(x0) / df(x0)) > 1e-6)
            {
                x0 -= f(x0) / df(x0);
                res.Add(x0);
            }

            return res;
        }

        static List<double> Secant(Func<double, double> f, double x0, double x1, int i)
        {
            List<double> res = new List<double> { x0, x1 };

            while (--i >= 0 && Math.Abs(x0 - x1) > 1e-6)
            {
                res.Add(x1 - (x1 - x0) * f(x1) / (f(x1) - f(x0)));
                x0 = x1;
                x1 = res[res.Count - 1];
            }

            return res;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Newton:");

            List<double> list0 = Newton(dF, d2F, 1.0, 15);

            foreach (var i in list0)
                Console.WriteLine(i);

            Console.WriteLine("-----------------");

            double xv = list0[list0.Count - 1];

            List<double> list1 = Newton(F, dF, xv / 2.0, 15);

            foreach (var i in list1)
                Console.WriteLine(i);

            Console.WriteLine("-----------------");

            List<double> list2 = Newton(F, dF, 1.0 + xv / 2.0, 15);

            foreach (var i in list2)
                Console.WriteLine(i);

            Console.WriteLine(String.Format("Roots: {0:F6}  {1:F6}", list1[list1.Count - 1], list2[list2.Count - 1]));

            Console.WriteLine("Secant:");

            list0 = Secant(dF, 0.0, 2.0, 15);

            foreach (var i in list0)
                Console.WriteLine(i);

            Console.WriteLine("-----------------");

            xv = list0[list0.Count - 1];

            list1 = Secant(F, 0.0, xv, 15);

            foreach (var i in list1)
                Console.WriteLine(i);

            Console.WriteLine("-----------------");

            list2 = Secant(F, xv, 2.0, 15);

            foreach (var i in list2)
                Console.WriteLine(i);

            Console.WriteLine(String.Format("Roots: {0:F6}  {1:F6}", list1[list1.Count - 1], list2[list2.Count - 1]));
        }
    }
}
