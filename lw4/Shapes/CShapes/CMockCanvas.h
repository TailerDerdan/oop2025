#pragma once
#include "ICanvas.h"
#include <vector>

enum class Methods
{
    DrawLine,
    FillPolygon,
    DrawCircle,
    FillCircle,
};

class MockCanvas : public ICanvas
{
public:
    MockCanvas() = default;

    void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) override
    {
        calls.push_back(Methods::DrawLine);
    }

    void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) override
    {
        calls.push_back(Methods::FillPolygon);
    }

    void DrawCircle(const CPoint& center, double radius, uint32_t lineColor) override
    {
        calls.push_back(Methods::DrawCircle);
    }

    void FillCircle(const CPoint& center, double radius, uint32_t fillColor) override
    {
        calls.push_back(Methods::FillCircle);
    }

    size_t CallCount(Methods method) const
    {
        size_t count = 0;
        for (const auto& call : calls)
        {
            if (call == method)
            {
                count++;
            }
        }
        return count;
    }

    void ClearCalls()
    {
        calls.clear();
    }

private:
    std::vector<Methods> calls;
};