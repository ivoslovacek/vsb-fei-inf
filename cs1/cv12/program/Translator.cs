namespace cv12;

public class Translator
{
    private Dictionary<string, string> data = new Dictionary<string, string>(StringComparer.InvariantCultureIgnoreCase);

    public void Add(string key, string value)
    {
        data[key] = value;
    }

    public string Translate(string key)
    {
        string[] words = key.Split(' ');
        List<string> result = new List<string>();

        foreach (string word in words)
        {
            try
            {
                result.Add(data[word]);
            }
            catch (Exception e)
            {
                result.Add("???");
            }
        }

        return string.Join(" ", result);
    }
}