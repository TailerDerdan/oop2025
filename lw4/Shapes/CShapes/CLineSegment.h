#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
    CLineSegment(
        const CPoint& startPoint,
        const CPoint& endPoint,
        uint32_t outLineColor = DEFAULT_OUTLINE_COLOR
    );

    ~CLineSegment() = default;

    double GetArea() const override;
    double GetPerimetr() const override;
    std::string ToString() const override;
    uint32_t GetOutLineColor() const override;

    void Draw(ICanvas &canvas) override;

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;

private:
    CPoint m_startPoint;
    CPoint m_endPoint;
};
