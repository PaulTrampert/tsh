//
// Created by paul on 9/11/25.
//

#include "job_tracker.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "job.h"

#define MAX_JOBS 1024

static pthread_mutex_t job_mutex = PTHREAD_MUTEX_INITIALIZER;

static Job *jobs[MAX_JOBS];

static Job *foregroundJob = NULL;

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

static void send_signal(Job *job, int signum)
{
    for (int i = 0; i < job->numPids; i++)
    {
        kill(job->pids[i], signum);
    }
}

int job_tracker_add(Job *job)
{
    pthread_mutex_lock(&job_mutex);
    int jobId = find_slot();
    if (jobId == -1)
    {
        pthread_mutex_unlock(&job_mutex);
        return -1;
    }

    job->id = jobId;
    jobs[jobId] = job;

    pthread_mutex_unlock(&job_mutex);
    return job->id;
}

void job_tracker_set_foreground(Job *job)
{
    if (!job)
        return;

    pthread_mutex_lock(&job_mutex);
    foregroundJob = job;

    while (foregroundJob != NULL)
    {
        pthread_mutex_unlock(&job_mutex);
        int status;
        pid_t pid = waitpid(-1, &status, WUNTRACED);
        job_tracker_handle_sigchld(pid, status);
        pthread_mutex_lock(&job_mutex);
    }
    pthread_mutex_unlock(&job_mutex);
}

Job* job_tracker_get_job(int jobid)
{
    return jobs[jobid];
}

void job_tracker_signal_foreground(int signum)
{
    pthread_mutex_lock(&job_mutex);
    if (foregroundJob)
    {
        send_signal(foregroundJob, signum);
    }
    pthread_mutex_unlock(&job_mutex);
}

void job_tracker_send_signal(int jobId, int signum)
{
    pthread_mutex_lock(&job_mutex);
    Job *job = job_tracker_get_job(jobId);
    if (job)
    {
        send_signal(job, signum);
    }
    pthread_mutex_unlock(&job_mutex);
}

void job_tracker_kill_all()
{
    pthread_mutex_lock(&job_mutex);
    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (jobs[i] != NULL)
        {
            send_signal(jobs[i], SIGKILL);
        }
    }
    pthread_mutex_unlock(&job_mutex);
}

void job_tracker_handle_sigchld(pid_t pid, int status)
{
    pthread_mutex_lock(&job_mutex);
    Job *job = find_job_by_pid(pid);
    if (!job)
    {
        pthread_mutex_unlock(&job_mutex);
        return;
    }
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
        if (job->background)
        {
            printf("\n");
            job_print(STDIN_FILENO, job);
            printf("\n");
        }
        jobs[job->id] = NULL;
        job_free(job);
    }
    pthread_mutex_unlock(&job_mutex);
}
