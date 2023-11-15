namespace Nemovitosti
{
    public class House : Realty, ILandArea, IUsableArea
    {
        public int LandArea { get; }
        private double LandCoefficient { get; }
        private int LandConstant { get; }

        public int UsableArea { get; }
        private double UsableCoefficient { get; }
        private int UsableConstant { get; }

        public House(string name) : base(name)
        {
            this.LandCoefficient = 100000.0;
            this.LandConstant = 100;

            this.UsableCoefficient = 43000.0;
            this.UsableConstant = 100;
        }

        public double GetLandArea()
        {
            return (this.Price.HasValue) ? Math.Round(this.Price.Value / this.LandCoefficient) : this.LandConstant;
        }

        public double GetUsableArea()
        {
            return (this.Price.HasValue) ? Math.Round(this.Price.Value / this.UsableCoefficient) : this.UsableConstant;
        }

        public override string ToString()
        {
            string price = "";

            if (this.Price.HasValue)
            {
                price = this.Price.Value.ToString();
            }
            else
            {
                price = "neznámá cena";
            }

            return $"{this.name} - dům o ploše {this.GetUsableArea()}m2 se zahradou {this.GetLandArea()}m2 - {price}Kč";
        }
    }

    public class Land : Realty, ILandArea
    {
        public int LandArea { get; }
        private double LandCoefficient { get; }
        private int LandConstant { get; }

        public Land(string name) : base(name)
        {
            this.LandCoefficient = 2500.0;
            this.LandConstant = 600;
        }

        public double GetLandArea()
        {
            return (this.Price.HasValue) ? Math.Round(this.Price.Value / this.LandCoefficient) : this.LandConstant;
        }

        public override string ToString()
        {
            string price = "";

            if (this.Price.HasValue)
            {
                price = this.Price.Value.ToString();
            }
            else
            {
                price = "neznámá cena";
            }

            return $"{this.name} - pozemek o ploše {this.GetLandArea()}m2 - {price}Kč";
        }
    }

    public class Apartment : Realty, IUsableArea
    {
        public int UsableArea { get; }
        private double UsableCoefficient { get; }
        private int UsableConstant { get; }

        public Apartment(string name) : base(name)
        {
            this.UsableCoefficient = 47000.0;
            this.UsableConstant = 70;
        }

        public double GetUsableArea()
        {
            return (this.Price.HasValue) ? Math.Round(this.Price.Value / this.UsableCoefficient) : this.UsableConstant;
        }

        public override string ToString()
        {
            string price = "";

            if (this.Price.HasValue)
            {
                price = this.Price.Value.ToString();
            }
            else
            {
                price = "neznámá cena";
            }

            return $"{this.name} - byt o ploše {this.GetUsableArea()}m2 - {price}Kč";
        }
    }
}
