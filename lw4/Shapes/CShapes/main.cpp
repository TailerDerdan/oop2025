#include <iostream>

#include "CCanvas.h"
#include "CController.h"

int main()
{
    std::ifstream input;
    input.open("image.txt");
    if (!input.is_open())
    {
        std::cout << "Unable to open input file" << std::endl;
        return EXIT_FAILURE;
    }
    std::ofstream output;
    output.open("output.txt");
    if (!output.is_open())
    {
        std::cout << "Unable to open output file" << std::endl;
        return EXIT_FAILURE;
    }
    CCanvas m_canvas;
    CController controller(input, output, m_canvas);

    output << ">";
    while (controller.HandleCommand())
    {
        output << ">";
    }

    while (m_canvas.GetWindow().isOpen())
    {
        while (const std::optional event = m_canvas.GetWindow().pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_canvas.GetWindow().close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    m_canvas.GetWindow().close();
                }
            }
        }

        m_canvas.GetWindow().clear(sf::Color::White);
        controller.DrawShapes();
        m_canvas.GetWindow().display();
    }
}