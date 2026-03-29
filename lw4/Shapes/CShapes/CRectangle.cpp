#include "CRectangle.h"

#include <iomanip>
#include <sstream>
#include <ios>

CRectangle::CRectangle(
    const CPoint &leftTop,
    double width,
    double height,
    std::optional<uint32_t> fillColor,
    uint32_t outlineColor
) : m_leftTop(leftTop),
    m_width(width),
    m_height(height)
{
    m_outlineColor = outlineColor;
    m_fillColor = fillColor;
}

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimetr() const
{
    return (m_width + m_height) * 2.0;
}

uint32_t CRectangle::GetOutLineColor() const
{
    return m_outlineColor;
}

std::optional<uint32_t> CRectangle::GetFillColor() const
{
    return m_fillColor;
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

std::string CRectangle::ToString() const
{
    auto shapeStr = "rectangle " +
            PointToString(m_leftTop) +
            " " +
            std::to_string(m_width) +
            " " +
            std::to_string(m_height) +
            " " +
            ColorToString(GetOutLineColor());
    if (m_fillColor.has_value())
    {
        shapeStr += " " + ColorToString(GetFillColor().value());
    }
    return shapeStr;
}

void CRectangle::Draw(ICanvas& canvas)
{
    CPoint leftTop = m_leftTop;
    CPoint leftBottom = m_leftTop;
    leftBottom.y += m_height;

    CPoint rightTop = m_leftTop;
    rightTop.x += m_width;

    CPoint rightBottom = m_leftTop;
    rightBottom.x += m_width;
    rightBottom.y += m_height;

    std::vector<CPoint> points;
    points.push_back(leftTop);
    points.push_back(rightTop);
    points.push_back(rightBottom);
    points.push_back(leftBottom);

    canvas.DrawLine(leftTop, rightTop, m_outlineColor);
    canvas.DrawLine(rightTop, rightBottom, m_outlineColor);
    canvas.DrawLine(rightBottom, leftBottom, m_outlineColor);
    canvas.DrawLine(leftBottom, leftTop, m_outlineColor);
    if (m_fillColor.has_value())
    {
        canvas.FillPolygon(points, m_fillColor.value());
    }
}