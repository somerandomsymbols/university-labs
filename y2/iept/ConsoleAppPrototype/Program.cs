using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleAppPrototype
{
    class Program
    {
        static void Main(string[] args)
        {
            Prototype prototype = new Triangle(1, 3, 4, 5);
            Prototype clone = prototype.Clone();
            prototype = new Triangle(2, 6, 8, 10);
            clone = prototype.Clone();
        }
    }
    abstract class Prototype
    {
        public int Id { get; private set; }
        public Prototype(int id)
        {
            this.Id = id;
        }
        public abstract Prototype Clone();
    }

    class ConcretePrototype1 : Prototype
    {
        public ConcretePrototype1(int id)
        : base(id)
        { }
        public override Prototype Clone()
        {
            return new ConcretePrototype1(Id);
        }
    }

    class ConcretePrototype2 : Prototype
    {
        public ConcretePrototype2(int id)
        : base(id)
        { }
        public override Prototype Clone()
        {
            return new ConcretePrototype2(Id);
        }
    }

    class Triangle : Prototype
    {
        private double a;
        private double b;
        private double c;

        public Triangle(int id, double x, double y, double z)
        : base(id)
        {
            a = x;
            b = y;
            c = z;
        }

        public override Prototype Clone()
        {
            return new Triangle(Id, a, b, c);
        }
    }
}
