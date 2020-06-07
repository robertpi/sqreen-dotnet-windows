using Microsoft.AspNetCore.Builder;
using System;

namespace SqreenHeader
{
    public static class HeaderMiddleware
    {
        public static void SetupHeaderMiddleware(this IApplicationBuilder app) 
        {
            app.Use(async (context, next) =>
            {
                context.Response.Headers.Add("X-Instrumented-By", "Sqreen");
                await next.Invoke();
            });
        }
    }
}
