@echo off
mkdir build
cd build
cmake ../ -G "Visual Studio 17 2022" -A x64
echo Launch VS project? (y/n)
set /p answer=
if %answer% == y goto launch
exit
:launch
CppLearning.sln
exit