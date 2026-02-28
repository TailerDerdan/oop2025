#include <catch2/catch_test_macros.hpp>
#include "CalculatorUI.h"

TEST_CASE("test base command")
{
    std::istringstream input;
    std::ostringstream output;
    Calculator calculator;
    CalculatorUI calculatorUI(input, output, calculator);

    SECTION("Unknown command")
    {
        input.str("unknownCmd");
        calculatorUI.HandleCommand();
        REQUIRE(output.str() == "Unknow command!\n");
    }

    SECTION("Valid command")
    {
        input.str("var x");
        calculatorUI.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("let x=10");
        calculatorUI.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("fn xx=x+x");
        calculatorUI.HandleCommand();
        REQUIRE(output.str().empty());
        output.str("");
        input.clear();

        input.str("print x");
        calculatorUI.HandleCommand();
        REQUIRE(output.str() == "10.00\n");
        output.str("");
        input.clear();

        input.str("print xx");
        calculatorUI.HandleCommand();
        REQUIRE(output.str() == "20.00\n");
        output.str("");
        input.clear();

        input.str("printvars");
        calculatorUI.HandleCommand();
        REQUIRE(output.str() == "x:10.00\n");
        output.str("");
        input.clear();

        input.str("printfns");
        calculatorUI.HandleCommand();
        REQUIRE(output.str() == "xx:20.00\n");
        output.str("");
        input.clear();
    }
}

TEST_CASE("test base operation")
{
    std::istringstream input;
    std::ostringstream output;
    Calculator calculator;
    CalculatorUI calculatorUI(input, output, calculator);

    input.str("let x=10");
    calculatorUI.HandleCommand();

    input.clear();
    input.str("let y=20");
    calculatorUI.HandleCommand();

    output.str("");

    SECTION("Add")
    {
        input.clear();
        input.str("fn xy1=x+y");
        calculatorUI.HandleCommand();

        input.clear();
        input.str("print xy1");
        calculatorUI.HandleCommand();

        REQUIRE(output.str() == "30.00\n");
        output.str("");
    }

    SECTION("Sub")
    {
        input.clear();
        input.str("fn xy2=x-y");
        calculatorUI.HandleCommand();

        input.clear();
        input.str("print xy2");
        calculatorUI.HandleCommand();

        REQUIRE(output.str() == "-10.00\n");
        output.str("");
    }

    SECTION("Div")
    {
        input.clear();
        input.str("fn xy3=y/x");
        calculatorUI.HandleCommand();

        input.clear();
        input.str("print xy3");
        calculatorUI.HandleCommand();

        REQUIRE(output.str() == "2.00\n");
        output.str("");
    }

    SECTION("Mul")
    {
        input.clear();
        input.str("fn xy4=x*y");
        calculatorUI.HandleCommand();

        input.clear();
        input.str("print xy4");
        calculatorUI.HandleCommand();

        REQUIRE(output.str() == "200.00\n");
    }
}

TEST_CASE("test fibonachi")
{
    std::istringstream input;
    std::ostringstream output;
    Calculator calculator;
    CalculatorUI calculatorUI(input, output, calculator);

    input.clear();
    input.str("let fb1=1");
    calculatorUI.HandleCommand();

    input.clear();
    input.str("let fb2=1");
    calculatorUI.HandleCommand();

    std::string line;
    for (size_t iter = 3; iter <= 50; iter++)
    {
        input.clear();
        line = "fn fb" + std::to_string(iter) + "=fb" + std::to_string(iter - 2) + "+fb" + std::to_string(iter - 1);
        input.str(line);
        calculatorUI.HandleCommand();
    }
    output.str("");

    input.clear();
    input.str("print fb50");
    calculatorUI.HandleCommand();
    REQUIRE(output.str() == "12586269025.00\n");
}

//оптимизировать
TEST_CASE("test very long depend")
{
    std::istringstream input;
    std::ostringstream output;
    Calculator calculator;
    CalculatorUI calculatorUI(input, output, calculator);

    input.clear();
    input.str("let x=1");
    calculatorUI.HandleCommand();

    input.clear();
    input.str("fn x2=x+x");
    calculatorUI.HandleCommand();

    std::string line;
    for (size_t iter = 3; iter <= 1000000; iter++)
    {
        line = "fn x" + std::to_string(iter) + "=x" + std::to_string(iter - 1) + "+x";
        input.clear();
        input.str(line);
        calculatorUI.HandleCommand();
    }
    output.str("");

    input.clear();
    input.str("print x1000000");
    calculatorUI.HandleCommand();
    REQUIRE(output.str() == "1000000.00\n");

    input.clear();
    input.str("let x=2");
    calculatorUI.HandleCommand();

    input.clear();
    input.str("print x1000000");
    calculatorUI.HandleCommand();

    REQUIRE(output.str() == "2000000.00\n");
}