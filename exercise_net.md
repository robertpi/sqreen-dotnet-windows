# .NET Agent Owner technical exercise
## Exercise
The exercise consists in forcing a Kestrel server to send a new HTTP header to the user,  *without modifying the server source code nor configuration*:

When running a default Kestrel server, the following occurs:
    $ curl -I http://<my-docker-host>:8888/
    HTTP/1.1 200 OK
    Date: Tue, 02 Jun 2020 21:47:47 GMT
    Content-Type: text/html; charset=utf-8
    Server: Kestrel

We would like to make it return one additional header:
    $ curl -I http://<my-docker-host>:8888/
    HTTP/1.1 200 OK
    [...]
    X-Instrumented-By: Sqreen

This should be done by injecting a library in the .Net process, using env variables such as CORECLR_ENABLE_PROFILING or CORECLR_PROFILER. The important thing is to remember we need to not change the source code, and not change the configuration.

## Deliverables
Share your solution in a GitHub repository. Feel free to make it public or to keep it private, but in this case invite the following users:
  aviat
  stombre
  zetaben

A Dockerfile should help test the result.

## This is an exercise
The code you will produce is part of our technical interview process. You'll own obviously property on everything you will produce.
