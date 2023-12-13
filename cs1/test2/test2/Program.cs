using System.Globalization;

namespace test2;

internal class Program
{
    public static void Main(string[] args)
    {
        CultureInfo.CurrentCulture = CultureInfo.InvariantCulture;
        CultureInfo.CurrentUICulture = CultureInfo.InvariantCulture;

        StudentCollection students = new StudentCollection();
        students.Load("students.csv");

        students.Sort();

        Console.WriteLine("Počty výskytů jednotlivých skóre");
        Console.WriteLine("----------------------------------");

        students.PrintMathScoreStats();
        
        Console.WriteLine();
        Console.WriteLine("Studentky bez přípravného kurzu a s nízkým skóre");
        Console.WriteLine("----------------------------------");
        foreach (Student student in students)
        {
            Console.WriteLine(student.Name);
        }

        students.Save("students.json");
    }
}