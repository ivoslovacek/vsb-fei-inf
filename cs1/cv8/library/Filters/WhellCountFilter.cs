namespace StockLib.Filters
{
    public class WheelCountFilter : IFilter
    {
        int? WheelCount = null;

        public bool IsMatch(IProduct item)
        {
            if (this.WheelCount == null)
            {
                throw new InvalidFilterArgumentsException();
            }

            if (item is IWheeledVehicle i)
            {
                return i.WheelCount == this.WheelCount;
            }

            return false;
        }
    }
}
