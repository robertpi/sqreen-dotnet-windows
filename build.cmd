@echo off

echo Build the C++ Profiling API source
pushd profiler
call build.cmd
popd

echo Build the aspnet test harness
pushd SqreenAspNetCore
dotnet build

echo Start the web server
pushd SqreenAspNetCoreDemo
call start.cmd
popd
popd