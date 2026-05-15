set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(StringListLib src/StringList.h
        src/StringList.cpp)

target_include_directories(StringListLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(StringList src/main.cpp)
target_link_libraries(StringList PRIVATE StringListLib)

add_subdirectory(test)

target_compile_definitions(StringListTest PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")