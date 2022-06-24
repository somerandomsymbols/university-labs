using System;
using System.Collections.Generic;
using System.Transactions;

namespace ConsoleAppStudents
{
    public abstract class Student
    {
        public string name;
        public string state;

        public Student(string n)
        {
            name = n;
            state = "";
        }

        public abstract void Study();

        public void Read()
        {
            state += "Read";
        }

        public void Write()
        {
            state += "Write";
        }

        public void Relax()
        {
            state += "Relax";
        }

        public override string ToString()
        {
            return $"Name: '{name}' State: {state}";
        }
    }

    public class GoodStudent : Student
    {
        public GoodStudent(string x) : base(x)
        {
            state = "good";
        }

        public override void Study()
        {
            Read();
            Write();
            Read();
            Write();
            Relax();
        }
    }

    public class BadStudent : Student
    {
        public BadStudent(string n) : base(n)
        {
            state = "bad";
        }

        public override void Study()
        {
            Relax();
            Relax();
            Relax();
            Relax();
            Read();
        }
    }

    public class Group
    {
        public string name;
        public List<Student> students;

        public Group(string n)
        {
            name = n;
            students = new List<Student>();
        }

        public void AddStudent(Student st)
        {
            students.Add(st);
        }

        public void Study()
        {
            foreach (Student i in students)
            {
                i.Study();
            }
        }

        public string GetInfo()
        {
            string s = "Group name: " + name + " Students list: {";

            foreach (Student i in students)
            {
                s += "'" + i.name + "', ";
            }

            return s.Substring(0, s.Length - 2) + "}";
        }

        public string GetFullInfo()
        {
            string s = "Group name: " + name + " Students list: {";

            foreach (Student i in students)
            {
                s += i + ", ";
            }

            return s.Substring(0, s.Length - 2) + "}";
        }

        public override string ToString()
        {
            return GetFullInfo();
        }
    }

    class Program
    {
        static Group InputGroup()
        {
            Console.WriteLine("Input group name:");
            Group g = new Group(Console.ReadLine());
            return g;
        }

        static Student InputStudent()
        {
            Console.WriteLine("Input student name:");
            string name = Console.ReadLine();
            Console.WriteLine("Now input word 'BAD' (no quotes) for bad student or 'GOOD' for good:");
            string type = Console.ReadLine();

            while (type != "BAD" && type != "GOOD")
            {
                Console.WriteLine($"Incorrect type '{type}', try again:");
                type = Console.ReadLine();
            }

            if (type == "BAD")
            {
                BadStudent student = new BadStudent(name);
                return student;
            }
            else
            {
                GoodStudent student = new GoodStudent(name);
                return student;
            }
        }

        static void InputStudentIntoGroup(Group g)
        {
            g.AddStudent(InputStudent());
        }

        static void Main(string[] args)
        {
            Group g = InputGroup();
            InputStudentIntoGroup(g);
            InputStudentIntoGroup(g);
            Console.WriteLine(g.GetInfo());
            g.Study();
            InputStudentIntoGroup(g);
            Console.WriteLine(g);
        }
    }
}
