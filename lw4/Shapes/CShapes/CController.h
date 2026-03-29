#pragma once

#include <fstream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

#include "ICanvas.h"
#include "IShape.h"

using ActionMap = std::unordered_map<std::string, std::function<void()>>;

class CController
{
public:
    CController(std::istream& input, std::ostream& output, ICanvas& canvas);

    [[nodiscard]] IShape* GetShapeWithMaxArea() const;
    [[nodiscard]] IShape* GetShapeWithMinPerimetr() const;

    void DrawShapes();

    bool HandleCommand();

private:
    void DefineLine();
    void DefineTriangle();
    void DefineRectangle();
    void DefineCircle();

private:
    std::vector<std::unique_ptr<IShape>> m_shapes;
    std::istream& m_input;
    std::ostream& m_output;
    ActionMap m_actionMap;
    ICanvas& m_canvas;
};