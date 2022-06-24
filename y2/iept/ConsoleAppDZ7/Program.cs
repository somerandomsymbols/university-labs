using System;
using System.Collections.Generic;

namespace ConsoleAppDZ7
{
    /*
     * Task 1: Single Responsibility Principle
     */

    class Item
    {

    }
    class ListOfItems
    {
        private List<Item> itemList;
        internal List<Item> ItemList
        {
            get
            {
                return itemList;
            }
            set
            {
                itemList = value;
            }
        }

        public void CalculateTotalSum() {/*...*/}
        public void GetItems() {/*...*/}
        public void GetItemCount() {/*...*/}
        public void AddItem(Item item) {/*...*/}
        public void DeleteItem(Item item) {/*...*/}
    }
    class Order
    {
        public void PrintOrder() {/*...*/}
        public void ShowOrder() {/*...*/}
    }

    class OrderLoader
    {
        public void Load(Order order, string path) {/*...*/}
        public void Save(Order order, string path) {/*...*/}
        public void Update(Order order, string path) {/*...*/}
        public void Delete(Order order) {/*...*/}
    }

    /*
     * Task 2
     */

    class Email
    {
        public String Theme { get; set; }
        public String From { get; set; }
        public String To { get; set; }
    }

    class EmailSender
    {
        public void Send(Email email)
        {
            // ... sending...
            Console.WriteLine("Email from '" + email.From + "' to '" + email.To + "' was send");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Email e1 = new Email()
            {
                From = "Me",
                To = "Vasya",
                Theme = "Who are you ? "
            };
            Email e2 = new Email()
            {
                From = "Vasya",
                To = "Me",
                Theme = "vacuum cleaners!"
            };
            Email e3 = new Email()
            {
                From = "Kolya",
                To = "Vasya",
                Theme = "No! Thanks!"
            };
            Email e4 = new Email()
            {
                From = "Vasya",
                To = "Me",
                Theme = "washing machines!"
            };
            Email e5 = new Email()
            {
                From = "Me",
                To = "Vasya",
                Theme = "Yes"
            };
            Email e6 = new Email()
            {
                From = "Vasya",
                To = "Petya",
                Theme = "+2"
            };
            EmailSender es = new EmailSender();
            es.Send(e1);
            es.Send(e2);
            es.Send(e3);
            es.Send(e4);
            es.Send(e5);
            es.Send(e6);
            Console.ReadKey();
        }
    }

    /*
     * Task 3
     */

    class Rectangle
    {
        public virtual int Width { get; set; }
        public virtual int Height { get; set; }
        public int GetRectangleArea()
        {
            return Width * Height;
        }
    }

    //квадрат наслідується від прямокутника!!!
    class Square : Rectangle
    {
        public override int Width
        {
            get { return base.Width; }
            set
            {
                base.Height = value;
                base.Width = value;
            }
        }
        public override int Height
        {
            get { return base.Height; }
            set
            {
                base.Height = value;
                base.Width = value;
            }
        }
        class Program
        {
            static void Main(string[] args)
            {
                Rectangle rect = new Square();
                rect.Width = 5;
                rect.Height = 10;
                Console.WriteLine(rect.GetRectangleArea());
                Console.ReadKey();
            }
        }
    }

    /*
     * Task 4: Interface Segregation Principle
     */

    interface IOnSaleItem
    {
        void ApplyDiscount(String discount);
        void ApplyPromocode(String promocode);
    }

    interface IColoredItem
    {
        void SetColor(byte color);
    }

    interface ISizedItem
    {
        void SetSize(byte size);
    }

    interface IValuableItem
    {
        void SetPrice(double price);
    }
}
