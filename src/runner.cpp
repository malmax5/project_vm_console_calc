#include "calculator.hpp"

void run(int argc, char **argv)
{
    CalcContext ctx = {0, 0, 0, 0, pvm_math_lib::MathStatus::OK, AppStatus::SUCCESS};

    parse(&ctx, argc, argv);
    check(&ctx);

    if (ctx.appStatus == AppStatus::SUCCESS)
    {
        calculate(&ctx);
    }

    print(&ctx);
}

void calculate(CalcContext *ctx)
{
    switch (ctx->operation)
    {
    case '+':
        ctx->mathStatus = pvm_math_lib::add(ctx->first, ctx->second, ctx->result);
        break;
    case '-':
        ctx->mathStatus = pvm_math_lib::sub(ctx->first, ctx->second, ctx->result);
        break;
    case '*':
        ctx->mathStatus = pvm_math_lib::mul(ctx->first, ctx->second, ctx->result);
        break;
    case '/':
        ctx->mathStatus = pvm_math_lib::div(ctx->first, ctx->second, ctx->result);
        break;
    case '^':
        ctx->mathStatus = pvm_math_lib::pow(ctx->first, ctx->second, ctx->result);
        break;
    case '!':
        ctx->mathStatus = pvm_math_lib::factorial(ctx->first, ctx->result);
        break;
    default:
        ctx->appStatus = AppStatus::ERROR_VALIDATION;
    }
}
