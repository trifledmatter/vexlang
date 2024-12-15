#include "manager.hpp"
#include "response.hpp"

CommandManager commandManager;

void CommandManager::registerCommand(std::unique_ptr<Command> command) {
    std::string key = command->name;
    commands[key] = std::move(command);
}

void CommandManager::executeCommand(const std::string& key, const std::vector<std::string>& args) {
    if (commands.find(key) != commands.end()) {
        std::string args_list;
        for (size_t i = 0; i < args.size(); ++i) {
            args_list += args[i];
            if (i < args.size() - 1) {
                args_list += ", ";
            }
        }

        update_screen("Executing: " + key, "Args: " + args_list);
        commands[key]->execute(args);
    } else {
        send_serial("Command not found: " + key);
        update_screen("Command not found: " + key, "None");
    }
}

void CommandManager::showCommands() {
    for (const auto& command : commands) {
        command.second->showInfo();
    }
}
