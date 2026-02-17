#include "calculator.hpp"

static AppStatus validateOperationAndOperands(const CalcContext *ctx)
{
    AppStatus retStatus = AppStatus::SUCCESS;

    switch (ctx->operation)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        if ((ctx->argCountCheckMask & 3) != 3)
        {
            retStatus = AppStatus::ERROR_VALIDATION;
        }
        break;
    case '!':
        if ((ctx->argCountCheckMask & 1) == 0)
        {
            retStatus = AppStatus::ERROR_VALIDATION;
        }
        break;
    default:
        retStatus = AppStatus::ERROR_VALIDATION;
        break;
    }

    return retStatus;
}

void check(CalcContext *ctx)
{
    if (ctx->appStatus != AppStatus::SUCCESS)
    {
        return;
    }

    if (ctx->operation == '\0' || ctx->operation == ' ')
    {
        ctx->appStatus = AppStatus::ERROR_VALIDATION;
        return;
    }

    ctx->appStatus = validateOperationAndOperands(ctx);
    if (ctx->appStatus != AppStatus::SUCCESS)
    {
        return;
    }
}
