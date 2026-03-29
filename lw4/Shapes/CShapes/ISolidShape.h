#pragma once

#include "IShape.h"
#include <optional>

constexpr uint32_t DEFAULT_FILL_COLOR = 0x000000;

class ISolidShape : public IShape
{
public:
    virtual std::optional<uint32_t> GetFillColor() const = 0;

protected:
    std::optional<uint32_t> m_fillColor;
};
