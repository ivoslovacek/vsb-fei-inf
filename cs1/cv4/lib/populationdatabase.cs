using System.Text;

namespace Database
{
    public class PopulationDatabase
    {
        public Person[]? people { get; set; }

        public void Add(Person person)
        {
            if (people != null)
            {
                Person[]? tmp = new Person[this.people.Length + 1];
                Array.Copy(this.people, tmp, this.people.Length);
                tmp[tmp.Length - 1] = person;
                this.people = tmp;
            }
            else
            {
                Person[]? tmp = new Person[1];
                tmp[0] = person;
                this.people = tmp;
            }
        }

        public int Count
        {
            get
            {
                if (this.people != null)
                {
                    return this.people.Length;
                }
                else
                {
                    return 0;
                }
            }
        }

        public int CountAdults
        {
            get
            {
                if (this.people != null)
                {
                    int tmp = 0;
                    foreach (Person person in this.people)
                    {
                        if (person.IsAdult)
                        {
                            tmp++;
                        }
                    }

                    return tmp;
                }
                else
                {
                    return 0;
                }
            }
        }

        public double? GetAverageAge()
        {
            int sum = 0;
            int count = 0;

            if (this.people != null)
            {
                foreach (Person person in this.people)
                {
                    if (person.Age != null)
                    {
                        count++;
                        sum += person.Age.Value;
                    }
                }
            }

            return (count == 0) ? null : sum / (double)count;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendLine($"Osob: {this.Count}");
            sb.AppendLine($"Dospělých: {this.CountAdults}");
            sb.AppendLine($"Průměrný věk: {this.GetAverageAge()}");

            if (people == null)
            {
                return sb.ToString();
            }

            foreach (Person person in people)
            {
                sb.AppendLine(person.ToString());
            }

            return sb.ToString();
        }
    }
}
