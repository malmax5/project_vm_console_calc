#include "logger/Logger.hpp"
#include "runner/Runner.hpp"

#include <exception>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace app_calculator;

    try
    {
        runner::Runner app;
        app.run(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Critical Error: " << e.what();
        return 1;
    }
    catch (...)
    {
        std::cerr << "Critical Error: Unknown Error occured.";
        return 1;
    }

    return 0;
}
