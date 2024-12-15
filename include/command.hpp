#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <iostream>
#include <vector>

/**
 * @author ethan@trifledmatter.com
 * @details This handler will tokenize command inputs and act accordingly
 */
class Command {
public:
    std::string name;       
    std::string author;     
    std::string description;
    float version;   

    Command(const std::string& name, const std::string& author, const std::string& description,
         float version)
        : name(name), author(author), description(description), version(version) {}

    virtual void execute(const std::vector<std::string>& args) = 0;

    virtual void showInfo() {
        std::cout << "Command: " << name << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Version: " << version << std::endl;
    }

    virtual ~Command() = default;
};


#endif
