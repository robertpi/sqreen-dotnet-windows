
This the implementation of ["How to add a header without changing the code base" home asignment](exercise_net.md). 

*Warning: this will clone and build the [.NET Runtime](https://github.com/dotnet/runtime/), so requires 10 GB of disk-space once build*

Building
========

Currently there only build scripts for Windows. The C# parts will already work under Windows, Linux, macOS & FreeBSD, but the profiler will need build scripts for *nix OSs.

First ensure you have all the [dependencies for Windows](https://github.com/dotnet/runtime/blob/master/docs/workflow/requirements/windows-requirements.md). To ensure all the correct packages from Visual Studio are installed make sure you import [runtime/.vsconfig](runtime/.vsconfig) into the visual studio installer, for more details [how to do this](https://docs.microsoft.com/en-us/visualstudio/install/import-export-installation-configurations?view=vs-2019).

Testing
=======

Hit http://localhost:5000/ in your favourite browser / tool.

![browser screenshot](MozillaFirefox.png)

Architecture
============

To complete this project there are three steps:

1. Build the coreclr source to obtain the necessary header and linker files to build the profiling API
2. Create a profiler that will listen to the JIT profiling events and rewrite certain methods before the JIT
3. Create a C# dll containing the methods to be injected, and also a test harness website to test the injection 


## Step One

Step one is fairly straight forward but can be time consuming to ensure all dependencies are sent up correctly to complete the build.

## Step Two

Step two is technically challenging, but fortunately there are some existing samples that are similar to what we want to achieve.

The code from this exercise is a modified version of [ClrProfiler.Trace](https://github.com/caozhiyuan/ClrProfiler.Trace). This project demonstrates how to inject C# code into a C# application being profiled, so the injected C# code can be responsible for collecting the trace data.

This project relies on an outdated way for preforming cross platform complication, so I replaced it with the build system from [doooot stacksampling](https://github.com/ghanysingh/doooot/tree/0b3bde45ecf74fff54b20c8e652cf9f961742de3/core/profiling/stacksampling) which uses cmake like coreclr.

## Step Three

The code for step three is trivial. Adding a header to an aspnet core app is straight forward:

```
        app.Use(async (context, next) =>
        {
            context.Response.Headers.Add("X-Instrumented-By", "Sqreen");
            await next.Invoke();
        });
```

For the test website one of the templates available in Visual Studio can be used. Rather that starting the website directly [a batch file](SqreenAspNetCore/SqreenAspNetCoreDemo/start.cmd) is used to set the necessary environment variables required to load the profiler.

TODO
====

- bash / *nix build scripts
- unit tests for the profiler code
- improve profiler code