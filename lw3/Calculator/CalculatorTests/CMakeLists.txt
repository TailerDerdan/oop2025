find_package(Catch2 3 REQUIRED)

add_executable(Catch_Tests_Run
        Calculator_Tests.cpp)

target_link_libraries(Catch_Tests_Run PRIVATE Calculator_lib)
target_link_libraries(Catch_Tests_Run PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(Catch_Tests_Run)