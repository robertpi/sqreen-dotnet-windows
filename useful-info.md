CoreClr
=======

How to build coreclr from source on docker: https://github.com/dotnet/coreclr/blob/v3.1.4/Documentation/building/linux-instructions.md

Bit about logging: https://books.google.fr/books?id=XibbpjWeRlMC&pg=PA41&lpg=PA41&dq=rotor+logging&source=bl&ots=33DH32wCzh&sig=ACfU3U0d4oH3G1eSujuC6mpONOSkNAEV9g&hl=en&sa=X&ved=2ahUKEwjRjK3Yp_HpAhXR8uAKHe1PDm4Q6AEwFXoECA0QAQ#v=onepage&q=rotor%20logging&f=false

Why is building from source useful? Logging: https://mattwarren.org/2018/03/23/Exploring-the-internals-of-the-.NET-Runtime/

Dot Net Part
============

Explains how to add a custom header, not too hard: https://stackoverflow.com/questions/46183171/how-to-add-custom-header-to-asp-net-core-web-api-response


Profiling API
=============

Example, suggests building coreclr is not necessary: https://github.com/david-mitchell/CoreCLRProfiler

Profiler API sample (seems out of date): https://github.com/Microsoft/clr-samples


Profiler API sample (the one we'll use): https://github.com/caozhiyuan/ClrProfiler.Trace

sudo apt-get install curl unzip tar
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update -y
sudo apt-get install g++-7 -y
cd ~/vcpkg
./bootstrap-vcpkg.sh
./vcpkg install spdlog

Docker
======

Building docker from multiple images: https://stackoverflow.com/questions/39626579/is-there-a-way-to-combine-docker-images-into-1-container


Build times
===========

Windows build.cmd -subset clr: Time Elapsed 00:09:46.20