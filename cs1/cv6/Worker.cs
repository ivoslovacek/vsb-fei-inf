namespace cv6
{
    public class Worker : HourSallaryEmployee
    {
        public Worker(string name, int age) : base(name, age, 130) { }

        public override double GetBonus()
        {
            return base.GetBonus() + ((this.HoursWorked > 160) ? 5000.0 : 0.0);
        }
    }
}
