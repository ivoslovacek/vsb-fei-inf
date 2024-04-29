namespace cv07;

public class ErrorHandlerMiddleware
{
    private readonly RequestDelegate next;
    private ExceptionHandler handler;

    public ErrorHandlerMiddleware(RequestDelegate next)
    {
        this.next = next;
    }

    public async Task Invoke(HttpContext ctx)
    {
        try
        {
            await next(ctx);
        }
        catch (Exception e)
        {
            await handler.Handle(e);
        }
    }
}