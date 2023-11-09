namespace StockLib.Products
{
    public class Bike : IPhysicalProduct, IWheeledVehicle
    {
        public string Name { get; set; }
        public required double Price { get; set; }

        public int Width { get; set; }
        public int Height { get; set; }
        public int Length { get; set; }

        public int WheelCount
        {
            get
            {
                return 2;
            }
        }
    }
}
