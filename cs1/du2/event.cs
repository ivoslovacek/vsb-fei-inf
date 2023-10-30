using System;

namespace du2
{
    public abstract class Event
    {
        public string Name;
        public DateTime Start;
        public DateTime End;
        public bool IsUpcoming
        {
            get
            {
                /* Nevěděl jsem jaký aktuální datum jsem měl použít, tak jsem tady
                 * zakomentovaně dal na pevno dané datum používáné napříč úkolem
                string dateString = "11. 10. 2023 00:00:00";
                DateTime date = DateTime.Parse(dateString);
                return this.Start > date;
                */
                return this.Start > DateTime.Now;
            }
        }

        public Event(string name, DateTime start, DateTime end)
        {
            this.Name = name;
            this.Start = start;
            this.End = end;
            if (this.Start > this.End)
            {
                DateTime tmp = this.Start;
                this.Start = this.End;
                this.End = tmp;
            }
        }

        public abstract DateTime? GetReminderTime();

        public override string ToString()
        {
            return $"{this.Name}: {this.Start} - {this.End}";
        }
    }
}
