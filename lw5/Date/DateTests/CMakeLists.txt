add_executable(DateTests
        DateTests.cpp)

target_link_libraries(DateTests PRIVATE DateLib)
target_link_libraries(DateTests PRIVATE Catch2::Catch2WithMain)