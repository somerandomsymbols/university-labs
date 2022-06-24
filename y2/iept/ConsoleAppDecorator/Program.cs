using System;

namespace ConsoleAppDecorator
{
    class MainApp
    {
        static void Main()
        {
            // Create ConcreteComponent and two Decorators
            Tree t = new Tree();
            TreeDecoration d1 = new TreeDecoration();
            d1.SetDecoration("Куля");
            TreeLights d2 = new TreeLights();

            // Link decorators
            d1.SetComponent(t);
            d2.SetComponent(d1);

            d2.Operation();

            // Wait for user
            Console.Read();
        }
    }
    // "Component"
    abstract class Component
    {
        public abstract void Operation();
    }

    class Tree : Component
    {
        public override void Operation()
        {
            Console.WriteLine("Ялинка");
        }
    }

    // "Decorator"
    abstract class Decorator : Component
    {
        protected Component component;

        public void SetComponent(Component component)
        {
            this.component = component;
        }
        public override void Operation()
        {
            if (component != null)
            {
                component.Operation();
            }
        }
    }

    class TreeDecoration : Decorator
    {
        private string decoration;

        public void SetDecoration(string x)
        {
            decoration = x;
        }

        public override void Operation()
        {
            base.Operation();
            Console.WriteLine(decoration);
        }
    }

    class TreeLights : Decorator
    {
        public override void Operation()
        {
            base.Operation();
            AddedBehavior();
        }

        void AddedBehavior()
        {
            Console.WriteLine("Ялинка світиться");
        }
    }
}
