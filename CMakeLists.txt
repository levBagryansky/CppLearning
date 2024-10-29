cmake_minimum_required(VERSION 3.25)
project(CppLearning)

set(CMAKE_CXX_STANDARD 23)

# set(Boost_USE_STATIC_LIBS OFF)
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME OFF)
# find_package(Boost COMPONENTS )

# if(Boost_FOUND)
    # include_directories(${Boost_INCLUDE_DIRS})
# endif()

# Adding testing
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip # release 1.15.2
)
FetchContent_MakeAvailable(googletest)

function(my_test SOURCE_NAME)
    get_filename_component(TARGET_NAME ${SOURCE_NAME} NAME_WE)
    add_executable(
            ${TARGET_NAME}
            ${SOURCE_NAME}
    )
    target_link_libraries(
            ${TARGET_NAME}
            GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(${TARGET_NAME})
    add_custom_target(${TARGET_NAME}_run
            COMMAND ./${TARGET_NAME}
            )
    add_dependencies(test ${TARGET_NAME}_run)

    target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
    if (MEMSAN)
        set(TARGET_NAME_SAN ${TARGET_NAME}_memsan)
        add_executable(
                ${TARGET_NAME_SAN}
                ${SOURCE_NAME}
        )
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

add_custom_target(test)
if (MEMSAN)
    add_custom_target(test-san)
endif ()
# Adding testing

add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
