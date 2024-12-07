find_package(benchmark REQUIRED COMPONENTS)

add_executable(Bench bench.cpp)
target_compile_options(Bench PRIVATE -O0)
target_link_libraries(Bench PRIVATE benchmark::benchmark)

add_custom_target(Bench_run
        COMMAND ./Bench
        )
add_dependencies(test Bench_run)
