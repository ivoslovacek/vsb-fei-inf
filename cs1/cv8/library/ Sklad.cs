namespace StockLib
{
    public interface IProduct
    {
        string Name { get; }
        double Price { get; }
    }

    public interface IPhysicalProduct : IProduct
    {
        int Width { get; }
        int Height { get; }
        int Length { get; }
    }

    public interface IWheeledVehicle
    {
        int WheelCount { get; }
    }

    public interface IFilter
    {
        bool IsMatch(IProduct item);
    }

    public class Stock<T> where T : IProduct
    {
        public List<T> Products;

        public void Add(T product)
        {

            foreach (IProduct each in this.Products)
            {
                if (object.ReferenceEquals(each, product))
                {
                    throw new DuplicitProductException();
                }
            }

            this.Products.Add(product);
        }

        public List<T> Filter(FilterEvaluator filterEvaluator)
        {

            return new List<T>(0);
        }
    }

    public class FilterEvaluator
    {
        public List<IFilter> filters;

        public void Add(IFilter filter)
        {
            this.filters.Add(filter);
        }

        public bool IsMatch(IProduct item)
        {
            foreach (var filter in this.filters)
            {
                if (!filter.IsMatch(item))
                {
                    return false;
                }
            }

            return true;
        }
    }


    public class DuplicitProductException : Exception
    {
    }

    public class InvalidFilterArgumentsException : Exception
    {
    }
}
