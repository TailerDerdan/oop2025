set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(EquationRoot4Lib CEquationRoot4/CEquationRoot4.h
        CEquationRoot4/CEquationRoot4.cpp)

target_include_directories(EquationRoot4Lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CEquationRoot4)

add_executable(EquationRoot4 CEquationRoot4/main.cpp)
target_link_libraries(EquationRoot4 PRIVATE EquationRoot4Lib)

add_subdirectory(EquationRoot4Tests)

target_compile_definitions(EquationRoot4Tests PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")