using System;
using System.IO;
using System.Threading;
using System.Globalization;
using Country1;


namespace du1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.GetCultureInfo("cs-CZ");
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            if (args.Length == 0)
            {
                Console.WriteLine("Specify a filepath to the CSV!");
                return;
            }

            Country[]? countries = Country.loadCSV(args[0]);
            if (countries == null)
            {
                Console.WriteLine("Couldn't load the CSV file!");
                return;
            }

            Console.WriteLine("Průměrný plat: " + Country.getAverageIncomeFromArray(countries));

            int year = 2023;
            Console.WriteLine($"Nejvyšší plat v roce {year}: {Country.getHighestAverageIncomeFromArray(countries, year)}");

            Console.WriteLine();

            foreach (Country country in countries)
            {
                double incomeInEUR = Math.Round(country.averageIncome.Ammount * country.exchangeRate, 2);
                Console.WriteLine($"{country.name}: {incomeInEUR} EUR");
            }

        }
    }
}
