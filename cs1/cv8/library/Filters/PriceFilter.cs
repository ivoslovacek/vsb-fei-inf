namespace StockLib.Filters
{
    public class PriceFilter : IFilter
    {
        int? MinPrice = null;
        int? MaxPrice = null;

        public bool IsMatch(IProduct item)
        {
            if (this.MinPrice == null || this.MaxPrice == null)
            {
                throw new InvalidFilterArgumentsException();
            }

            return (item.Price >= this.MinPrice && item.Price <= this.MaxPrice) ? true : false;
        }
    }
}
