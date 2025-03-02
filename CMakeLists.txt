cmake_minimum_required(VERSION 3.26)
project(CppLearning)

set(CMAKE_CXX_STANDARD 23)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS )

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Adding testing
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip # release 1.15.2
)
FetchContent_MakeAvailable(googletest)

function(my_test)
    list(GET ARGN 0 SOURCE_NAME)
    list(REMOVE_AT ARGN 0)
    get_filename_component(TARGET_NAME ${SOURCE_NAME} NAME_WE)
    add_executable(
            ${TARGET_NAME}
            ${SOURCE_NAME}
    )
    foreach(arg IN LISTS ARGN)
        target_sources(${TARGET_NAME} PUBLIC ${arg})
    endforeach()
    target_link_libraries(
            ${TARGET_NAME}
            GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(${TARGET_NAME})
    add_custom_target(${TARGET_NAME}_run
            COMMAND ./${TARGET_NAME}
            DEPENDS ${TARGET_NAME}
            )
    add_dependencies(test ${TARGET_NAME}_run)

    target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
    if (MEMSAN)
        set(TARGET_NAME_SAN ${TARGET_NAME}_memsan)
        add_executable(
                ${TARGET_NAME_SAN}
                ${SOURCE_NAME}
        )
        foreach(arg IN LISTS ARGN)
            message(STATUS "Processing argument: ${arg}")
            target_sources(${TARGET_NAME_SAN} PRIVATE ${arg})
        endforeach()
        target_link_libraries(
                ${TARGET_NAME_SAN}
                GTest::gtest_main
        )
        include(GoogleTest)
        gtest_discover_tests(${TARGET_NAME_SAN})
        target_compile_options(${TARGET_NAME_SAN} PRIVATE -fsanitize=address -g -fsanitize=leak -fsanitize=undefined)
        target_link_options(${TARGET_NAME_SAN} PRIVATE -fsanitize=address -fsanitize=leak  -fsanitize=undefined)
        add_custom_target(${TARGET_NAME_SAN}_run
                COMMAND ./${TARGET_NAME_SAN}
                )
        add_dependencies(test-san ${TARGET_NAME_SAN}_run)
    endif()
endfunction(my_test)

# Make a test from .cpp file with main function inside.
function(my_executable filename)
    # Extract the base name without extension
    string(REGEX REPLACE "\\.[^.]+$" "" target_name ${filename})

    # Create an executable
    add_executable(${target_name} ${filename})

    # Create a custom target to run the executable
    add_custom_target(${target_name}_run
            COMMAND ./${target_name}
            DEPENDS ${target_name}
            )

    # Add a dependency to a test target (modify as needed)
    add_dependencies(test ${target_name}_run)
endfunction()

add_custom_target(test)
if (MEMSAN)
    add_custom_target(test-san)
endif ()
# Adding testing

add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)
add_subdirectory(09)
