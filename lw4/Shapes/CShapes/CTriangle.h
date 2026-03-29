#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
    CTriangle(
        const CPoint& pointA,
        const CPoint& pointB,
        const CPoint& pointC,
        std::optional<uint32_t> fillColor,
        uint32_t outlineColor = DEFAULT_OUTLINE_COLOR
    );

    ~CTriangle() = default;

    double GetArea() const override;
    double GetPerimetr() const override;
    std::string ToString() const override;
    uint32_t GetOutLineColor() const override;
    std::optional<uint32_t> GetFillColor() const override;

    void Draw(ICanvas &canvas) override;

private:
    CPoint m_pointA;
    CPoint m_pointB;
    CPoint m_pointC;
};
