#include "calculator.hpp"

#include <getopt.h>
#include <stdlib.h>

void parse(CalcContext *ctx, int argc, char **argv)
{
    static struct option long_options[] = {
        {"first", required_argument, 0, 'a'},
        {"second", required_argument, 0, 'b'},
        {"op", required_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    int opt;

    while ((opt = getopt_long(argc, argv, "a:b:o:h", long_options, nullptr)) != -1)
    {
        switch (opt)
        {
        case 'a':
            ctx->first = atoll(optarg);
            break;
        case 'b':
            ctx->second = atoll(optarg);
            break;
        case 'o':
            ctx->operation = optarg[0];
            break;
        case 'h':
            ctx->appStatus = AppStatus::ERROR_HELP;
            return;
        default:
            ctx->appStatus = AppStatus::ERROR_PARSE;
            return;
        }
    }
}
