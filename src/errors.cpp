#include "errors.hpp"
#include "response.hpp"

void handleErrors(const std::string &context, const std::function<void()> &func)
{
    try
    {
        func();
    }
    catch (const std::exception &e)
    {
        logError(context, e.what());
    }
    catch (...)
    {
        logError(context, "An unknown error occurred.");
    }
}

void logError(const std::string &context, const std::string &errorMessage)
{
    update_screen(context + " Error", errorMessage);
    send_serial("Error in " + context + ": " + errorMessage);
}
