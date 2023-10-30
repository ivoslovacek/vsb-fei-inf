namespace cv6
{
    public class Population
    {
        private Person[] persons = new Person[3];
        private int personCount = 0;

        public void Add(Person person)
        {
            if (this.personCount == this.persons.Length)
            {
                Array.Resize(ref this.persons, 2 * this.personCount);
            }

            this.persons[personCount] = person;
            this.personCount++;
        }

        public void PrintUnemployed()
        {
            for (int i = 0; i < this.personCount; i++)
            {
                if (this.persons[i] is Unemployed)
                {
                    this.persons[i].PrintInfo();
                }
            }
        }

        public void PrintEmployeesWithSallary()
        {
            for (int i = 0; i < this.personCount; i++)
            {
                if (this.persons[i] is Employee employee)
                {
                    this.persons[i].PrintInfo();
                    Console.WriteLine(employee.GetSallary());
                }
            }
        }

        public Employee GetPersonWithHighestSallary()
        {
            Employee tmp = null;

            for (int i = 0; i < this.personCount; i++)
            {
                if (this.persons[i] is Employee employee)
                {
                    this.persons[i].PrintInfo();
                    if (tmp == null || tmp < employee)
                    {
                        tmp = employee;
                    }
                }
            }

            return tmp;
        }
    }
}
