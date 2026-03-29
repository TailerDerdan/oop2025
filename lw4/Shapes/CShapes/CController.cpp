#include "CController.h"

#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"

#include <sstream>

CController::CController(std::istream& input, std::ostream& output, ICanvas& canvas)
    : m_input(input)
    , m_output(output)
    , m_canvas(canvas)
    , m_actionMap({
        { "line",      [this]() { DefineLine();      } },
        { "triangle",  [this]() { DefineTriangle();  } },
        { "rectangle", [this]() { DefineRectangle(); } },
        { "circle",    [this]() { DefineCircle();    } },
    })
{
}

bool CController::HandleCommand()
{
    std::string command;
    m_input >> command;

    if (command == "exit")
    {
        return false;
    }

    if (const auto commandIter = m_actionMap.find(command); commandIter != m_actionMap.end())
    {
        try
        {
            commandIter->second();
        }
        catch (const std::exception& e)
        {
            m_output << e.what() << std::endl;
        }
    }
    else
    {
        m_output << "Unknow command!" << std::endl;
    }
    return true;
}

void CController::DefineLine()
{
    std::string line;
    std::getline(m_input, line);
    std::istringstream iss(line);

    float x1, y1, x2, y2;
    if (!(iss >> x1 >> y1 >> x2 >> y2))
    {
        m_output << "Error: invalid line format" << std::endl;
        return;
    }

    CPoint startPoint{ x1, y1 };
    CPoint endPoint{ x2, y2 };

    std::string colorStr;
    if (iss >> colorStr)
    {
        try
        {
            uint32_t outlineColor = std::stoul(colorStr, nullptr, 16);
            m_shapes.push_back(std::make_unique<CLineSegment>(startPoint, endPoint, outlineColor));
        }
        catch (const std::exception&)
        {
            m_output << "Error: invalid color format" << std::endl;
        }
    }
    else
    {
        m_shapes.push_back(std::make_unique<CLineSegment>(startPoint, endPoint));
    }
}

void CController::DefineTriangle()
{
    std::string line;
    std::getline(m_input, line);
    std::istringstream iss(line);

    float x1, y1, x2, y2, x3, y3;
    if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3))
    {
        m_output << "Error: invalid triangle format" << std::endl;
        return;
    }

    CPoint pointA{ x1, y1 };
    CPoint pointB{ x2, y2 };
    CPoint pointC{ x3, y3 };

    std::string token1, token2;
    bool hasToken1 = false;
    bool hasToken2 = false;

    if (iss >> token1)
    {
        hasToken1 = true;
    }
    if (iss >> token2)
    {
        hasToken2 = true;
    }

    try
    {
        if (hasToken1 && hasToken2)
        {
            uint32_t outlineColor = std::stoul(token1, nullptr, 16);
            uint32_t fillColor    = std::stoul(token2, nullptr, 16);
            m_shapes.push_back(std::make_unique<CTriangle>(pointA, pointB, pointC, fillColor, outlineColor));
        }
        else if (hasToken1)
        {
            uint32_t outlineColor = std::stoul(token1, nullptr, 16);
            m_shapes.push_back(std::make_unique<CTriangle>(pointA, pointB, pointC, std::nullopt, outlineColor));
        }
        else
        {
            m_shapes.push_back(std::make_unique<CTriangle>(pointA, pointB, pointC, std::nullopt));
        }
    }
    catch (const std::exception&)
    {
        m_output << "Error: invalid color format" << std::endl;
    }
}

void CController::DefineRectangle()
{
    std::string line;
    std::getline(m_input, line);
    std::istringstream iss(line);

    float x1, y1, width, height;
    if (!(iss >> x1 >> y1 >> width >> height))
    {
        m_output << "Error: invalid rectangle format" << std::endl;
        return;
    }

    CPoint leftTop{ x1, y1 };

    std::string token1, token2;
    bool hasToken1 = false;
    bool hasToken2 = false;

    if (iss >> token1)
    {
        hasToken1 = true;
    }
    if (iss >> token2)
    {
        hasToken2 = true;
    }

    try
    {
        if (hasToken1 && hasToken2)
        {
            uint32_t outlineColor = std::stoul(token1, nullptr, 16);
            uint32_t fillColor    = std::stoul(token2, nullptr, 16);
            m_shapes.push_back(std::make_unique<CRectangle>(leftTop, width, height, fillColor, outlineColor));
        }
        else if (hasToken1)
        {
            uint32_t outlineColor = std::stoul(token1, nullptr, 16);
            m_shapes.push_back(std::make_unique<CRectangle>(leftTop, width, height, std::nullopt, outlineColor));
        }
        else
        {
            m_shapes.push_back(std::make_unique<CRectangle>(leftTop, width, height, std::nullopt));
        }
    }
    catch (const std::exception&)
    {
        m_output << "Error: invalid color format" << std::endl;
    }
}

void CController::DefineCircle()
{
    std::string line;
    std::getline(m_input, line);
    std::istringstream iss(line);

    float x1, y1, radius;
    if (!(iss >> x1 >> y1 >> radius))
    {
        m_output << "Error: invalid circle format" << std::endl;
        return;
    }

    CPoint center{ x1, y1 };

    std::string token1, token2;
    bool hasToken1 = false;
    bool hasToken2 = false;

    if (iss >> token1)
    {
        hasToken1 = true;
    }
    if (iss >> token2)
    {
        hasToken2 = true;
    }

    try
    {
        if (hasToken1 && hasToken2)
        {
            uint32_t outlineColor = std::stoul(token1, nullptr, 16);
            uint32_t fillColor    = std::stoul(token2, nullptr, 16);
            m_shapes.push_back(std::make_unique<CCircle>(center, radius, fillColor, outlineColor));
        }
        else if (hasToken1)
        {
            uint32_t outlineColor = std::stoul(token1, nullptr, 16);
            m_shapes.push_back(std::make_unique<CCircle>(center, radius, std::nullopt, outlineColor));
        }
        else
        {
            m_shapes.push_back(std::make_unique<CCircle>(center, radius, std::nullopt));
        }
    }
    catch (const std::exception&)
    {
        m_output << "Error: invalid color format" << std::endl;
    }
}

IShape* CController::GetShapeWithMaxArea() const
{
    if (m_shapes.empty())
    {
        return nullptr;
    }

    auto shape = std::max_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b)
        {
            return a->GetArea() < b->GetArea();
        });
    return shape->get();
}

IShape* CController::GetShapeWithMinPerimetr() const
{
    if (m_shapes.empty())
    {
        return nullptr;
    }

    auto shape = std::min_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b)
        {
            return a->GetPerimetr() < b->GetPerimetr();
        });

    return shape->get();
}

void CController::DrawShapes()
{
    for (auto& shape : m_shapes)
    {
        shape->Draw(m_canvas);
    }
}
