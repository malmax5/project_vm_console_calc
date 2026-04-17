#include "application/CLIOptions.hpp"

namespace app_calculator
{

CLIOptions CLIOptions::parse(int argc, char **argv)
{
    CLIOptions options;
    
    if (argc > 1)
    {
        std::string modeArg(argv[1]);
        if (modeArg == "--server")
        {
            options.mode = AppMode::Server;
        }
        else if (modeArg == "--console")
        {
            options.mode = AppMode::Console;
            if (argc > 2)
            {
                options.inputJson = argv[2];
            }
        }
        else if (modeArg == "--client")
        {
            options.mode = AppMode::Client;
            if (argc > 2)
            {
                options.inputJson = argv[2];
            }

            if (argc > 3)
            {
                options.serverAddress = argv[3];
            }
        }
    }

    return options;
}

} // namespace app_calculator
