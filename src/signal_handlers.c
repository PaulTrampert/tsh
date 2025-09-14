//
// Created by paul on 9/11/25.
//
#include <signal.h>
#include <wait.h>
#include "signal_handlers.h"

#include <stdlib.h>

#include "state/job_tracker.h"

static void handle_sigchld(int signum)
{
    if (signum != SIGCHLD)
        return;
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    job_tracker_handle_sigchld(pid, status);
}

static void handle_signal_forward(int signum)
{
    job_tracker_signal_foreground(signum);
}

static void handle_exit()
{
    job_tracker_kill_all();
}

void signal_handlers_init()
{
    signal(SIGCHLD, handle_sigchld);
    signal(SIGINT, handle_signal_forward);
    signal(SIGTSTP, handle_signal_forward);
}
