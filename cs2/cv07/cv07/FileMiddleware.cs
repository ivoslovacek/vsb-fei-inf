using System.Net;

namespace cv07;

public class FileMiddleware
{
    private readonly RequestDelegate next;

    public FileMiddleware(RequestDelegate next)
    {
        this.next = next;
    }

    public async Task Invoke(HttpContext ctx)
    {
        if (ctx.Request.Path.Value.EndsWith(".png"))
        {
            if (File.Exists(ctx.Request.Path.Value.TrimStart('/')))
            {
                await ctx.Response.SendFileAsync(ctx.Request.Path.Value.TrimStart('/'));
            }
            else
            {
                ctx.Response.StatusCode = 404;
            }
        }
        else
        {
            throw new NotImplementedException();
        }
    }
}