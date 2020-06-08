@echo off
pushd runtime
REM Save time by just building coreclr: https://github.com/dotnet/runtime/blob/master/docs/workflow/building/coreclr/README.md
call build.cmd -subset clr
popd