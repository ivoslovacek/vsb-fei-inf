namespace cv7
{
    internal class ArrayHelper<T>
    {
        public static void Swap(T[] data, int i, int j)
        {
            T tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }

        public static T[] Concat(T[] data1, T[] data2)
        {
            T[] tmp = new T[data1.Length + data2.Length];

            Array.Copy(data1, tmp, data1.Length);
            Array.Copy(data2, 0, tmp, data1.Length, data2.Length);

            return tmp;
        }
    }

    internal class ArrayHelper2
    {
        public static void Swap<T>(T[] data, int i, int j)
        {
            T tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }

        public static T[] Concat<T>(T[] data1, T[] data2)
        {
            T[] tmp = new T[data1.Length + data2.Length];

            Array.Copy(data1, tmp, data1.Length);
            Array.Copy(data2, 0, tmp, data1.Length, data2.Length);

            return tmp;
        }

    }
}

