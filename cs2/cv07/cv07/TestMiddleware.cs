namespace cv07;

public class TestMiddleware
{
    private readonly RequestDelegate next;

    public TestMiddleware(RequestDelegate next)
    {
        this.next = next;
    }

    public async Task Invoke(HttpContext ctx)
    {
        if (ctx.Request.Path == "/test")
        {
            ctx.Response.ContentType = "text/html; charset=utf-8";
            await ctx.Response.WriteAsync("<h1>FIGHT</h1><img src=haha.png></a>");
        }
        else
        {
            await next(ctx);
        }
    }
}