using Database;

namespace cv4
{
    internal class Program
    {
        static void Main(string[] args)
        {
            GenderEnum gender = GenderEnum.MALE;

            Person person = new Person()
            {
                Name = "Ivo",
                Age = 5,
                Gender = gender
            };

            PopulationDatabase people = new PopulationDatabase();
            people.Add(person);
            people.Add(new Person() { Name = "Jan", Age = 25, Gender = GenderEnum.MALE });
            people.Add(new Person() { Name = "Jana", Age = 67, Gender = GenderEnum.FEMALE });

            Console.WriteLine(people.ToString());
        }
    }
}
