namespace ProductsApp
{
    public delegate int Operation(int x, int y);
    public class Product
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public double Price { get; set; }

        public int Quantity { get; set; }
    }

}
