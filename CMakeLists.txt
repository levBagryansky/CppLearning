cmake_minimum_required(VERSION 3.25)
project(CppLearning)

set(CMAKE_CXX_STANDARD 23)

# Adding testing
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip # release 1.15.2
)
FetchContent_MakeAvailable(googletest)

function(cxec_test SOURCE_NAME)
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
endfunction(cxec_test)

add_custom_target(test)
# Adding testing

add_subdirectory(01)
add_subdirectory(02)
