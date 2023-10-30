namespace cv6
{
    public class Secretary : MonthlySallaryEmployee
    {
        public Secretary(string name, int age) : base(name, age, 20_000) { }

        public override void PrintInfo()
        {
            System.Console.WriteLine("Pozice: Manager");
            base.PrintInfo();
        }
    }
}
