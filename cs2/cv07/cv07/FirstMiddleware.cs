namespace cv07;

public class FirstMiddleware
{
    private readonly RequestDelegate next;

    public FirstMiddleware(RequestDelegate next)
    {
        this.next = next;
    }

    public async Task Invoke(HttpContext ctx)
    {
        if (ctx.Request.Path == "/")
        {
            ctx.Response.Headers.ContentType = "text/html; charset=utf-8";
            await ctx.Response.WriteAsync("<h1>Název stránky</h1><p>je to mrdka</p>");
        }
        else
        {
            ctx.Response.Headers["FDSA"] = "ASDF";
            await next(ctx);
        }
    }
}