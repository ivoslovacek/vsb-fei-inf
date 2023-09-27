namespace cv1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string name = Console.ReadLine();
            if (name == null)
            {
                return;
            }

            name = name.ToUpper();

            Console.WriteLine("Ahoj: " + name);
        }
    }
}
