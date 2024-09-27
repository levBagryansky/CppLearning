@echo off
mkdir build
cd build
cmake ../ -G "Visual Studio 16 2019" -A x64
echo Launch VS project? (y/n)
set /p answer=
if %answer% == y goto launch
exit
:launch
CppLearning.sln
exit