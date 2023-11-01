namespace cv7
{
    internal interface IKeyValuePair<Tkey, TValue>
    {
        Tkey Key { get; }
        TValue Value { get; }
    }

    internal class Node<TKey, TValue> : IKeyValuePair<TKey, TValue>
    {
        public TKey Key { get; set; }
        public TValue Value { get; set; }

        public Node<TKey, TValue>? Left { get; set; }
        public Node<TKey, TValue>? Right { get; set; }

        public Node(TKey key, TValue value)
        {
            this.Key = key;
            this.Value = value;
        }
    }

    internal class TreeMap<TKey, TValue> where TKey : IComparable<TKey>
    {
        private Node<TKey, TValue>? root { get; set; }

        public TreeMap()
        {
            this.root = null;
        }

        public TreeMap(TKey key, TValue value)
        {
            this.root = new Node<TKey, TValue>(key, value);
        }

        public TValue this[TKey key]
        {
            get
            {
                Node<TKey, TValue>? current = this.root;

                while (true)
                {
                    if (current == null)
                    {
                        return default(TValue);
                    }

                    if (current.Key.CompareTo(key) == 0)
                    {
                        return current.Value;
                    }

                    if (current.Key.CompareTo(key) < 0)
                    {
                        current = current.Right;
                    }
                    else if (current.Key.CompareTo(key) == 0)
                    {
                        current = current.Left;
                    }
                }
            }
            set
            {
                Node<TKey, TValue>? current = this.root;
                while (true)
                {
                    if (current == null)
                    {
                        this.root = new Node<TKey, TValue>(key, value);
                        return;
                    }

                    if (current.Key.CompareTo(key) == 0)
                    {
                        current.Value = value;
                        return;
                    }

                    if (current.Key.CompareTo(key) < 0)
                    {
                        current = current.Right;
                    }
                    else if (current.Key.CompareTo(key) == 0)
                    {
                        current = current.Left;
                    }
                }
            }
        }

        public int Count
        {
            get
            {
                if (root == null)
                {
                    return 0;
                }

                int count = 0;

                Queue<Node<TKey, TValue>> queue = new Queue<Node<TKey, TValue>>();

                queue.Enqueue(this.root);

                while (queue.Count != 0)
                {
                    Node<TKey, TValue> tmp = queue.Dequeue();
                    count++;

                    if (tmp.Left != null)
                    {
                        queue.Enqueue(tmp.Left);
                    }

                    if (tmp.Right != null)
                    {
                        queue.Enqueue(tmp.Right);
                    }
                }

                return count;
            }
        }
    }
}
