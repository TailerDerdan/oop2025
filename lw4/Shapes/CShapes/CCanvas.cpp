#include "CCanvas.h"

CCanvas::CCanvas()
{
    m_window.create(sf::VideoMode({1920, 1080}), "SFML Canvas");
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor)
{
    sf::VertexArray line(sf::PrimitiveType::Lines, 2);
    line[0].position = {float(from.x), float(from.y)};
    line[1].position = {float(to.x), float(to.y)};

    auto color = GetColor(lineColor);
    line[0].color = color;
    line[1].color = color;

    m_window.draw(line);
}

void CCanvas::FillPolygon(const std::vector<CPoint> &points, uint32_t fillColor)
{
    if (points.size() < 3) {
        return;
    }

    sf::VertexArray polygon(sf::PrimitiveType::TriangleFan, points.size());

    auto color = GetColor(fillColor);

    for (size_t i = 0; i < points.size(); ++i) {
        polygon[i].position = {
            float(points[i].x),
            float(points[i].y)
        };
        polygon[i].color = color;
    }

    m_window.draw(polygon);
}

void CCanvas::DrawCircle(const CPoint &center, double radius, uint32_t lineColor)
{
    auto radiusFloat = float(radius);
    sf::CircleShape circle(radiusFloat);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({float(center.x), float(center.y)});
    circle.setOutlineColor(GetColor(lineColor));
    m_window.draw(circle);
}

void CCanvas::FillCircle(const CPoint &center, double radius, uint32_t fillColor)
{
    auto radiusFloat = float(radius);
    sf::CircleShape circle(radiusFloat);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({float(center.x), float(center.y)});
    circle.setFillColor(GetColor(fillColor));
    m_window.draw(circle);
}

sf::Color CCanvas::GetColor(uint32_t color)
{
    return {
         static_cast<std::uint8_t>((color >> 24) & 0xFF),
         static_cast<std::uint8_t>((color >> 16) & 0xFF),
         static_cast<std::uint8_t>((color >> 8) & 0xFF),
         static_cast<std::uint8_t>(color & 0xFF)
     };
}
