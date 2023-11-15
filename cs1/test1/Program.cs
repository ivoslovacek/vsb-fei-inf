using Nemovitosti;
using System.Globalization;

namespace Test1
{
    public class Test1
    {
        public static void Main(string[] args)
        {
            CultureInfo.DefaultThreadCurrentCulture = CultureInfo.InvariantCulture;
            CultureInfo.DefaultThreadCurrentUICulture = CultureInfo.InvariantCulture;


            RealtyDatabase db = new RealtyDatabase();


            var land1 = new Land("Janoušek" /* jméno prodávajícího */);
            land1.Price = 2_500_000;
            db.Add(land1);

            var land2 = new Land("Gajdoš");
            land2.Price = 3_200_000;
            db.Add(land2);

            var house1 = new House("Alibaba" /* jméno prodávajícího */);
            house1.Price = 12_000_000;
            db.Add(house1);

            var apartment1 = new Apartment("Novák" /* jméno prodávajícího */);
            apartment1.Price = 20_000_000;
            db.Add(apartment1);

            var house2 = new House("Sokol");
            house2.Price = 8_000_000;
            db.Add(house2);


            // TODO: Vyvolání výjimky
            /*
            var apartment2 = new Apartment("No name");
            apartment2.Price = -1;
            db.Add(apartment2);
            */

            var averageHousePrice = db.GetAveragePriceByType<House>();
            Console.WriteLine("Průměrná cena domů: " + averageHousePrice);

            var averageApartmentPrice = db.GetAveragePriceByType<Apartment>();
            Console.WriteLine("Průměrná cena bytů: " + averageApartmentPrice);

            var averageLandPrice = db.GetAveragePriceByType<Land>();
            Console.WriteLine("Průměrná cena pozemků: " + averageLandPrice);

            var averageRealtyPrice = db.GetAveragePriceByType<Realty>();
            Console.WriteLine("Průměrná cena nemovitostí: " + averageRealtyPrice);

            Console.WriteLine();

            foreach (var realty in db.GetAllWithMinUsableArea(110  /* minimální plocha */ ))
            {
                Console.WriteLine(realty);
            }
        }
    }
}
