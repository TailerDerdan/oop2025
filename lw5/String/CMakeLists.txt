set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(StringLib CString/CString.cpp CString/CString.h)

target_include_directories(StringLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CString)

add_executable(String CString/main.cpp)
target_link_libraries(String PRIVATE StringLib)

add_subdirectory(StringTests)

target_compile_definitions(StringTests PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")