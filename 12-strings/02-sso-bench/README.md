## Testing threshold for Small String Optimization

```shell
$ cmake . -B build
$ cd build
$ make && make SSoBench_run

Run on (12 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 512 KiB (x6)
  L3 Unified 4096 KiB (x2)
Load Average: 1.13, 1.06, 1.00
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-----------------------------------------------------
Benchmark           Time             CPU   Iterations
-----------------------------------------------------
test/3           42.8 ns         42.8 ns     16201255
test/4           41.8 ns         41.8 ns     16517416
test/5           42.1 ns         42.1 ns     16624197
test/6           42.1 ns         42.0 ns     16884837
test/7           42.2 ns         42.2 ns     16622017
test/8           42.0 ns         42.0 ns     16669382
test/9           43.0 ns         43.0 ns     16017853
test/10          42.3 ns         42.3 ns     16448103
test/11          42.5 ns         42.5 ns     16545554
test/12          42.6 ns         42.6 ns     16457550
test/13          42.4 ns         42.4 ns     16037606
test/14          41.8 ns         41.8 ns     16530116
test/15          42.1 ns         42.1 ns     16597016
test/16           100 ns          100 ns      6696073
test/17           101 ns          101 ns      6896227
test/18           100 ns          100 ns      6913459
test/19          99.9 ns         99.9 ns      7054928
test/20           102 ns          102 ns      6972723
test/30           103 ns          103 ns      6818765
test/60          99.7 ns         99.7 ns      6942552
test/120          100 ns          100 ns      6936806
test/240         98.2 ns         98.2 ns      6960716
test/480          100 ns          100 ns      7026788
test/1000         102 ns          102 ns      6922562
```
### The maximum size of the string placed on the stack is ***16***
