#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "ICanvas.h"

class ICanvasDrawable
{
public:
    virtual void Draw(ICanvas& canvas) = 0;
    virtual ~ICanvasDrawable() = default;
};

constexpr uint32_t DEFAULT_OUTLINE_COLOR = 0xffffff;

class IShape: public ICanvasDrawable
{
public:
    virtual double GetArea() const = 0;
    virtual double GetPerimetr() const = 0;
    virtual std::string ToString() const = 0;
    virtual uint32_t GetOutLineColor() const = 0;

    virtual ~IShape() = default;

protected:
    static std::string ColorToString(uint32_t color)
    {
        std::ostringstream oss;
        oss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(6) << color;
        return oss.str();
    }

    uint32_t m_outlineColor = 0;
};