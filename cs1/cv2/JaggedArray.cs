using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;


namespace JaggedArray
{
    internal class JaggedArray
    {
        private void CreateT(bool[][] data, int x, int y)
        {
            data[y][x] = true;
            data[y][x + 1] = true;
            data[y][x + 2] = true;
            data[y + 1][x + 1] = true;
        }

        private void CreateZ(bool[][] data, int x, int y)
        {
            data[y][x] = true;
            data[y][x + 1] = true;
            data[y + 1][x + 1] = true;
            data[y + 1][x + 2] = true;
        }


        public void Run()
        {
            bool[][] data = new bool[20][];
            for (int i = 0; i < data.Length; i++)
            {
                data[i] = new bool[10];
            }

            CreateT(data, 2, 0);
            CreateZ(data, 4, 5);

            System.Console.CursorVisible = false;

            MainLoop(data);
        }

        private void Print(bool[][] data)
        {

            for (int y = 0; y < data.Length; y++)
            {
                for (int x = 0; x < data[y].Length; x++)
                {
                    System.Console.Write(data[y][x] ? "\u2588" : " ");
                }
                System.Console.WriteLine();
            }
        }

        private void Move(bool[][] data)
        {
            for (int y = data.Length - 1; y > 0; y--)
            {
                for (int x = 0; x < data[y].Length; x++)
                {
                    data[y] = data[y - 1];
                }
            }

            for (int x = 0; x < data[0].Length; x++)
            {
                data[0] = new bool[data[0].Length];
            }
        }

        private void MainLoop(bool[][] data)
        {
            while (true)
            {
                System.Console.Clear();

                Print(data);

                Move(data);

                Thread.Sleep(500);
            }
        }
    }
}
