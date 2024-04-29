namespace cv07;

public class TxtLogger
{
    public async Task Log(string txt)
    { 
        await File.WriteAllTextAsync(txt);
    }
}