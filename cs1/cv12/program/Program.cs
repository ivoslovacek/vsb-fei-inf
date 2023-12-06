namespace cv12;

internal class Cv12
{
    static void Main(string[] args)
    {
        /* MyList list = new MyList();

        list.Add(1);
        list.Add(2);
        list.Add(3);
        list.Add(4);
        list.Add(5);

        foreach (int x in list)
        {
            Console.WriteLine(x);
        }

        //same thing as foreach
        using IEnumerator<int> enu = list.GetEnumerator();
        while (enu.MoveNext())
        {
            Console.WriteLine(enu.Current);
        }

        foreach (var x in list.Multiply(5))
        {
            Console.WriteLine(x);
        }
         */

        /*
         int[] data = new int[] { 5, 8, 21, 4, 7, 6, 8, 987, 157, -82 };
        List<int> list = new List<int>(data);

        Array.Sort(data, new MyComparer());
        list.Sort(new MyComparer2());

        Console.WriteLine(string.Join(", ", data));
        Console.WriteLine(string.Join(", ", list));
        */

        Translator t = new Translator();
        t.Add("nový", "new");
        t.Add("rok", "year");
        t.Add("Šťastný", "Happy");
        Console.WriteLine(t.Translate("šťastný nový rok"));
    }
}