using Microsoft.AspNetCore.Builder;
using System;
using System.Diagnostics;

namespace SqreenHeader
{
    public static class HeaderMiddleware
    {
        public static void SetupHeaderMiddleware(this IApplicationBuilder app) 
        {
            Console.WriteLine($"app {app}");
            app.Use(async (context, next) =>
            {
                context.Response.Headers.Add("X-Instrumented-By", "Sqreen");
                await next.Invoke();
            });
        }
    }
}
