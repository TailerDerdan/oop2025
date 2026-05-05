add_executable(StringTests
        StringTests.cpp)

target_link_libraries(StringTests PRIVATE StringLib)
target_link_libraries(StringTests PRIVATE Catch2::Catch2WithMain)