add_executable(AddExceptions 03.17.class.operator.overload.cpp)

add_custom_target(AddExceptions_run
        COMMAND ./AddExceptions
        )
target_link_libraries(AddExceptions ${Boost_LIBRARIES})

#add_dependencies(test AddExceptions_run)
