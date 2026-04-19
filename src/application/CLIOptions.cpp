#include "application/CLIOptions.hpp"

#include "core/Exceptions.hpp"

#include <cstring>
#include <getopt.h>
#include <iostream>

namespace app_calculator
{

CLIOptions CLIOptions::parse(int argc, char **argv)
{
    CLIOptions options;

    static struct option longOptions[] = {{"server", no_argument, 0, 's'},
                                          {"console", no_argument, 0, 'c'},
                                          {"client", no_argument, 0, 'l'},
                                          {"address", required_argument, 0, 'a'},
                                          {"config", required_argument, 0, 'f'},
                                          {"verbose", no_argument, 0, 'v'},
                                          {0, 0, 0, 0}};

    int opt = 0;
    int longIndex = 0;

    optind = 1;
    while ((opt = getopt_long(argc, argv, "sclva:f:", longOptions, &longIndex)) != -1)
    {
        switch (opt)
        {
        case 's':
            options.mode = AppMode::server;
            break;
        case 'c':
            options.mode = AppMode::console;
            break;
        case 'l':
            options.mode = AppMode::client;
            break;
        case 'a':
            if (optarg != nullptr)
            {
                options.address = optarg;
            }
            break;
        case 'f':
            if (optarg != nullptr)
            {
                options.configPath = optarg;
            }
            break;
        case 'v':
            options.verbose = true;
            break;
        default:
            throw exceptions::ConfigException("Unknown command line option.");
        }
    }

    if (optind < argc)
    {
        options.inputJson = argv[optind];
    }

    if (options.address.empty())
    {
        if (options.mode == AppMode::server)
        {
            options.address = core::defaultServerAddress;
        }
        else if (options.mode == AppMode::client)
        {
            options.address = core::defaultClientAddress;
        }
    }

    if (options.mode == AppMode::unknown)
    {
        throw exceptions::ConfigException(
            "App mode (--server/--client/--console) must be specified.");
    }

    return options;
}

} // namespace app_calculator
