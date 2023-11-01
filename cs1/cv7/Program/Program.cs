using System;

namespace cv7
{
    class Program
    {
        static internal void Main(string[] args)
        {
            int[] arr1 = { 1, 2, 3 };
            int[] arr2 = { 1, 2, 3 };

            int[] arr = ArrayHelper<int>.Concat(arr1, arr2);
            arr = ArrayHelper2.Concat<int>(arr, arr1);

            Console.WriteLine(string.Join(", ", arr));
        }
    }

}
