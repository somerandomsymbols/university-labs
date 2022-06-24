using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsAppTriangle
{
    public class Triangle
    {
        public double sideA, sideB, sideC;

        public Triangle(double a, double b, double c)
        {
            setSides(a, b, c);
        }

        public void setSides(double a, double b, double c)
        {
            if (a + b < c && b + c < a && c + a < b)
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

        public double getPerimeter()
        {
            return sideA + sideB + sideC;
        }

        public double getAngleA()
        {
            return Math.Acos((-sideA * sideA + sideB * sideB + sideC * sideC) / (2 * sideB * sideC));
        }

        public double getAngleB()
        {
            return Math.Acos((sideA * sideA - sideB * sideB + sideC * sideC) / (2 * sideC * sideA));
        }

        public double getAngleC()
        {
            return Math.Acos((sideA * sideA + sideB * sideB - sideC * sideC) / (2 * sideA * sideB));
        }
    }

    public class IsoscelesTriangle : Triangle
    {
        public double area;

        public IsoscelesTriangle(double a, double b) : base(a, b, a)
        {
            area = getArea();
        }

        public double getArea()
        {
            return Math.Sqrt(4 * sideA * sideA - sideB * sideB) * sideB / 4;
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
