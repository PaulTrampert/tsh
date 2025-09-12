#ifndef STATE_JOB_H
#define STATE_JOB_H

#include <sys/types.h>
#include <stdbool.h>
#include "../grammar/ast.h"

typedef enum
{
    RUNNING = 0,
    STOPPED = 1,
    EXITED = 2
} JobStatus;

typedef struct
{
    int id;
    JobStatus status;
    bool background;
    int numPids;
    int completedPids;
    AstNode *jobAst;
    pid_t *pids;
} Job;

Job *job_new(AstNode *ast, int numPids, pid_t *pids, bool background);

void job_print(int outFd, Job *job);

void job_incr_completed(Job *job, pid_t pid);

void job_free(Job *job);

#endif // STATE_JOB_H