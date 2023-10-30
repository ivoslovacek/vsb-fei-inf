using System;

namespace cv6
{
    public class Person
    {
        public readonly string Name;
        public int Age { get; set; }

        public Person(string name, int age)
        {
            this.Name = name;
            this.Age = age;
        }

        public virtual void PrintInfo()
        {
            System.Console.WriteLine($"Name: {this.Name}, Age: {this.Age}");
        }
    }
}
