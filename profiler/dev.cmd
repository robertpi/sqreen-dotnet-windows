cd /d %~dp0

SET WorkDir=%~dp0

SET CORECLR_PROFILER={cf0d821e-299b-5307-a3d8-b283c03916dd}
SET CORECLR_ENABLE_PROFILING=1
SET CORECLR_PROFILER_PATH=%WorkDir%src\ClrProfiler\x64\Debug\ClrProfiler.dll
SET CORECLR_PROFILER_HOME=%WorkDir%src\ClrProfiler.Trace\bin\Debug\netstandard2.0

SET COR_PROFILER={af0d821e-299b-5307-a3d8-b283c03916dd}
SET COR_ENABLE_PROFILING=1
SET COR_PROFILER_PATH=%WorkDir%src\ClrProfiler\x64\Debug\ClrProfiler.dll
SET COR_PROFILER_HOME=%WorkDir%src\ClrProfiler.Trace\bin\Debug\net461

echo Starting Visual Studio...
set _VSWHERE="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist %_VSWHERE% (
  for /f "usebackq tokens=*" %%i in (`%_VSWHERE% -latest -prerelease -property installationPath`) do set _VSPATH=%%i
)
START "Visual Studio" "%_VSPATH%\Common7\IDE\devenv.exe" "%~dp0\src\ClrProfiler.sln"
