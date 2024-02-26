using System.Security.Cryptography.X509Certificates;
using System.Linq;

namespace ProductsApp
{
    static class MyExtension
    {
        public static string JoinNumbers(this IEnumerable<int> nums)
        {
            return string.Join(", ", nums);
        }

        public static IEnumerable<int> OddPosition(this int[] nums)
        {
            for(int i = 0; i < nums.Length; i++)
            {
                if (i % 2 == 0)
                    yield return nums[i];
            }
        }

        public static IEnumerable<T> MapNumbers<T>(this IEnumerable<T> nums, Map<T> map)
        {
            foreach (T num in nums)
            {
                yield return map(num);
            } 
        }
    }

    delegate T Map<T>(T x);
    
    internal class Program
    {
        static void Main(string[] args)
        {
            Calculator calculator = new Calculator();
            calculator.OnSetXY += (sender, eventArgs) =>
            {
                Console.WriteLine("Zavoláno");
            };
            calculator.SetXY(3, 4);
            calculator.OnCompute += (sender, eventArgs) =>
            {
                Console.WriteLine($"Result is {eventArgs.Result}"); 
            };
            Console.WriteLine(calculator.Execute(Calculator.Add));

            int[] nums = { 4, 5, 6, 7 };
            
            Console.WriteLine(nums.MapNumbers(x => x * x).JoinNumbers());
            
            IEnumerable<Product> products = GetProducts();
            double priceSum = products.Sum(x => x.Price);
            int productCount = products.Count();
            Console.WriteLine(priceSum / productCount);
            Console.WriteLine(products.Average(x => x.Price));
            Console.WriteLine(products.Where(x => x.Quantity >0).Average(x => x.Price));
            string[] names = products.Select(x => x.Name).ToArray();
            Product first = products.First();
        }

        private static IEnumerable<Product> GetProducts()
        {
            return new List<Product>()
            {
                new Product(){ Id = 1, Name = "Auto", Price = 700_000, Quantity = 10 },
                new Product(){ Id = 1, Name = "Slon", Price = 1_500_000, Quantity = 0 },
                new Product(){ Id = 1, Name = "Kolo", Price = 26_000, Quantity = 5 },
                new Product(){ Id = 1, Name = "Brusle", Price = 2_800, Quantity = 30 },
                new Product(){ Id = 1, Name = "Hodinky", Price = 18_500, Quantity = 2 },
                new Product(){ Id = 1, Name = "Mobil", Price = 24_000, Quantity = 0 }
            };
        }
    }
}