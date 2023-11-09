namespace StockLib.Products
{
    public class Voucher : IProduct
    {
        public string Name { get; set; }
        public required double Price { get; set; }
    }
}
