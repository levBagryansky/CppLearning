add_executable(05.02.pattern.factory 05.02.pattern.factory.cpp)
add_custom_target(05.02.pattern.factory_run
        COMMAND ./05.02.pattern.factory
        )
add_dependencies(test 05.02.pattern.factory_run)


