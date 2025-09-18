//
// Created by paul on 9/14/25.
//

#include "builtins.h"
#include "jobs.h"
#include <string.h>

#include "bg.h"

builtin_cmd_t get_builtin(const char* cmdName)
{
    if (strcmp(cmdName, "jobs") == 0)
    {
        return &jobs;
    }
    if (strcmp(cmdName, "bg") == 0)
    {
        return &bg;
    }
    return NULL;
}
