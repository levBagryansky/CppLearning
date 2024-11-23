# How to build

```shell
clang++ -std=c++20 Entity.cppm --precompile -o Entity.pcm -stdlib=libc++
clang++ -std=c++20 main.cpp -fmodule-file=entity=Entity.pcm Entity.pcm -o Hello.out -stdlib=libc++
```
