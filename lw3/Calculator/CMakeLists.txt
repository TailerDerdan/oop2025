cmake_minimum_required(VERSION 3.20)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Calculator)

add_library(Calculator_lib
        Calculator/Calculator.cpp
        Calculator/Calculator.h
        Calculator/CalculatorUI.cpp
        Calculator/CalculatorUI.h
        Calculator/CFunction.cpp
        Calculator/CFunction.h
        Calculator/CVariable.cpp
        Calculator/CVariable.h
        Calculator/IObservable.h
        Calculator/IObserver.h
        Calculator/IValue.h
        Calculator/CObservable.cpp
        Calculator/CObservable.h)

add_executable(Calculator Calculator/main.cpp)
target_link_libraries(Calculator PRIVATE Calculator_lib)

target_include_directories(Calculator_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Calculator)

add_subdirectory(CalculatorTests)

target_compile_definitions(Catch_Tests_Run PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")