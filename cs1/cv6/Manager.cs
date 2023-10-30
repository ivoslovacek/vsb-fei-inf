namespace cv6
{
    public class Manager : MonthlySallaryEmployee
    {
        public Manager(string name, int age) : base(name, age, 80_000) { }

        public override double GetSallary()
        {
            return this.MonthlySallary + this.Age * 500 + this.GetBonus();
        }

        public override void PrintInfo()
        {
            System.Console.WriteLine("Pozice: Manager");
            base.PrintInfo();
        }
    }
}
