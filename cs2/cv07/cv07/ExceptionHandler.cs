namespace cv07;

public class ExceptionHandler
{
    private TxtLogger logger;
    public async Task Handle(Exception exception)
    {
        await logger.Log(exception.StackTrace);
    }
}