using System;
using System.Collections.Generic;

namespace ConsoleAppFacade
{
    class MainApp
    {
        public static void Main()
        {
            EducationSystem facade = new EducationSystem();
            facade.AddStudent("Іванов");
            facade.AddTeacher("Петров");
            facade.CreateCourse("ООП");
            // Wait for user 
            Console.Read();
        }
    }

    class Students
    {
        private List<string> students;

        public Students()
        {
            students = new List<string>();
        }

        public void AddStudent(string x)
        {
            students.Add(x);
            Console.WriteLine("Додано студента " + x);
        }
    }

    class Teachers
    {
        private List<string> teachers;

        public Teachers()
        {
            teachers = new List<string>();
        }

        public void AddTeacher(string x)
        {
            teachers.Add(x);
            Console.WriteLine("Додано викладача " + x);
        }
    }

    class Courses
    {
        private List<string> courses;

        public Courses()
        {
            courses = new List<string>();
        }

        public void CreateCourse(string x)
        {
            courses.Add(x);
            Console.WriteLine("Створено курс " + x);
        }
    }

    class EducationSystem
    {
        Teachers teachers;
        Students students;
        Courses courses;

        public EducationSystem()
        {
            teachers = new Teachers();
            students = new Students();
            courses = new Courses();
        }

        public void AddStudent(string x)
        {
            students.AddStudent(x);
        }

        public void AddTeacher(string x)
        {
            teachers.AddTeacher(x);
        }

        public void CreateCourse(string x)
        {
            courses.CreateCourse(x);
        }
    }
}
