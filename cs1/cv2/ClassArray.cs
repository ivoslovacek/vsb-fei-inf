using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;


namespace ClassArray
{
    internal class Brick
    {
        public int x;
        public int y;

        public Brick(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    internal class CompositeBrick
    {
        private int index;
        public int x;
        public int y;
        public Brick[] data;

        public CompositeBrick(int x, int y, int size)
        {
            this.x = x;
            this.y = y;
            this.data = new Brick[size];

            this.index = 0;
        }

        public void addBrick(int x, int y)
        {
            this.data[this.index] = new Brick(x, y);
            this.index++;
        }

        public void Print()
        {
            System.Console.Clear();
            for (int i = 0; i < data.Length; i++)
            {
                if (this.y + data[i].y > 20)
                {
                    continue;
                }
                System.Console.SetCursorPosition(this.x + data[i].x, this.y + data[i].y);
                System.Console.Write("\u2588");
            }
        }

        public void Move()
        {
            this.y++;
        }
    }

    internal class ClassArray
    {
        public void Run()
        {
            CompositeBrick bricks = new CompositeBrick(2, 0, 4);

            bricks.addBrick(0, 0);
            bricks.addBrick(1, 0);
            bricks.addBrick(2, 0);
            bricks.addBrick(1, 1);

            MainLoop(bricks);
        }

        private void MainLoop(CompositeBrick bricks)
        {
            while (true)
            {
                bricks.Print();
                bricks.Move();
                System.Threading.Thread.Sleep(500);
            }
        }
    }
}
