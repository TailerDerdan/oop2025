set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DateLib CDate/CDate.cpp CDate/CDate.h)

target_include_directories(DateLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CDate)

add_executable(Date CDate/main.cpp)
target_link_libraries(Date PRIVATE DateLib)

add_subdirectory(DateTests)

target_compile_definitions(DateTests PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")