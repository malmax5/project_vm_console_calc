#include "logger/Logger.hpp"
#include "runner/Runner.hpp"

#include <exception>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace app_calculator;

    try
    {
        auto &logger = logger::Logger::instance();

        runner::Runner app;

        if (argc > 1)
        {
            app.run(argv[1]);
        }
        else
        {
            logger.warn("No arguments provided. Please provide argument as JSON with 'operation': "
                        "'op' and 'operands': [fields].");
        }
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
