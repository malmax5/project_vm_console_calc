#include "calculator.hpp"

int g_argc;
char** g_argv;

int main(int argc, char** argv)
{
    g_argc = argc;
    g_argv = argv;

    run();

    return 0;
}
