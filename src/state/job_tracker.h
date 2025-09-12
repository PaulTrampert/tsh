//
// Created by paul on 9/11/25.
//

#ifndef TSH_JOB_TRACKER_H
#define TSH_JOB_TRACKER_H
#include <sys/types.h>

#include "job.h"

void job_tracker_handle_sigchld(pid_t pid, int status);
int job_tracker_add(Job *job);
void job_tracker_set_foreground(Job *job);
Job *job_tracker_get_job(int jobid);
void job_tracker_signal_foreground(int signum);
void job_tracker_send_signal(int jobId, int signum);
void job_tracker_kill_all();
#endif //TSH_JOB_TRACKER_H