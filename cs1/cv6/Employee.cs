using System;

namespace cv6
{
    public abstract class Employee : Person
    {
        public virtual double GetBonus()
        {
            return 0.0;
        }

        public abstract double GetSalary();

        public Employee(string name, int age) : base(name, age) { }


        public static bool operator <(Employee e1, Employee e2)
        {
            if (e1 is null || e2 is null)
            {
                return false;
            }
            return e1.GetSalary() < e2.GetSalary();
        }

        public static bool operator >(Employee e1, Employee e2)
        {
            if (e1 is null || e2 is null)
            {
                return false;
            }
            return e1.GetSalary() > e2.GetSalary();
        }

        public static bool operator ==(Employee e1, Employee e2)
        {
            if (e1 is null && e2 is null)
            {
                return true;
            }

            if (e1 is null || e2 is null)
            {
                return false;
            }

            return e1.GetSalary() == e2.GetSalary();
        }

        public static bool operator !=(Employee e1, Employee e2)
        {
            return !(e1 == e2);
        }
    }

    public abstract class HourSallaryEmployee : Employee
    {
        public double HourlySallary { get; set; }
        public int HoursWorked { get; set; }

        public HourSallaryEmployee(string name, int age, double hourlySallary) : base(name, age)
        {
            this.HourlySallary = hourlySallary;
        }

        public override double GetSalary()
        {
            return this.HoursWorked * this.HourlySallary + this.GetBonus();
        }
    }

    public abstract class MonthlySallaryEmployee : Employee
    {
        public double MonthlySallary { get; set; }

        protected MonthlySallaryEmployee(string name, int age, double monthlySallary) : base(name, age)
        {
            this.MonthlySallary = monthlySallary;
        }

        public override double GetSalary()
        {
            return this.MonthlySallary + this.GetBonus();
        }
    }
}
