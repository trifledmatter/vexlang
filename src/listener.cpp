#include "main.h"
#include "listener.hpp"
#include "handler.hpp"
#include "command.hpp"

#include <stdio.h>
#include <string.h>

void listener(void* param) {
    char buffer[128];

    while (true) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            handler(buffer);
        }

        pros::delay(60);
    }
}