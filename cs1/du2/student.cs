namespace du2
{
    internal interface IStudent
    {
        Student[]? Students { get; }
    }

    public class Student
    {
        public string Name
        {
            get;
        }

        public Student(string Name)
        {
            this.Name = Name;
        }

        public override string ToString()
        {
            return Name;
        }
    }
}
