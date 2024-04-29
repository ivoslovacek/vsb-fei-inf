
using Microsoft.AspNetCore.Html;

namespace cv07
{
    internal class cv07
    {
        static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            var app = builder.Build();

            builder.Services.AddSingleton<ExceptionHandler>();
            builder.Services.AddSingleton<TxtLogger>();
            
            app.UseMiddleware<ErrorHandlerMiddleware>();
            app.UseMiddleware<FirstMiddleware>();
            app.UseMiddleware<TestMiddleware>();
            app.UseMiddleware<FileMiddleware>();
            
            
            app.MapGet("/mrdka", () =>
            {
                return TypedResults.Content("<h1>JE TO MRDKA</h1><p>MRTKA</p>", "text/html; charset=utf-8");
            });
            
            app.Run();
        }
    }
}