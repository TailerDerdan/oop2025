#include "CLineSegment.h"

#include <iomanip>
#include <sstream>
#include <ios>


CLineSegment::CLineSegment(
    const CPoint& startPoint,
    const CPoint& endPoint,
    uint32_t outLineColor
) :
    m_startPoint(startPoint), m_endPoint(endPoint)
{
    m_outlineColor = outLineColor;
}

double CLineSegment::GetPerimetr() const
{
    return GetLength(m_startPoint, m_endPoint);
}

double CLineSegment::GetArea() const
{
    return 0;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

std::string CLineSegment::ToString() const
{
    return "line " +
            PointToString(m_startPoint) +
            " " +
            PointToString(m_endPoint) +
            " " +
            ColorToString(m_outlineColor);
}

uint32_t CLineSegment::GetOutLineColor() const
{
    return m_outlineColor;
}

void CLineSegment::Draw(ICanvas &canvas)
{
    canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}