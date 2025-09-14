//
// Created by paul on 9/14/25.
//

#include "builtins.h"
#include "jobs.h"
#include <string.h>

builtin_cmd_t get_builtin(const char* cmdName)
{
    if (strcmp(cmdName, "jobs") == 0)
    {
        return &jobs;
    }
    return NULL;
}
