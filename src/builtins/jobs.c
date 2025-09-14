//
// Created by paul on 9/14/25.
//

#include "jobs.h"

#include <unistd.h>

#include "../state/job_tracker.h"

int jobs(int argc, char** argv)
{
    job_tracker_print_jobs(STDOUT_FILENO);

    return 0;
}
