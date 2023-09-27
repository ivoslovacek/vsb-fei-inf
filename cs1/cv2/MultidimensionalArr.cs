using System.Threading;


namespace MultidimensionalArr
{
    internal class MultidimensionalArray
    {
        private void CreateT(bool[,] data, int x, int y)
        {
            data[x, y] = true;
            data[x + 1, y] = true;
            data[x + 2, y] = true;
            data[x + 1, y + 1] = true;
        }

        private void CreateZ(bool[,] data, int x, int y)
        {
            data[x, y] = true;
            data[x + 1, y] = true;
            data[x + 1, y + 1] = true;
            data[x + 2, y + 1] = true;
        }

        public void Run()
        {
            bool[,] data = new bool[10, 20];

            CreateT(data, 2, 0);
            CreateZ(data, 4, 5);

            System.Console.CursorVisible = false;

            MainLoop(data);
        }

        private void Print(bool[,] data)
        {

            for (int y = 0; y < data.GetLength(1); y++)
            {
                for (int x = 0; x < data.GetLength(0); x++)
                {
                    System.Console.Write(data[x, y] ? "\u2588" : " ");
                }
                System.Console.WriteLine();
            }
        }

        private void Move(bool[,] data)
        {
            for (int y = data.GetLength(1) - 1; y > 0; y--)
            {
                for (int x = 0; x < data.GetLength(0); x++)
                {
                    data[x, y] = data[x, y - 1];
                }
            }

            for (int x = 0; x < data.GetLength(0); x++)
            {
                data[x, 0] = false;
            }
        }

        private void MainLoop(bool[,] data)
        {
            while (true)
            {
                System.Console.Clear();

                Print(data);

                Move(data);

                System.Threading.Thread.Sleep(500);

            }
        }
    }
}
