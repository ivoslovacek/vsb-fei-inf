namespace Nemovitosti
{
    public abstract class Realty
    {
        private double? _Price;
        public double? Price
        {
            get
            {
                return this._Price;
            }
            set
            {
                if (value >= 0)
                {
                    this._Price = value;
                }
                else
                {
                    throw new InvalidPriceException();
                }
            }
        }
        public string name;

        public Realty(string name)
        {
            this.name = name;
        }
    }

    public class InvalidPriceException : Exception
    {
    }

    public interface ILandArea
    {
        int LandArea { get; }

        double GetLandArea();
    }

    public interface IUsableArea
    {
        int UsableArea { get; }

        double GetUsableArea();
    }
}
