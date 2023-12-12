namespace Program;

public delegate void OnDataCallback(string[] row, int index);

public delegate void OnInvalidDataHandler(string row, int index);

public class CsvReader
{
    private string _filePath;

    private int _columnNumber = -1;

    private OnDataCallback _onDataCallback;

    public event OnInvalidDataHandler OnInvalidData;

    public CsvReader(string filePath)
    {
        this._filePath = filePath;
    }

    public void SetDataCallback(OnDataCallback onDataCallback)
    {
        this._onDataCallback = onDataCallback;
    }

    public void Read()
    {
        if (!File.Exists(this._filePath))
            return;

        if (this._onDataCallback is null | this.OnInvalidData is null)
            return;

        using FileStream fs = new FileStream(this._filePath, FileMode.Open, FileAccess.Read);
        using StreamReader sr = new StreamReader(fs);

        string line;
        for (int i = 0; (line = sr.ReadLine()) != null; i++)
        {
            string[] row = line
                .Split(';')
                .Select(column => column.Trim())
                .ToArray();

            if (this._columnNumber == -1)
            {
                this._columnNumber = row.Length;
            }

            if (row.Length == this._columnNumber)
            {
                this._onDataCallback(row, i);
            }
            else
            {
                OnInvalidData(line, i);
            }
        }
    }
}