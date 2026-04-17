#include "application/CLIOptions.hpp"

#include "core/Exceptions.hpp"

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
            options.mode = AppMode::server;
        }
        else if (modeArg == "--console")
        {
            options.mode = AppMode::console;
            if (argc > 2)
            {
                options.inputJson = argv[2];
            }
        }
        else if (modeArg == "--client")
        {
            options.mode = AppMode::client;
            if (argc > 2)
            {
                options.inputJson = argv[2];
            }

            if (argc > 3)
            {
                options.serverAddress = argv[3];
            }
        }
        else
        {
            throw exceptions::ConfigException(
                "App mode (--server/--client/--console) must be specified.");
        }
    }

    return options;
}

} // namespace app_calculator
