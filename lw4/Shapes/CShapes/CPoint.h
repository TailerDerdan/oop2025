#pragma once
#include <cmath>
#include <string>

struct CPoint
{
    double x = 0.0;
    double y = 0.0;
};

inline double GetLength(const CPoint& pointFirst, const CPoint& pointSecond)
{
    return std::sqrt(
        (pointFirst.x - pointSecond.x) * (pointFirst.x - pointSecond.x) +
        (pointFirst.y - pointSecond.y) * (pointFirst.y - pointSecond.y));
}

inline std::string PointToString(const CPoint& point)
{
    return std::to_string(point.x) + ":" + std::to_string(point.y);
}