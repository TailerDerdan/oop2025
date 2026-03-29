#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
    CCircle(
        const CPoint &center,
        double radius,
        std::optional<uint32_t> fillColor,
        uint32_t outlineColor = DEFAULT_OUTLINE_COLOR
    );

    ~CCircle() = default;

    double GetArea() const override;
    double GetPerimetr() const override;
    std::string ToString() const override;
    uint32_t GetOutLineColor() const override;
    std::optional<uint32_t> GetFillColor() const override;

    void Draw(ICanvas &canvas) override;

    double GetRadius() const;


private:
    CPoint m_center;
    double m_radius;
};
