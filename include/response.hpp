#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <algorithm>

void send_serial(const std::string& message);
void update_screen(const std::string& errors, const std::string& response);

#endif
