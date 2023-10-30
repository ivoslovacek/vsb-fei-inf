using System;

namespace cv6
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Population population = new Population();
            population.Add(new Secretary("Ana", 30));
            population.Add(new Manager("Petr", 40));
            population.Add(new Worker("Tomáš", 25)
            {
                HoursWorked = 90
            });
            population.Add(new Worker("Monika", 50)
            {
                HoursWorked = 200
            });


            population.Add(new Unemployed("Ondra", 50));

            Console.WriteLine("Zaměstnanci:");
            population.PrintEmployeesWithSallary();

            Console.WriteLine("Nezaměstnaní:");
            population.PrintUnemployed();

            Console.Write("Osoba s nejvyšším platem:");
            var person = population.GetPersonWithHighestSallary();
            person.PrintInfo();
            Console.WriteLine($"Plat: {person.GetSalary()}");



            var hourlySallaryEmployees = population.GetHorlySallaryEmployees();
            population.IncreaseHourlySallary(hourlySallaryEmployees, 20);
        }
    }
}
