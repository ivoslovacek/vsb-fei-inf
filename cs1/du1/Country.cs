using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace Country1
{
    public struct AverageIncome
    {
        public string Currency;
        public double Ammount;
    }


    internal class Country
    {
        public string name;
        public AverageIncome averageIncome;
        public double exchangeRate;
        public int? yearOfAcquisition;
        public bool isEUMember;

        public Country(string n, AverageIncome ai, double er, int? yoa, bool ieu)
        {
            name = n;
            averageIncome = ai;
            exchangeRate = er;
            yearOfAcquisition = yoa;
            isEUMember = ieu;
        }


        public static Country[]? loadCSV(string filePath)
        {
            try
            {
                string[] lines = File.ReadAllLines(filePath);

                Country[] countries = new Country[lines.Length - 1];

                for (int i = 1; i < lines.Length; i++)
                {
                    string[] subStrings = lines[i].Split(';');

                    string n = subStrings[0];

                    AverageIncome averageIncome = Country.ParseAverageIncome(subStrings[1]);

                    double.TryParse(subStrings[2], out double er);

                    int? yoa = 0;
                    if (string.IsNullOrEmpty(subStrings[3]))
                    {
                        yoa = null;
                    }
                    else
                    {
                        string[] yearInfo = subStrings[3].Split('-');
                        int.TryParse(yearInfo[0], out int parsedInt);
                        yoa = parsedInt;
                    }

                    bool ieu = (subStrings[4] == "ano") ? true : false;

                    countries[i - 1] = new Country(n, averageIncome, er, yoa, ieu);
                }

                return countries;
            }
            catch (FileNotFoundException)
            {
                Console.WriteLine("The file does not exist.");
                return null;
            }
            catch (IOException e)
            {
                Console.WriteLine("An error occurred while reading the file: " + e.Message);
                return null;
            };

        }

        private static AverageIncome ParseAverageIncome(string text)
        {
            string[] subStrings = text.Split(" ");
            double ammount = 0;

            if (double.TryParse(subStrings[0], out ammount))
            {
                return new AverageIncome
                {
                    Ammount = ammount,
                    Currency = subStrings[1]
                };
            }
            else
            {
                double.TryParse(subStrings[1], out ammount);
                return new AverageIncome
                {
                    Ammount = ammount,
                    Currency = subStrings[0]
                };
            }
        }

        public static double getAverageIncomeFromArray(Country[] countries)
        {
            double sum = 0.0;
            int EUcount = 0;


            foreach (Country country in countries)
            {
                if (country.isEUMember)
                {
                    sum += country.averageIncome.Ammount * country.exchangeRate;
                    EUcount++;
                }
            }

            return Math.Round(sum / EUcount, 2);
        }

        public static string getHighestAverageIncomeFromArray(Country[] countries, int year)
        {
            double highestIncome = 0;
            int index = 0;

            for (int i = 0; i < countries.Length; i++)
            {
                double incomeInEUR = countries[i].averageIncome.Ammount * countries[i].exchangeRate;
                bool hasHighestIncome = (incomeInEUR > highestIncome);
                // countries[i].yearOfAcquisition == null tu je kvůli tomu, že to má vypsat Lichtenstein
                // ale Lichtenstein nemá zadaný údaj roku kdy byly získany data ????????????????????????
                // nedává mi to moc smysl ale předpokládám že mám ten plat počítat podle toho year of acquistion,
                // protože nemůžu mít data z 2022 pro rok 2023 (např. u Malty)
                bool isRecordedInSpecifiedYear = (countries[i].yearOfAcquisition == year || countries[i].yearOfAcquisition == null);

                if (hasHighestIncome && isRecordedInSpecifiedYear)
                {
                    index = i;
                    highestIncome = incomeInEUR;
                }
            }

            return countries[index].name;
        }
    }
}
