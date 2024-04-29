using System.Text.Json;

namespace cv07.Properties;

public class JSONLogger
{
    public async Task Log(string exception)
    {
        await File.WriteAllTextAsync("log.json", JsonSerializer.Serialize(new
        {
            Error = "An error has occured" + exception,
        }));
    }
}