//
// Created by paul on 9/11/25.
//

#include "job_tracker.h"

#include <stdlib.h>
#include <sys/wait.h>

#include "job.h"

#define MAX_JOBS 1024

Job *jobs[MAX_JOBS];

Job *foregroundJob = NULL;

static Job *find_job_by_pid(pid_t pid)
{
    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (jobs[i] != NULL)
        {
            for (int j = 0; j < jobs[i]->numPids; j++)
            {
                if (jobs[i]->pids[j] == pid)
                    return jobs[i];
            }
        }
    }
    return NULL;
}

static int find_slot()
{
    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (jobs[i] == NULL)
            return i;
    }
    return -1;
}

int job_tracker_add(Job *job)
{
    int jobId = find_slot();
    if (jobId == -1)
        return -1; // No available slot

    job->id = jobId;
    jobs[jobId] = job;

    return job->id;
}

void job_tracker_set_foreground(Job *job)
{
    if (!job)
        return;

    foregroundJob = job;

    while (foregroundJob != NULL)
    {
        int status;
        pid_t pid = waitpid(-1, &status, WUNTRACED);
        job_tracker_handle_sigchld(pid, status);
    }
}

Job* job_tracker_get_job(int jobid)
{
    return jobs[jobid];
}

void job_tracker_handle_sigchld(pid_t pid, int status)
{
    Job *job = find_job_by_pid(pid);
    if (!job)
        return;
    if (WIFEXITED(status) || WIFSIGNALED(status))
    {
        job->completedPids++;
    }
    if (WIFSTOPPED(status))
    {
        job->status = STOPPED;
        job->background = true;
        if (job == foregroundJob)
        {
            foregroundJob = NULL;
        }
    }
    if (job->completedPids == job->numPids)
    {
        job->status = EXITED;
        if (job == foregroundJob)
        {
            foregroundJob = NULL;
        }
        jobs[job->id] = NULL;
        job_free(job);
    }
}
