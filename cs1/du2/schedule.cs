using System;
using System.Collections.Generic;
using System.Linq;

namespace du2
{
    public class Schedule
    {
        List<Event> events = new List<Event>();

        public void Add(Event e)
        {
            this.events.Add(e);
        }

        public List<Event> this[int year, int month, int day]
        {
            get
            {
                return events.Where(e =>
                           e.Start.Year == year
                        && e.Start.Month == month
                        && e.Start.Day == day).ToList();
            }
        }

        public List<Event> GetAllUpcoming()
        {
            return events.Where(e => e.IsUpcoming).ToList();
        }
    }
}
