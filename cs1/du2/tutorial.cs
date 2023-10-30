using System;

namespace du2
{
    public class Tutorial : Event, IStudent
    {
        public Student[]? Students { get; set; }

        public Tutorial(Student[]? students, string name, DateTime start, DateTime end) : base(name, start, end)
        {
            this.Students = students;
        }

        public override DateTime? GetReminderTime()
        {
            int numberOfStudents;

            numberOfStudents = (this.Students != null) ? this.Students.Length : 0;

            return this.Start.AddMinutes(-30 - 10 * numberOfStudents);
        }
    }
}
