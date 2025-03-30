find_package(benchmark REQUIRED COMPONENTS)

add_executable(SsoBench sso-bench.cpp)
target_compile_options(SsoBench PRIVATE -O0)
target_link_libraries(SsoBench PRIVATE benchmark::benchmark)

add_custom_target(SsoBench_run
        COMMAND ./SsoBench
        DEPENDS SsoBench
        )
add_dependencies(test SsoBench_run)
