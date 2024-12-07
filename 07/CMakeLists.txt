add_subdirectory(01-SquareEquation)
add_subdirectory(05-AddExceptions)
add_subdirectory(03-person-optional)

find_package(benchmark COMPONENTS)
if(benchmark_FOUND)
    message(STATUS "Found benchmark")
    add_subdirectory(09-Bench)
else()
    message(WARNING "Did not find benchmark")
endif()

add_subdirectory(10-BinSearchTest)
