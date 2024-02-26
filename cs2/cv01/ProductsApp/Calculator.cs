namespace ProductsApp
{
    public class Calculator
    {
        private int X { get; set; }
        private int Y{ get; set; }

        public event EventHandler OnSetXY;

        public event EventHandler<CalculationResult> OnCompute; 
        public void SetXY(int x, int y)
        {
            this.X = x;
            this.Y = y;
            OnSetXY(this, EventArgs.Empty);
        }
        
        public int Execute(Operation operation)
        {
            int result = operation(this.X, this.Y);
            OnCompute?.Invoke(this, new CalculationResult(result));
            return result;
        }

        public static int Add(int x, int y)
        {
            return x + y;
        }
   }

    public class CalculationResult(int result) : EventArgs
    {
        public int Result { get; set; } = result;
    }
}