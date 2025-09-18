//
// Created by paul on 9/17/25.
//
#include <signal.h>
#include "../state/job_tracker.h"
#include "bg.h"

#include <stdio.h>
#include <stdlib.h>

static bool is_numeric(const char *str)
{
    if (*str == '\0')
        return false;
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return false;
        str++;
    }
    return true;
}

int bg(int argc, char** argv)
{
    if (argc < 2)
    {
        usage:
        printf("Usage: bg <pid | %%job_id>\n");
        return -1;
    }
    char *id_str = argv[1];
    if (id_str == NULL)
    {
        goto usage;
    }
    if (id_str[0] == '%')
    {
        if (!is_numeric(id_str + 1))
        {
            goto usage;
        }
        int jid = atoi(id_str + 1);
        job_tracker_send_signal(jid, SIGCONT);
    }
    else
    {
        if (!is_numeric(id_str))
        {
            goto usage;
        }
        pid_t pid = atoi(id_str);
        kill(pid, SIGCONT);
    }
    return 0;
}
