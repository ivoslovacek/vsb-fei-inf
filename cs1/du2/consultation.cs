using System;

namespace du2
{
    public class Consultation : Event, IStudent
    {
        private Student[]? _Students;
        public Student[]? Students
        {
            get
            {
                if (this._Students == null)
                {
                    return new Student[0];
                }
                else
                {
                    return _Students;
                }
            }
            set
            {
                this._Students = value;
            }
        }

        public Consultation(Student[] students, string? location, string name, DateTime start, DateTime end) : base(name, start, end)
        {
            this.Students = students;
            this.Location = location;
        }

        public string? _Location;
        public string? Location
        {
            get
            {
                if (this._Location == "")
                {
                    return "Neznámé místo";
                }
                else
                {
                    return this._Location;
                }
            }
            set
            {
                this._Location = value;
            }
        }

        public override DateTime? GetReminderTime()
        {
            return null;
        }

        public override string ToString()
        {
            string baseString = base.ToString();

            return $"{baseString} ({Location})";
        }

    }
}
