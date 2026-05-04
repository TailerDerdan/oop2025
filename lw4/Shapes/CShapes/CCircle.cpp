#include "CCircle.h"

#include <iomanip>
#include <sstream>
#include <ios>

CCircle::CCircle(
    const CPoint &center,
    double radius,
    std::optional<uint32_t> fillColor,
    uint32_t outlineColor
) : m_center(center),
    m_radius(radius)
{
    m_outlineColor = outlineColor;
    m_fillColor = fillColor;
}

double CCircle::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimetr() const
{
    return M_PI * m_radius * 2.0;
}

uint32_t CCircle::GetOutLineColor() const
{
    return m_outlineColor;
}

std::optional<uint32_t> CCircle::GetFillColor() const
{
    return m_fillColor;
}

double CCircle::GetRadius() const
{
    return m_radius;
}

std::string CCircle::ToString() const
{
    auto circleStr = "circle " +
            PointToString(m_center) +
            " " +
            std::to_string(m_radius) +
            " " +
            ColorToString(GetOutLineColor());
    if (m_fillColor.has_value())
    {
        circleStr += " " + ColorToString(GetFillColor().value());
    }
    return circleStr;
}

void CCircle::Draw(ICanvas &canvas)
{
    canvas.DrawCircle(m_center, m_radius, m_outlineColor);
    if (m_fillColor.has_value())
    {
        canvas.FillCircle(m_center, m_radius, m_fillColor.value());
    }
}
