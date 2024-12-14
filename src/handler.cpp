#include "handler.hpp"
#include "pros/llemu.hpp"

#include <vector>
#include <string>
#include <iostream>

#include "commands/ping.hpp"

/**
 * @author ethan@trifledmatter.com
 * @details This will tokenize and prep commands for the handler
 */
std::vector<std::string> tokenize(const char* message) {
    std::vector<std::string> tokens;
    std::string token;
    for (size_t i = 0; message[i] != '\0'; ++i) {
        if (message[i] == ' ') {
            tokens.push_back(token);
            token.clear();
        } else {
            token.push_back(message[i]);
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * @author ethan@trifledmatter.com
 * @details This handler will tokenize command inputs and act accordingly
 */
void handler(const char* message) {
    std::vector<std::string> tokens = tokenize(message);

    if (tokens.size() < 3) {
        pros::lcd::set_text(4, "Invalid Command");
        return;
    }

    std::string key = tokens[1] + " " + tokens[2];
    printf("Attempting to execute: %s\n", key.c_str());

    commandManager.executeCommand(key, {tokens.begin() + 3, tokens.end()});
}
