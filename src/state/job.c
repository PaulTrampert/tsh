#include <stdio.h>
#include <stdlib.h>
#include "job.h"
#include "../exit_codes.h"

static char *statusStrings[] = {
    "Running",
    "Stopped",
    "Exited"
};

Job *job_new(AstNode *ast, int numPids, int *pids, bool background)
{
    Job *job = malloc(sizeof(Job));
    if (!job)
        exit(EOOM);

    job->id = 0; // Will be set by job tracker
    job->status = RUNNING;
    job->background = background;
    job->numPids = numPids;
    job->completedPids = 0;
    job->jobAst = ast;
    job->pids = pids;

    return job;
}

void job_print(int outFd, Job *job)
{
    if (!job)
        return;

    char *statusStr = statusStrings[job->status];
    dprintf(outFd, "[%d] + %s\t\t", job->id, statusStr);
    ast_print(job->jobAst, outFd);

    dprintf(outFd, "\n");
    for (int i = 0; i < job->numPids; i++)
    {
        dprintf(outFd, "%d ", job->pids[i]);
    }
    dprintf(outFd, "\n");
}

void job_incr_completed(Job* job, pid_t pid)
{
    for (int i = 0; i < job->numPids; i++)
    {
        if (job->pids[i] == pid)
        {
            job->completedPids++;
            break;
        }
    }
}

void job_free(Job* job)
{
    free(job->pids);
    ast_free_node(job->jobAst);
    free(job);
}
