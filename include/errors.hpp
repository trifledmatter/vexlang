#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>
#include <functional>


void handleErrors(const std::string &context, const std::function<void()> &func);
void logError(const std::string &context, const std::string &errorMessage);

#endif
