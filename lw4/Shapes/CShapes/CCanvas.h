#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
    CCanvas();
    void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) override;
    void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) override;
    void DrawCircle(const CPoint& center, double radius, uint32_t lineColor) override;
    void FillCircle(const CPoint& center, double radius, uint32_t fillColor) override;
    ~CCanvas() = default;

    sf::RenderWindow& GetWindow() { return m_window; }

private:
    static sf::Color GetColor(uint32_t color);

private:
    sf::RenderWindow m_window;
};
