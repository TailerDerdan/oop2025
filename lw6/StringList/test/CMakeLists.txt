add_executable(StringListTest
        test.cpp)

target_link_libraries(StringListTest PRIVATE StringListLib)
target_link_libraries(StringListTest PRIVATE Catch2::Catch2WithMain)