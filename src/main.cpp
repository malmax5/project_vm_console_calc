#include "runner/Runner.hpp"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    using namespace app_calculator;
    runner::Runner app;

    if (argc > 1)
    {
        app.run(argv[1]);
        return 0;
    }

    std::cout << "Enter JSON task: ";
    std::string input;
    std::string line;

    while (std::getline(std::cin, line))
    {
        input += line;
    }

    if (!input.empty())
    {
        app.run(input);
    }

    return 0;
}
