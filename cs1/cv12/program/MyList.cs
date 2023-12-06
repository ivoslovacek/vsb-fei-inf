using System;
using System.Collections;
using System.Collections.Generic;

namespace cv12
{
    internal class MyList : IEnumerable<int>
    {
        private List<int> data = new List<int>();

        public void Add(int x)
        {
            this.data.Add(x);
        }

        public IEnumerable<int> Multiply(int x)
        {
            foreach (int val in data)
            {
                yield return val * x;
            }
        }

        public IEnumerator<int> GetEnumerator()
        {
            return new MyListEnumerator(data);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new MyListEnumerator(data);
        }
    }

    internal class MyListEnumerator(List<int> data) : IEnumerator<int>
    {
        private int position = -1;

        public int Current => data[position];

        object IEnumerator.Current => data[position];

        public void Dispose()
        {
        }

        public bool MoveNext()
        {
            position++;
            return position < data.Count;
        }

        public void Reset()
        {
            position = -1;
        }
    }
}