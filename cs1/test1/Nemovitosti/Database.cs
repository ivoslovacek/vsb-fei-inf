namespace Nemovitosti
{
    public class RealtyDatabase
    {
        List<Realty> list = new List<Realty>();

        public void Add(Realty r)
        {
            list.Add(r);
        }

        public double GetAveragePriceByType<T>()
        {
            double price = 0;
            int count = 0;

            foreach (Realty tmp in this.list)
            {
                if (tmp is T && tmp.Price.HasValue)
                {
                    price += tmp.Price.Value;
                    count++;
                }
            }

            if (count != 0)
            {
                price /= count;
            }

            return price;
        }

        public List<IUsableArea> GetAllWithMinUsableArea(double area)
        {
            List<IUsableArea> minUsable = new List<IUsableArea>();

            foreach (Realty tmp in this.list)
            {
                if (tmp is IUsableArea usable)
                {
                    if (usable.GetUsableArea() > area)
                    {
                        minUsable.Add(usable);
                    }
                }
            }

            return minUsable;
        }
    }
}
