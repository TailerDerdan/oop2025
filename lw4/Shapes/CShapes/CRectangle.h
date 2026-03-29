#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
    CRectangle(
        const CPoint& pointA,
        double width,
        double height,
        std::optional<uint32_t> fillColor,
        uint32_t outlineColor = DEFAULT_OUTLINE_COLOR
    );

    ~CRectangle() = default;

    double GetArea() const override;
    double GetPerimetr() const override;
    std::string ToString() const override;
    uint32_t GetOutLineColor() const override;
    std::optional<uint32_t> GetFillColor() const override;

    void Draw(ICanvas& canvas) override;

    double GetWidth() const;
    double GetHeight() const;

private:
    CPoint m_leftTop;
    double m_width;
    double m_height;
};
