using System;

namespace cv3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Zadejte číslo: ");
            string? text = Console.ReadLine();
            if (text == null)
            {
                return;
            }

            int x = Parser.ParseInt(text);
            Console.WriteLine(x);
            int? y = Parser.ParseIntOrNull(text);
            Console.WriteLine((y == null) ? "null" : y);
            int z = 0;
            Console.WriteLine((Parser.TryParseInt(text, out z)) ? z : "není číslo");
        }

    }
}
