set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_library(ShapesLib
        CShapes/IShape.h
        CShapes/ISolidShape.h
        CShapes/CPoint.h
        CShapes/CLineSegment.cpp
        CShapes/CLineSegment.h
        CShapes/CTriangle.cpp
        CShapes/CTriangle.h
        CShapes/CRectangle.cpp
        CShapes/CRectangle.h
        CShapes/CCircle.cpp
        CShapes/CCircle.h
        CShapes/CController.cpp
        CShapes/CController.h
        CShapes/ICanvas.h
        CShapes/CCanvas.cpp
        CShapes/CCanvas.h
        CShapes/CMockCanvas.h)


target_link_libraries(ShapesLib PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)

target_include_directories(ShapesLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CShapes)


add_executable(Shapes CShapes/main.cpp)
target_link_libraries(Shapes PRIVATE ShapesLib)

add_subdirectory(CShapesTests)

target_compile_definitions(CShapesTests PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")