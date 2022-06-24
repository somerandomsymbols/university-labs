using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsAppTriangles2
{
    public abstract class Triangle
    {
        public double sideA, sideB, apexAngle;

        public Triangle(double a, double b, double x)
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

        public abstract double getPerimeter();

        public abstract double getArea();
    }

    public abstract class RightTriangle : Triangle
    {
        public RightTriangle(double a, double b) : base(a, b, Math.PI / 2)
        {

        }

        public override double getPerimeter()
        {
            return sideA + sideB + Math.Sqrt(sideA * sideA + sideB * sideB);
        }

        public override double getArea()
        {
            return sideA * sideB / 2;
        }
    }

    public abstract class IsoscelesTriangle : Triangle
    {
        public IsoscelesTriangle(double a, double x) : base(a, a, x)
        {

        }

        public override double getPerimeter()
        {
            return 2 * sideA * (1 + Math.Sin(apexAngle / 2));
        }

        public override double getArea()
        {
            return sideA * sideA * Math.Sin(apexAngle) / 2;
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
