@echo off

REM more meaningful name
SET BatchDir=%~dp0


REM activates .NET Core's internal logging, will only work for a debug build
SET COMPlus_LogLevel=10
SET COMPlus_LogFacility=FFFFFFFF
SET COMPlus_StressLogSize=2000000
SET COMPlus_TotalStressLogSize=40000000
SET COMPlus_LogEnable=1
SET COMPlus_LogToConsole=1
SET COMPlus_LogToFile=1
SET COMPlus_LogFile=c:\code\rotor.log

REM Setup the profiling dll
SET CORECLR_PROFILER={88E5B029-D6B4-4709-B445-03E9BDAB2FA2}
SET CORECLR_ENABLE_PROFILING=1
SET CORECLR_PROFILER_PATH=%BatchDir%\..\..\profiler\bin\Debug\ClrProfiler.dll
SET CORECLR_PROFILER_HOME=%BatchDir%\bin\Debug\netcoreapp3.1\

REM run the app
dotnet run SqreenAspNetCoreDemo