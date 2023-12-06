namespace cv12;

internal class MyComparer : IComparer<int>
{
    public virtual int Compare(int x, int y)
    {
        if ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0))
        {
            return x.CompareTo(y);
        }

        return (x % 2 == 0) ? -1 : 1;
    }
}

internal class MyComparer2 : MyComparer
{
    public override int Compare(int x, int y)
    {
        return -base.Compare(x,y);
    }
}
