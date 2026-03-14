set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(BankLib CBank/CBank.cpp
        CBank/CBank.h
        CBank/Actor.cpp
        CBank/Actor.h
        CBank/Simulation.cpp
        CBank/Simulation.h
        CBank/Actors.cpp
        CBank/Actors.h)

add_executable(Bank CBank/main.cpp)
target_link_libraries(Bank PRIVATE BankLib)

target_include_directories(BankLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Bank)

add_subdirectory(CBankTests)

target_compile_definitions(TestsBank PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")