namespace StockLib.Products
{
    public class MobilePhone : IPhysicalProduct
    {
        public string Name { get; set; }
        public required double Price { get; set; }

        public int Width { get; set; }
        public int Height { get; set; }
        public int Length { get; set; }
    }
}
