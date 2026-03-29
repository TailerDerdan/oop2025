#include <catch2/catch_test_macros.hpp>

#include "CCanvas.h"
#include "CCircle.h"
#include "CController.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CMockCanvas.h"
#include "CRectangle.h"

TEST_CASE("test command with color")
{
    std::istringstream input;
    std::ostringstream output;
    CCanvas canvas;
    CController controller(input, output, canvas);

    SECTION("error color")
    {
        input.str("circle 8 19 6.78 zzzzzz");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid color format\n");
        output.str("");
        input.clear();

        input.str("circle 8 19 6.78 !%@$!^@");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid color format\n");
        output.str("");
        input.clear();
    }

    SECTION("valid color")
    {
        input.str("circle 8 19 6.78 00ff00ff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("circle 8 19 6.78 00ff00ff ffff00ff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();
    }
}

TEST_CASE("test triangle")
{
    std::istringstream input;
    std::ostringstream output;
    CCanvas canvas;
    CController controller(input, output, canvas);

    SECTION("error triangle")
    {
        input.str("triangle");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid triangle format\n");
        output.str("");
        input.clear();

        input.str("triangle 8");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid triangle format\n");
        output.str("");
        input.clear();

        input.str("triangle §¡•¶™£§");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid triangle format\n");
        output.str("");
        input.clear();
    }

    SECTION("valid triangle")
    {
        input.str("triangle 7 7 7 7 7 7 7 7 7 7 7");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("triangle 10 10 100 10 10 100");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("triangle 10 10 100 10 10 100 ff00ffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("triangle 10 10 100 10 10 100 ffffffff ffaaffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();
    }

    SECTION("draw triangle")
    {
        MockCanvas mockCanvas;
        CPoint pointA{};
        pointA.x = 10;
        pointA.y = 10;

        CPoint pointB{};
        pointB.x = 100;
        pointB.y = 10;

        CPoint pointC{};
        pointB.x = 10;
        pointB.y = 100;

        uint32_t fillColor = 0x00FF00FF;

        CTriangle triangle(pointA, pointB, pointC, fillColor);
        triangle.Draw(mockCanvas);
        REQUIRE(mockCanvas.CallCount(Methods::DrawLine) == 3);
        REQUIRE(mockCanvas.CallCount(Methods::FillPolygon) == 1);
        mockCanvas.ClearCalls();

        CTriangle triangleWithoutFillColor(pointA, pointB, pointC, std::nullopt);
        triangleWithoutFillColor.Draw(mockCanvas);
        REQUIRE(mockCanvas.CallCount(Methods::DrawLine) == 3);
        REQUIRE(mockCanvas.CallCount(Methods::FillPolygon) == 0);
    }
}

TEST_CASE("test line")
{
    std::istringstream input;
    std::ostringstream output;
    CCanvas canvas;
    CController controller(input, output, canvas);

    SECTION("error line")
    {
        input.str("line");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid line format\n");
        output.str("");
        input.clear();

        input.str("line 8");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid line format\n");
        output.str("");
        input.clear();

        input.str("line §¡•¶™£§");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid line format\n");
        output.str("");
        input.clear();
    }

    SECTION("valid line")
    {
        input.str("line 7 7 7 7 7 7 7 7 7 7 7");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("line 10 10 100 10");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("line 10 10 100 10 ff00ffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("line 10 10 100 10 ffffffff ffaaffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();
    }

    SECTION("draw line")
    {
        MockCanvas mockCanvas;
        CPoint pointA{};
        pointA.x = 10;
        pointA.y = 10;

        CPoint pointB{};
        pointB.x = 100;
        pointB.y = 10;

        uint32_t fillColor = 0x00FF00FF;

        CLineSegment line(pointA, pointB, fillColor);
        line.Draw(mockCanvas);
        REQUIRE(mockCanvas.CallCount(Methods::DrawLine) == 1);
        REQUIRE(mockCanvas.CallCount(Methods::FillPolygon) == 0);
        mockCanvas.ClearCalls();
    }
}

TEST_CASE("test circle")
{
    std::istringstream input;
    std::ostringstream output;
    CCanvas canvas;
    CController controller(input, output, canvas);

    SECTION("error circle")
    {
        input.str("circle");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid circle format\n");
        output.str("");
        input.clear();

        input.str("circle 8");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid circle format\n");
        output.str("");
        input.clear();

        input.str("circle §¡•¶™£§");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid circle format\n");
        output.str("");
        input.clear();
    }

    SECTION("valid circle")
    {
        input.str("circle 7 7 7 7 7 7 7 7 7 7 7");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("circle 10 10 100");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("circle 10 10 100 ff00ffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("circle 10 10 100 ffffffff ffaaffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();
    }

    SECTION("draw circle")
    {
        MockCanvas mockCanvas;
        CPoint center{};
        center.x = 10;
        center.y = 10;

        uint32_t fillColor = 0x00FF00FF;

        CCircle circle(center, 100, fillColor);
        circle.Draw(mockCanvas);
        REQUIRE(mockCanvas.CallCount(Methods::DrawCircle) == 1);
        REQUIRE(mockCanvas.CallCount(Methods::FillCircle) == 1);
        mockCanvas.ClearCalls();

        CCircle circleWithoutFillColor(center, 100, std::nullopt);
        circleWithoutFillColor.Draw(mockCanvas);
        REQUIRE(mockCanvas.CallCount(Methods::DrawCircle) == 1);
        REQUIRE(mockCanvas.CallCount(Methods::FillCircle) == 0);
    }
}

TEST_CASE("test rectangle")
{
    std::istringstream input;
    std::ostringstream output;
    CCanvas canvas;
    CController controller(input, output, canvas);

    SECTION("error rectangle")
    {
        input.str("rectangle");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid rectangle format\n");
        output.str("");
        input.clear();

        input.str("rectangle 8");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid rectangle format\n");
        output.str("");
        input.clear();

        input.str("rectangle §¡•¶™£§");
        controller.HandleCommand();
        REQUIRE(output.str() == "Error: invalid rectangle format\n");
        output.str("");
        input.clear();
    }

    SECTION("valid rectangle")
    {
        input.str("rectangle 7 7 7 7 7 7 7 7 7 7 7");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("rectangle 10 10 100 50");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("rectangle 10 10 100 50 ff00ffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("rectangle 10 10 100 50 ffffffff ffaaffff");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();
    }

    SECTION("draw rectangle")
    {
        MockCanvas mockCanvas;
        CPoint leftTop{};
        leftTop.x = 10;
        leftTop.y = 10;

        uint32_t fillColor = 0x00FF00FF;

        CRectangle rect(leftTop, 100, 50, fillColor);
        rect.Draw(mockCanvas);
        REQUIRE(mockCanvas.CallCount(Methods::DrawLine) == 4);
        REQUIRE(mockCanvas.CallCount(Methods::FillPolygon) == 1);
        mockCanvas.ClearCalls();

        CRectangle rectWithoutFillColor(leftTop, 100, 50, std::nullopt);
        rectWithoutFillColor.Draw(mockCanvas);
        REQUIRE(mockCanvas.CallCount(Methods::DrawLine) == 4);
        REQUIRE(mockCanvas.CallCount(Methods::FillPolygon) == 0);
    }
}

TEST_CASE("check max area and min perimetr")
{
    std::istringstream input;
    std::ostringstream output;
    CCanvas canvas;
    CController controller(input, output, canvas);

    SECTION("max area")
    {
        input.str("rectangle 10 10 100 100");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("circle 10 10 50");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("triangle 10 10 50 50 10 50");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("exit");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        REQUIRE(controller.GetShapeWithMaxArea()->GetArea() == 10000);
    }

    SECTION("min perimetr")
    {
        input.str("rectangle 10 10 100 100");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("circle 10 10 50");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("triangle 10 10 50 50 10 50");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("line 10 10 10 50");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("exit");
        controller.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        REQUIRE(controller.GetShapeWithMinPerimetr()->GetPerimetr() == 40);
    }
}