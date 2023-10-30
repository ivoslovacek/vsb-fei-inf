
namespace du2
{
    public class Lecture : Event
    {
        public Lecture(string name, DateTime start, DateTime end) : base(name, start, end) { }

        public override DateTime? GetReminderTime()
        {
            return this.Start.AddMinutes(-30);
        }
    }
}
