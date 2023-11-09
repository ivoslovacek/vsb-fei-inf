namespace StockLib.Filters
{
    public class WidthFilter : IFilter
    {
        int? MinWidth = null;
        int? MaxWidth = null;

        public bool IsMatch(IProduct item)
        {
            if (this.MinWidth == null || this.MaxWidth == null)
            {
                throw new InvalidFilterArgumentsException();
            }

            if (item is IPhysicalProduct i)
            {
                return (i.Width >= this.MinWidth && i.Width <= this.MaxWidth) ? true : false;
            }

            return false;
        }
    }
}
