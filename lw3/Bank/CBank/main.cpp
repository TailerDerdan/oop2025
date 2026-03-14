#include <iostream>

#include "Simulation.h"

struct Args
{
    size_t iterations;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        return std::nullopt;
    }

    Args args;
    args.iterations = std::stoull(argv[1]);
    return args;
}

int main(int argc, char* argv[])
{
    try
    {
        const auto args = ParseArgs(argc, argv);
        size_t iterations = 0;
        if (args)
        {
            iterations = args->iterations;
        }
        else
        {
            std::cout << "Please, enter count of iterations: ";
            if (!(std::cin >> iterations))
            {
                std::cerr << "Invalid input iterations" << std::endl;
                return EXIT_FAILURE;
            }
        }
        Simulation simulation;
        simulation.Run(iterations);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
