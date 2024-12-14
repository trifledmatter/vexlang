#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <vector>
#include <memory>

#include "command.hpp"
#include "manager.hpp"
#include "handler.hpp"

/**
 * @author ethan@trifledmatter.com
 * @details This listener will listen to and read incoming serial messages from USB
 * connected-devices.
 */
void listener(void* param);

#endif