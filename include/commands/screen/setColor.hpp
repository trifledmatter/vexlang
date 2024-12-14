#ifndef SET_COLOR_COMMAND_HPP
#define SET_COLOR_COMMAND_HPP

#include "command.hpp"
#include "pros/screen.hpp"
#include "pros/colors.hpp" 

class SetColorCommand : public Command {
public:
    SetColorCommand();

    void execute(const std::vector<std::string>& args) override;
};

#endif
