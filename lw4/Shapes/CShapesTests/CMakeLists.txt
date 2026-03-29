add_executable(CShapesTests
        CShapesTests.cpp)

target_link_libraries(CShapesTests PRIVATE ShapesLib)
target_link_libraries(CShapesTests PRIVATE Catch2::Catch2WithMain)