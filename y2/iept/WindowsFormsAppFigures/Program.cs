using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsAppFigures
{
    public abstract class Figure
    {
        public abstract double getPerimeter();

        public abstract double getArea();
    }

    public class Triangle : Figure
    {
        public double sideA, sideB, sideC;

        public Triangle(double a, double b, double c)
        {
            if (a + b < c && b + c < a && c + a < b && a > 0 && b > 0 && c > 0)
            {
                sideA = a;
                sideB = b;
                sideC = c;
            }
            else
            {
                sideA = Double.NaN;
                sideB = Double.NaN;
                sideC = Double.NaN;
            }
        }

        public override double getPerimeter()
        {
            return sideA + sideB + sideC;
        }

        public override double getArea()
        {
            double p = getPerimeter() / 2;
            return Math.Sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
        }
    }

    public class Circle : Figure
    {
        public double radius;

        public Circle(double r)
        {
            if (r > 0)
            {
                radius = r;
            }
            else
            {
                radius = Double.NaN;
            }
        }

        public override double getPerimeter()
        {
            return Math.PI * 2 * radius;
        }

        public override double getArea()
        {
            return Math.PI * radius * radius;
        }
    }

    public class Rhombus : Figure
    {
        public double sideA, sideB, apexAngle;

        public Rhombus(double a, double b, double x)
        {
            if (a > 0 && b > 0 && x > 0 && x < Math.PI)
            {
                sideA = a;
                sideB = b;
                apexAngle = x;
            }
            else
            {
                sideA = Double.NaN;
                sideB = Double.NaN;
                apexAngle = Double.NaN;
            }
        }

        public override double getPerimeter()
        {
            return 4 * sideA;
        }

        public override double getArea()
        {
            return sideA * sideA * Math.Sin(apexAngle);
        }
    }

    public class Rectangle : Figure
    {
        public double sideA, sideB;

        public Rectangle(double a, double b)
        {
            if (a > 0 && b > 0)
            {
                sideA = a;
                sideB = b;
            }
            else
            {
                sideA = Double.NaN;
                sideB = Double.NaN;
            }
        }

        public override double getPerimeter()
        {
            return 2 * (sideA + sideB);
        }

        public override double getArea()
        {
            return sideA * sideB;
        }
    }

    public class Square : Rectangle
    {
        public Square(double a) : base(a, a)
        {

        }

        public override double getPerimeter()
        {
            return 4 * sideA;
        }

        public override double getArea()
        {
            return sideA * sideA;
        }
    }

    static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
