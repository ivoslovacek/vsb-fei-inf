using System.Text;

namespace Database
{
    public class Person
    {
        public string? Name { get; set; }
        private int? _age;
        public int? Age
        {
            get
            {
                return this._age;
            }
            set
            {
                if (value >= 0 && value <= 150)
                {
                    this._age = value;
                }
                else
                {
                    this._age = null;
                }
            }
        }
        public GenderEnum Gender { get; set; }

        public bool IsAdult
        {
            get
            {
                return _age >= 18;
            }
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.Append("Osoba: ");
            sb.Append(this.Name);
            sb.Append(", ");
            sb.Append(this._age);
            sb.Append(", ");
            sb.Append(this.Gender);

            return sb.ToString();
        }
    }
}
