#ifndef STATE_JOB_H
#define STATE_JOB_H

#include <sys/types.h>
#include <stdbool.h>
#include "../grammar/ast.h"


typedef struct _job {
    int id;
    int status;
    bool background;
    int numPids;
    AstNode *jobAst;
    pid_t *pids;
} Job;

Job *job_new(AstNode *ast);

void job_print(int outFd, Job *job);

#endif // STATE_JOB_H