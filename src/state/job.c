#include <stdio.h>
#include <stdlib.h>
#include "job.h"
#include "../exit_codes.h"

static int nextJobId = 1;

Job *job_new(AstNode *ast)
{
    Job *job = (Job *)malloc(sizeof(Job));
    if (!job)
        exit(EOOM);

    job->id = nextJobId++; // Not assigned yet
    job->status = 0;
    job->background = false;
    job->numPids = 0;
    job->jobAst = ast;
    job->pids = NULL;

    return job;
}

void job_print(int outFd, Job *job)
{
    if (!job)
        return;

    dprintf(outFd, "[%d] - ", job->id);
    ast_print(job->jobAst, outFd);

    dprintf(outFd, ":");
    for (int i = 0; i < job->numPids; i++)
    {
        dprintf(outFd, " %d", job->pids[i]);
    }
}
