## Comparison calling of virtual method with non-virtual:

```shell
Running ./Bench
Run on (12 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 512 KiB (x6)
  L3 Unified 4096 KiB (x2)
Load Average: 1.81, 1.22, 0.87
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
test<Derived1>       3.77 ns         3.77 ns    182411542
test<Base>           3.78 ns         3.78 ns    185554512
tardis3@RyanGosling:~/CppLearning/build/07/09-Bench$ make && ./Bench 
[100%] Built target Bench
2024-12-07T18:40:38+03:00
Running ./Bench
Run on (12 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 512 KiB (x6)
  L3 Unified 4096 KiB (x2)
Load Average: 1.28, 1.15, 0.85
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
test<Derived1>       3.79 ns         3.77 ns    185605764   # Non-virtual
test<Base>           4.21 ns         4.19 ns    166795157   # Virtual
```
