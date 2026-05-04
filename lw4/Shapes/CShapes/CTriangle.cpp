#include "CTriangle.h"

#include <iomanip>
#include <sstream>
#include <ios>

CTriangle::CTriangle(
    const CPoint &pointA,
    const CPoint &pointB,
    const CPoint &pointC,
    std::optional<uint32_t> fillColor,
    uint32_t outlineColor
) : m_pointA(pointA),
    m_pointB(pointB),
    m_pointC(pointC)
{
    m_outlineColor = outlineColor;
    m_fillColor = fillColor;
}

double CTriangle::GetArea() const
{
    double vecABX = m_pointB.x - m_pointA.x;
    double vecABY = m_pointB.y - m_pointA.y;

    double vecACX = m_pointC.x - m_pointA.x;
    double vecACY = m_pointC.y - m_pointA.y;

    double crossProduct = vecABX * vecACY - vecABY * vecACX;

    return std::abs(crossProduct) / 2.0;
}

double CTriangle::GetPerimetr() const
{
    return GetLength(m_pointA, m_pointB) +
            GetLength(m_pointB, m_pointC) +
            GetLength(m_pointC, m_pointA);
}

uint32_t CTriangle::GetOutLineColor() const
{
    return m_outlineColor;
}

std::optional<uint32_t> CTriangle::GetFillColor() const
{
    return m_fillColor;
}

std::string CTriangle::ToString() const
{
    auto triangleStr = "triangle " +
            PointToString(m_pointA) +
            " " +
            PointToString(m_pointB) +
            " " +
            PointToString(m_pointC) +
            " " +
            ColorToString(GetOutLineColor());
    if (m_fillColor.has_value())
    {
        triangleStr += " " + ColorToString(GetFillColor().value());
    }
    return triangleStr;
}

void CTriangle::Draw(ICanvas &canvas)
{
    std::vector<CPoint> points;
    points.push_back(m_pointA);
    points.push_back(m_pointB);
    points.push_back(m_pointC);

    canvas.DrawLine(m_pointA, m_pointB, m_outlineColor);
    canvas.DrawLine(m_pointB, m_pointC, m_outlineColor);
    canvas.DrawLine(m_pointC, m_pointA, m_outlineColor);

    if (m_fillColor.has_value())
    {
        canvas.FillPolygon(points, m_fillColor.value());
    }
}
